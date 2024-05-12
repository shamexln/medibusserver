#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionManager.h>
#include <S31/Sdc/Private/Client/Endpoint/DpwsEndpoint.h>
#include <S31/Sdc/Private/Client/StateMachine/ClientStateMachine.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Discovery/IDpwsDiscoverySubject.h>
#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/Sdc/Public/Client/MdibSubscriptionType.h>
#include <S31/Sdc/Public/Client/RemoteDevicesSubject.h>
#include <S31/Sdc/Public/Client/SubscriptionReports.h>
#include <S31/Sdc/Public/Common/InstanceIdentifiersUtil.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Chrono/Public/Duration.h>

#include <condition_variable>
#include <map>
#include <mutex>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Hosts client state machines and manages their life cycle.
 * @details Moreover, provides a function to \ref ClientStateMachineRegistry::remoteDevice() "retrieve existing remote devices".
 * @ingroup S31SdcClient
 */
class ClientStateMachineRegistry:
        public Endpoint::DpwsEndpointObserver,
        public Csm::ClientStateMachineObserver,
        public std::enable_shared_from_this<ClientStateMachineRegistry>,
        public RemoteDevicesSubject
{
    public:
        /**
         * @brief Class to facilitate mocking of client state machines and DPWS endpoints.
         */
        class InstanceFactory
        {
            public:
                InstanceFactory() = default;
                InstanceFactory(std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue> outgoingJobQueue,
                                std::weak_ptr<Sdc::Impl::IScheduling> scheduling,
                                std::weak_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject> discoverySubject,
                                std::weak_ptr<S31::Sdc::Impl::DpwsSubscriptionManager> dpwsSubscriptionManager,
                                std::set<std::string> supportedUriSchemes);
                virtual ~InstanceFactory() = default;

                virtual DFL::NotNull<std::unique_ptr<Csm::ClientStateMachine>> createClientStateMachine(
                    const EndpointReference& endpointReference,
                    const DeviceMetadata& metadata,
                    const S31::Nomenclature::Credentials& credentials,
                    const std::map<ServiceId, Endpoint::HostedServiceExecutor>& executors,
                    DFL::NotNull<std::shared_ptr<Endpoint::DpwsEndpoint>> dpwsEndpoint,
                    const boost::optional<DFL::Mdib::InstanceIdentifier>& expectedLocation) const;

                virtual DFL::NotNull<std::unique_ptr<Endpoint::DpwsEndpoint>> createDpwsEndpoint(
                    const EndpointReference& endpointReference,
                    ConnectionPriorityGroup priorityGroup) const;

            private:
                std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue> m_outgoingJobQueue;
                std::weak_ptr<Sdc::Impl::IScheduling> m_scheduling;
                std::weak_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject> m_discoverySubject;
                std::weak_ptr<S31::Sdc::Impl::DpwsSubscriptionManager> m_dpwsSubscriptionManager;
                std::set<std::string> m_supportedUriSchemes;
        };

        /**
         * @brief Constructs a %ClientStateMachineRegistry with default instance factory.
         */
        ClientStateMachineRegistry(const std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue>& outgoingJobQueue,
                                   const std::weak_ptr<S31::Sdc::Impl::IScheduling>& scheduling,
                                   const std::weak_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject>& discoverySubject,
                                   const std::weak_ptr<S31::Sdc::Impl::DpwsSubscriptionManager>& dpwsSubscriptionManager,
                                   std::set<std::string> supportedUriSchemes);

        /**
         * @brief Sends a \ref S31::Sdc::Errors::Shutdown offline error for all connected remote devices without disconnecting beforehand.
         * @details If you want to perform a graceful shutdown, invoke \ref ClientStateMachineRegistry::disconnect() in advance.
         */
        ~ClientStateMachineRegistry() noexcept override;

        /**
         * @brief Constructs a %ClientStateMachineRegistry with given instance factory.
         */
        explicit ClientStateMachineRegistry(DFL::NotNull<std::unique_ptr<ClientStateMachineRegistry::InstanceFactory>> instanceFactory);

        /**
         * @brief Starts connection process if none is running.
         * @details - If at the same time a disconnect is running, the connect is postponed until the disconnect is finished
         *          - If subsequent disconnects/connects are triggered, the last action always "wins"
                    - priorityGroup configures a connection delay, allowing clients to connect to a device in priority order
         */
        void connect(const EndpointReference& endpointReference,
                     ConnectionPriorityGroup priorityGroup);

        /**
         * @brief Starts connection process if none is running including the given subscriptions.
         * @details The connect with given subscriptions does only take effect if no connection
         *          is ongoing
         * @see ClientStateMachineRegistry::connect(const EndpointReference& endpointReference)
         */
        void connect(const EndpointReference& endpointReference,
                     const MdibSubscriptionTypes& mdibSubscriptions,
                     ConnectionPriorityGroup priorityGroup);

        /**
         * @brief Starts connection process if none is running including the given subscriptions.
         * @details The connect with given subscriptions does only take effect if no connection
         *          is ongoing
         * @see ClientStateMachineRegistry::connect(const EndpointReference& endpointReference)
         */
        void
        connect(const EndpointReference& endpointReference,
                SubscriptionReports      reports,
                ConnectionPriorityGroup  priorityGroup);

        /**
         * @brief Resolves a vector of all connected devices.
         */
        std::vector<DFL::NotNull<std::shared_ptr<RemoteDevice>>> connectedDevices() const;

        /**
         * @brief Starts disconnection process if none is running.
         * @details If there was a connect triggered meanwhile, the connection process is started right after disconnect is finished.
         */
        void disconnect(const EndpointReference& endpointReference, const Utils::Error& error);

        /**
         * @brief Gracefully disconnects all remote devices.
         * @details Gracefully means that \ref ClientStateMachineRegistry::disconnect() is called on every connected remote device.
         *          \note Please not that \c disconnectAll() is an asynchronous call
         * @return A sequence of all devices that are affected.
         */
        std::vector<DFL::NotNull<std::shared_ptr<RemoteDevice>>> disconnectAll();

        /**
         * @brief Disconnects all remote devices.
         * @details Is also called on destruction.
         *          - Sends an offline without calling \ref ClientStateMachineRegistry::disconnect()
         *          - Empties connecting, disconnecting and active client state machines
         *          - Keeps running subscriptions untouched
         */
        void tearDown();

        /**
         * @brief Revalidates a DPWS endpoint.
         * @details Tries to \ref S31::Sdc::Impl::Endpoint::DpwsEndpoint::validate() "revalidate" the
         *          DPWS endpoint that matches the given endpoint reference.
         */
        void revalidate(const EndpointReference& endpointReference);

        /**
         * @brief Changes the expected location in order to allow expedited reject during connection.
         * @details - If \c boost::none is given, every location is considered a match.
         *          - The location only applies to newly connected remote devices. Existing connections remain untouched.
         */
        void expectedLocation(boost::optional<DFL::Mdib::InstanceIdentifier>&& expectedLocation);

        /**
         * @brief Changes the expected location in order to allow expedited reject during connection.
         * @details - If \c boost::none is given, every location is considered a match.
         *          - The location only applies to newly connected remote devices. Existing connections remain untouched.
         */
        void expectedLocation(const boost::optional<DFL::Mdib::InstanceIdentifier>& expectedLocation);

        /**
         * @brief Starts listening for devices getting online.
         * @details - Immediately returns with a remote device if the device is already online.
         *          - Waits for a device getting online until waitTime is over and returns either
         *            the remote device on success, \c nullptr otherwise
         */
        std::shared_ptr<RemoteDevice> waitForRemoteDevice(const EndpointReference& endpointReference,
                                                          DFL::Chrono::Milliseconds waitTime = DFL::Chrono::Milliseconds(5000));

        /**
         * @brief Returns remote device if existing, \c nullptr otherwise.
         */
        std::shared_ptr<RemoteDevice> remoteDevice(const EndpointReference& endpointReference) const;

        // Overridden methods from RemoteDevicesSubject
        void registerObserver(const std::weak_ptr<RemoteDevicesObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<RemoteDevicesObserver>& observer) override;


        // Overridden methods from Endpoint::DpwsEndpointObserver
        void invalid(const EndpointReference& endpointReference, const S31::Utils::Error& error) override;
        void resolved(const EndpointReference& endpointReference, const std::vector<Endpoint::Url>& urls) override;
        void valid(const EndpointReference& endpointReference, const DeviceMetadata& metadata, const S31::Nomenclature::Credentials& credentials, const std::map<ServiceId, Endpoint::HostedServiceExecutor>& executors) override;

        // Overridden methods from Csm::ClientStateMachineObserver
        void offline(const EndpointReference& endpointReference, const Utils::Error& error) override;
        void online(const EndpointReference& endpointReference, const DFL::NotNull<std::shared_ptr<RemoteDevice>>& remoteDevice) override;

    private:
        template<class T_Value>
        struct BucketItem
        {
            struct Params
            {
                    SoapActions mdibChangeReports;
            };

            DFL::NotNull<std::shared_ptr<T_Value>> value;
            Params params;
        };

        // Use std::string for map key as Endpoint Reference / Uri comparison is unclear at the moment
        using EndpointReferenceAddressString = std::string;

        // Declare bucket to hold existing DPWS endpoints
        using DpwsEndpointBucket = std::map<EndpointReferenceAddressString, BucketItem<Endpoint::DpwsEndpoint>>;

        // Declare buckets to hold client state machines in different stages of connection
        using ClientStateMachineMap = std::map<EndpointReferenceAddressString, BucketItem<Csm::ClientStateMachine>>;

        // State machine is waiting for connection
        using WaitingStateMachineBucket = ClientStateMachineMap;

        // State machine is connecting
        using ConnectingStateMachineBucket = ClientStateMachineMap;

        // State machine is connected
        using ActiveStateMachineBucket = ClientStateMachineMap;

        // State machine is waiting for disconnect or disconnecting
        using DisconnectingStateMachineBucket = ClientStateMachineMap;



        DFL::NotNull<std::unique_ptr<InstanceFactory>> m_instanceFactory;

        mutable std::mutex m_waitForDeviceMutex;
        mutable std::condition_variable m_waitForDeviceCondition;

        mutable std::mutex m_bucketMutex;

        DpwsEndpointBucket m_dpwsEndpoints;

        WaitingStateMachineBucket m_waitingStateMachines;
        ConnectingStateMachineBucket m_connectingStateMachines;
        ActiveStateMachineBucket m_activeStateMachines;
        DisconnectingStateMachineBucket m_disconnectingStateMachines;

        boost::optional<DFL::Mdib::InstanceIdentifier> m_expectedLocation;

        Utils::ObservableSubjectDelegate<Sdc::RemoteDevicesObserver> m_observable;

        std::set<EndpointReferenceAddressString> m_pendingRevalidation;

        void
        connect(const EndpointReference& endpointReference,
                SoapActions              mdibChangeReports,
                ConnectionPriorityGroup  priorityGroup);

        bool hasWaitingStateMachine(const EndpointReference& endpointReference) const;

        bool hasConnectingStateMachine(const EndpointReference& endpointReference) const;

        bool hasActiveStateMachine(const EndpointReference& endpointReference) const;

        bool hasDisconnectingStateMachine(const EndpointReference& endpointReference) const;

        bool hasDpwsEndpoint(const EndpointReference& endpointReference) const;

        // returns true if validation was started, false otherwise
        template<class T_Map>
        bool revalidateIfPending(T_Map& source, const EndpointReference& endpointReference);

        static std::vector<DFL::NotNull<std::shared_ptr<RemoteDevice>>> convertToRemoteDevices(const ClientStateMachineMap& clientStateMachines);
        void tearDownNoLock(const std::vector<DFL::NotNull<std::shared_ptr<RemoteDevice>>>& remoteDevices);
};

}
