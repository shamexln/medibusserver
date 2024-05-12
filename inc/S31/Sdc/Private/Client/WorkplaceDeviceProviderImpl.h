#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Sdc/Private/Discovery/MdsTypeErrorReporter.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/EndpointReferenceIo.h>
#include <S31/Sdc/Public/Common/InstanceIdentifierFactory.h>
#include <S31/Sdc/Public/Common/MdibAccess.h>
#include <S31/Sdc/Public/Discovery/DiscoveryProvider.h>
#include <S31/Sdc/Public/Discovery/LocationContextDiscovery.h>

#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/Model/CodedValueIo.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetailIo.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifierSemantic.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

#include <algorithm>
#include <optional>
#include <queue>


namespace S31::Sdc::Impl
{

namespace WorkplaceDeviceProviderImplHelper
{

/**
 * @brief States of the WorkplaceDeviceProviderImpl.
 * @ingroup S31SdcClient
 */
enum class State
{
    Stopped, ///< Initial state
    Probing,
    Connected
};

DFL_ENUM_CLASS_STREAM_OPERATOR(State, (Stopped)(Probing)(Connected))

/**
 * @brief Allows monitoring of state transitions.
 * @ingroup S31SdcClient
 */
class StateWrapper
{
    public:
        StateWrapper() = default;
        StateWrapper(const StateWrapper&) = delete;
        StateWrapper(StateWrapper&&) = delete;
        StateWrapper& operator=(const StateWrapper&) = delete;
        StateWrapper& operator=(StateWrapper&&) = delete;

        explicit operator State() noexcept
        {
            return m_state;
        }

        StateWrapper& operator=(State newState) noexcept
        {
            set(newState);
            return *this;
        }

        bool stateEquals(State rhs) const noexcept
        {
            return m_state == rhs;
        }

        bool stateNotEquals(State rhs) const noexcept
        {
            return m_state != rhs;
        }

    private:
        void set(State newState) noexcept
        {
            if (newState != m_state)
            {
                S31_STREAM_TRACE_LOGGER("Sdc.Client", "State transition: ", m_state, " to ", newState);
                m_state = newState;
            }
        }

        State m_state{State::Stopped};
};

struct CurrentDeviceInfo
{
        std::optional<EndpointReference> epr;
        std::shared_ptr<RemoteDevice> device;
};

struct LocationInfo
{
        DFL::Mdib::LocationDetail detail;
        DFL::Mdib::InstanceIdentifier identifier;
};

class ForwardingMdibObserver : public DFL::Mdib::MdibObserver
{
    public:
        using ForwardFunc = std::function<void(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType)>;

        explicit ForwardingMdibObserver(ForwardFunc f):
            m_forwardFunc(std::move(f))
        {}

        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) override
        {
            m_forwardFunc(mdib, changes, changeType);
        }

    private:
        ForwardFunc m_forwardFunc;
};

}

class WorkplaceDeviceProviderImpl :
        public S31::Sdc::RemoteDevicesObserver,
        public S31::Sdc::RemoteDevicesSubject,
        public LocationContextDiscoveryObserver,
        public std::enable_shared_from_this<WorkplaceDeviceProviderImpl>
{
    public:
        WorkplaceDeviceProviderImpl(std::weak_ptr<S31::Sdc::DiscoveryProvider> discoveryProvider,
                                    std::weak_ptr<S31::Sdc::RemoteDevicesProvider> nodeProvider):
            m_discoveryProvider(std::move(discoveryProvider)),
            m_nodeProvider(std::move(nodeProvider))
        {
        }

        void setOwnMdibAccess(const std::shared_ptr<DFL::Mdib::MdibAccess>& localMdibAccess)
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            if (!localMdibAccess)
            {
                return;
            }

            std::weak_ptr<WorkplaceDeviceProviderImpl> const weakThis = shared_from_this();
            auto forwardFunc = [weakThis](const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType)
            {
                if (auto t = weakThis.lock())
                {
                    t->onLocalMdibChange(mdib, changes, changeType);
                }
            };
            m_localMdibObserver = std::make_shared<ForwardingMdibObserver>(forwardFunc);
            localMdibAccess->registerObserver(m_localMdibObserver);
        }

        void setOwnLocation(const DFL::Mdib::LocationDetail& location)
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            {
                std::scoped_lock<std::mutex> const lock{m_mutex};
                if (m_ownLocation && m_ownLocation->detail == location)
                {
                    return;
                }
            }

            disconnectAndStop("Own location changed.");
            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Set own location to ", location);
            {
                std::scoped_lock<std::mutex> const lock{m_mutex};

                if (auto id = S31::Sdc::InstanceIdentifierFactory::fallbackInstanceIdentifier(location))
                {
                    m_ownLocation = LocationInfo{location, *id};
                }
                else
                {
                    S31_STREAM_TRACE_LOGGER("Sdc.Client", "Given location seems invalid, could not make instance identifier");
                    m_ownLocation = std::nullopt;
                    return;
                }

            }
            toStateProbing();
        }

        void clearOwnLocation()
        {
            {
                std::scoped_lock<std::mutex> const lock{m_mutex};
                if (!m_ownLocation)
                {
                    return;
                }

                m_ownLocation = std::nullopt;
            }

            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Own location cleared.");
            disconnectAndStop("Own location was cleared.");
        }

        void blacklistOwnEpr(const EndpointReference& epr)
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            std::unique_lock<std::mutex> lock{m_mutex};
            if (m_ownEprForBlacklisting && S31::Sdc::addressEquals(epr, *m_ownEprForBlacklisting))
            {
                return;
            }

            m_ownEprForBlacklisting = epr;

            if (m_state.stateEquals(State::Connected))
            {
                if (!m_currentDevice.device)
                {
                    return;
                }

                if (S31::Sdc::addressEquals(m_currentDevice.device->endpointReference(), epr))
                {
                    lock.unlock();
                    disconnectAndStop("The EPR address of the connected device is now blacklisted.");
                    toStateProbing();
                }
            }
        }

        void setOwnMdsType(const DFL::Mdib::CodedValue& mdsType)
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            std::unique_lock<std::mutex> lock{m_mutex};
            if (m_ownMdsType && DFL::Mdib::isSemanticallyEqual(mdsType, *m_ownMdsType))
            {
                m_ownMdsType = mdsType;
                return;
            }

            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Set own mds type to ", mdsType);
            m_ownMdsType = mdsType;

            if (m_state.stateEquals(State::Connected))
            {
                if (!m_currentDevice.device)
                {
                    return;
                }

                const auto mdib = m_currentDevice.device->mdibAccess()->latestMdib();
                if (std::string message; !remoteMdsIsGood(*mdib, message))
                {
                    lock.unlock();
                    disconnectAndStop("Own Mds type changed so that remote Mds type is no longer allowed.");
                    toStateProbing();
                }
            }
        }

        void clearOwnMdsType()
        {
            std::scoped_lock<std::mutex> const lock{m_mutex};
            if (!m_ownMdsType)
            {
                return;
            }

            m_ownMdsType = std::nullopt;
            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Own mds type cleared.");
        }

        void registerObserver(const std::weak_ptr<Sdc::RemoteDevicesObserver>& observer) override
        {
            m_remoteDevicesObservers.registerObserver(observer);
        }

        void unregisterObserver(const std::weak_ptr<Sdc::RemoteDevicesObserver>& observer) override
        {
            m_remoteDevicesObservers.unregisterObserver(observer);
        }

        void joinsLocation(const RemoteDeviceInfo& device) override
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            auto nodeProvider = m_nodeProvider.lock();
            if (!nodeProvider)
            {
                return;
            }

            std::scoped_lock<std::mutex> const lock{m_mutex};

            if (m_state.stateNotEquals(State::Probing))
            {
                return;
            }

            if (m_ownEprForBlacklisting && S31::Sdc::addressEquals(*m_ownEprForBlacklisting, device.endpointReference()))
            {
                return;
            }

            if (m_ownMdsType)
            {
                const auto& types = device.types();
                if (!std::none_of(types.begin(), types.end(), [&](const auto& type)
                {
                    return DFL::Mdib::isSemanticallyEqual(*m_ownMdsType, type);
                }))
                {
                    return;
                }
            }

            m_foundCandidates.push(device);

            if (!m_currentDevice.epr) // no connect is in progress -> trigger connect
            {
                nodeProvider->registerObserver(shared_from_this());
                tryNextCandidate();
            }
        }

        void leavesLocation(const EndpointReference& /*epr*/) override
        {
            // ignore
        }

        // Note: this is the only point to reach the state 'connected'
        void online(const DFL::NotNull<std::shared_ptr<RemoteDevice>>& remoteDevice) override
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            const auto& epr = remoteDevice->endpointReference();
            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Got online for ", epr);
            std::unique_lock<std::mutex> lock{m_mutex};
            if (!m_currentDevice.epr
                || !S31::Sdc::addressEquals(epr, *m_currentDevice.epr)
                || m_state.stateNotEquals(State::Probing))
            {
                return;
            }

            const auto latestMdib = remoteDevice->mdibAccess()->latestMdib();
            if (std::string message; !remoteMdsIsGood(*latestMdib, message) || !remoteLocationIsGood(*latestMdib, message))
            {
                S31_STREAM_TRACE_LOGGER("Sdc.Client", "Disconnect and skip device ", epr, ". ", message);
                tryNextCandidate();
                if (auto deviceProvider = m_nodeProvider.lock())
                {
                    deviceProvider->disconnectFromRemoteDevice(epr);
                }
                return;
            }

            {
                std::weak_ptr<WorkplaceDeviceProviderImpl> const weakThis = shared_from_this();
                auto forwardFunc = [weakThis](const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType)
                {
                    if (auto t = weakThis.lock())
                    {
                        t->onRemoteMdibChange(mdib, changes, changeType);
                    }
                };
                m_remoteMdibObserver = std::make_shared<ForwardingMdibObserver>(forwardFunc);
                remoteDevice->mdibAccess()->registerObserver(m_remoteMdibObserver);
            }

            m_currentDevice.device = remoteDevice.get();
            m_state = State::Connected;
            S31_STREAM_TRACE_LOGGER("Sdc.Client", "WorkplaceDeviceProvider now holds connection to ", epr);

            lock.unlock();
            m_remoteDevicesObservers.notify([&](RemoteDevicesObserver& observer)
            {
               observer.online(remoteDevice);
            });
        }

        // We can end up here while probing or while losing connection to the connected device
        void offline(const EndpointReference& epr, const Utils::Error& error) override
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            std::unique_lock<std::mutex> lock{m_mutex};
            if (!m_currentDevice.epr || !S31::Sdc::addressEquals(epr, *m_currentDevice.epr))
            {
                return;
            }
            S31_STREAM_TRACE_LOGGER("Sdc.Client", epr, " is offline");

            if (m_state.stateEquals(State::Probing))
            {
                S31_STREAM_TRACE_LOGGER("Sdc.Client", "While probing failed to reach ", epr, ". Reason: ", error.message());
                tryNextCandidate();
                return;
            }

            if (m_state.stateNotEquals(State::Connected))
            {
                return;
            }

            m_currentDevice.device = nullptr;
            m_currentDevice.epr = std::nullopt;
            lock.unlock();
            disconnectAndStop("");
            toStateProbing();

            m_remoteDevicesObservers.notify([&](RemoteDevicesObserver& observer)
            {
               observer.offline(epr, error);
            });
        }

        void onLocalMdibChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/, DFL::Mdib::MdibChangeType changeType)
        {
            // for now only changing Mds type is handled

            if (changeType != DFL::Mdib::MdibChangeType::Description)
            {
                return;
            }

            auto mdsEntities = mdib->range<DFL::Mdib::Mds>();
            if (mdsEntities.empty())
            {
                clearOwnMdsType();
                return;
            }
            auto mds = *mdsEntities.begin();
            const auto& mdsDesc = mds->descriptor();
            if (auto mdsType = mdsDesc->type())
            {
                setOwnMdsType(*mdsType);
                return;
            }
            clearOwnMdsType();
        }

        void onRemoteMdibChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& /*changes*/, DFL::Mdib::MdibChangeType changeType)
        {
            if (changeType == DFL::Mdib::MdibChangeType::Description || changeType == DFL::Mdib::MdibChangeType::ContextStates)
            {
                std::unique_lock<std::mutex> lock{m_mutex};
                std::string message{};
                if (!remoteLocationIsGood(*mdib, message))
                {
                    lock.unlock();
                    disconnectAndStop("Location in remote Mdib is not longer good. " + message);
                    toStateProbing();
                    return;
                }
            }

            if (changeType == DFL::Mdib::MdibChangeType::Description)
            {
                std::unique_lock<std::mutex> lock{m_mutex};
                std::string message{};
                if (!remoteMdsIsGood(*mdib, message))
                {
                    lock.unlock();
                    disconnectAndStop("Mds in remote Mdib is not longer good. " + message);
                    toStateProbing();
                }
            }
        }

    private:

        void disconnectAndStop(const std::string& disconnectReason)
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            std::unique_lock<std::mutex> lock{m_mutex};
            if (m_state.stateEquals(State::Stopped))
            {
                return;
            }

            m_locationContextDiscoveryRegistry = nullptr;
            m_state = State::Stopped;

            // If a device is connected -> disconnect it
            if (m_currentDevice.device)
            {
                const auto epr = m_currentDevice.device->endpointReference();
                m_currentDevice.device = nullptr;
                m_currentDevice.epr = std::nullopt;

                if (auto provider = m_nodeProvider.lock())
                {
                    provider->disconnectFromRemoteDevice(epr);
                    auto error = Utils::makeError(Errors::WorkplaceConnectionLost{}, DFL::Locale::Utf8{disconnectReason});
                    lock.unlock();

                    m_remoteDevicesObservers.notify([&](RemoteDevicesObserver& observer)
                    {
                       observer.offline(epr, error);
                    });
                }
            }
        }

        void toStateProbing()
        {
            using namespace WorkplaceDeviceProviderImplHelper;
            std::scoped_lock<std::mutex> const lock{m_mutex};
            if (m_state.stateNotEquals(State::Stopped)
                    || !m_ownLocation)
            {
                return;
            }

            auto discovery = m_discoveryProvider.lock();
            if (!discovery)
            {
                return;
            }

            m_locationContextDiscoveryRegistry =
                    discovery->createLocationContextDiscoveryRegistry(
                        m_ownLocation->detail,
                        DiscoveryTimeout{DFL::Chrono::Seconds{20}},
                        ProbeInterval{DFL::Chrono::Seconds{15}},
                        m_ownEprForBlacklisting);

            m_locationContextDiscoveryRegistry->registerObserver(shared_from_this());

            if (m_ownMdsType)
            {
                m_mdsTypeErrorReporter = std::make_shared<MdsTypeErrorReporter>(*m_ownMdsType);
                m_locationContextDiscoveryRegistry->registerObserver(m_mdsTypeErrorReporter);
            }

            m_locationContextDiscoveryRegistry->reset();

            m_state = State::Probing;
        }

        void tryNextCandidate()
        {
            m_currentDevice.epr = std::nullopt;
            auto nodeProvider = m_nodeProvider.lock();
            if (!nodeProvider)
            {
                return;
            }

            if (m_foundCandidates.empty())
            {
                return;
            }

            auto device = std::move(m_foundCandidates.front());
            m_foundCandidates.pop();
            S31_STREAM_TRACE_LOGGER("Sdc.Client", "Trigger connect to ", device.endpointReference());
            m_currentDevice.epr = device.endpointReference();
            nodeProvider->connectToRemoteDevice(device.endpointReference());
        }

        // Intended to be called while the caller holds the mutex
        bool remoteLocationIsGood(const DFL::Mdib::Mdib& mdib, std::string& notGoodInfo)
        {
            if (!m_ownLocation)
            {
                notGoodInfo = "Own location is not set.";
                return false;
            }

            const auto range = mdib.range<DFL::Mdib::LocationContext>();
            if (range.empty())
            {
                notGoodInfo = "Remote Mdib does not contain location contexts.";
                return false;
            }

            auto associatedContextIt = std::find_if(range.begin(), range.end(), [&](const DFL::NotNull<DFL::Mdib::LocationContextSharedPtr>& context)
            {
                return context->state()->contextAssociation() == DFL::Mdib::ContextAssociation::Associated;
            });

            if (associatedContextIt == range.end())
            {
                notGoodInfo = "Remote Mdib does not contain a associated location context.";
                return false;
            }

            const auto& state = (*associatedContextIt)->state();
            const auto& identifications = state->identifications();

            if (!std::any_of(identifications.begin(), identifications.end(),
                           [this](const auto& identifier)
                           {
                                return DFL::Mdib::referencesSameInstance(identifier, m_ownLocation->identifier) == DFL::Mdib::ReferencesSameInstance::True;
                           }))
            {
                notGoodInfo = "None of the identifiers of the associated location context in the remote Mdib matches.";
                return false;
            }

            if (state->validators().empty())
            {
                notGoodInfo = "The associated location context in the remote Mdib has no validator.";
                return false;
            }
            return true;
        }

        // Intended to be called while the caller holds the mutex
        bool remoteMdsIsGood(const DFL::Mdib::Mdib& mdib, std::string& notGoodInfo) const
        {
            const auto range = mdib.range<DFL::Mdib::Mds>();
            if (range.empty())
            {
                notGoodInfo = "Remote Mdib does not contain a Mds.";
                return false;
            }
            if (++range.begin() != range.end())
            {
                notGoodInfo = "Remote Mdib contains more than one Mds.";
                return false;
            }

            const auto mds = *range.begin();
            const auto type = mds->descriptor()->type();
            if (!type)
            {
                notGoodInfo = "Remote Mdib's Mds has no type.";
                return false;
            }

            if (m_ownMdsType && DFL::Mdib::isSemanticallyEqual(*m_ownMdsType, *type))
            {
                notGoodInfo = "Remote Mdib's Mds type is the same as ours.";
                return false;
            }
            return true;
        }

        std::weak_ptr<S31::Sdc::DiscoveryProvider> m_discoveryProvider;
        std::weak_ptr<S31::Sdc::RemoteDevicesProvider> m_nodeProvider;
        WorkplaceDeviceProviderImplHelper::StateWrapper m_state;
        WorkplaceDeviceProviderImplHelper::CurrentDeviceInfo m_currentDevice;
        Utils::ObservableSubjectDelegate<Sdc::RemoteDevicesObserver> m_remoteDevicesObservers;
        std::optional<WorkplaceDeviceProviderImplHelper::LocationInfo> m_ownLocation;
        std::optional<DFL::Mdib::CodedValue> m_ownMdsType;
        boost::optional<EndpointReference> m_ownEprForBlacklisting;
        std::queue<RemoteDeviceInfo> m_foundCandidates;
        std::shared_ptr<RemoteDevice> m_device;
        std::shared_ptr<LocationContextDiscoveryRegistry> m_locationContextDiscoveryRegistry;
        std::shared_ptr<WorkplaceDeviceProviderImplHelper::ForwardingMdibObserver> m_localMdibObserver;
        std::shared_ptr<WorkplaceDeviceProviderImplHelper::ForwardingMdibObserver> m_remoteMdibObserver;
        std::shared_ptr<MdsTypeErrorReporter> m_mdsTypeErrorReporter;
        std::mutex m_mutex;

};

}
