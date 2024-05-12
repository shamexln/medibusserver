#pragma once

#include <S31/Sdc/Public/Discovery/DiscoveryObserver.h>
#include <S31/Sdc/Public/Discovery/LocationContextDiscovery.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>

#include <mutex>
#include <map>

namespace S31::Sdc::Impl
{

/**
 * @brief Tracks devices on a location using WS-Discovery.
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP LocationContextDiscoveryTracker: public DiscoveryObserver
{
    public:
        LocationContextDiscoveryTracker(
                const DFL::Mdib::LocationDetail&          location,
                DFL::Chrono::Seconds                      timeout,
                const boost::optional<EndpointReference>& ignore);  // NOLINT(modernize-pass-by-value)

        void foundDevice(const RemoteDeviceInfo& device) override;

        void byeFromDevice(const EndpointReference& epr) override;

        void handleTimedOutDevices();

        void registerObserver(const std::shared_ptr<LocationContextDiscoveryObserver>& observer);
        void unregisterObserver(const std::shared_ptr<LocationContextDiscoveryObserver>& observer);

        void reset();

        std::vector<RemoteDeviceInfo> devices();

    private:
        bool matchesLocation(const RemoteDeviceInfo& deviceInfo) const;

        struct DiscoveredDeviceInfo
        {
                RemoteDeviceInfo remoteDeviceInfo;
                DFL::Chrono::SteadyClock::TimePoint lastUpdate;
        };

        struct EndpointReferenceCompareLess
        {
                bool operator()(const EndpointReference& lhs, const EndpointReference& rhs) const noexcept
                {
                    return lhs.address().str() < rhs.address().str();
                }
        };

        mutable std::mutex m_mutex;
        std::map<EndpointReference, DiscoveredDeviceInfo, EndpointReferenceCompareLess> m_remoteDevices;
        DFL::Mdib::InstanceIdentifier m_location;
        DFL::Chrono::Seconds m_timeout;
        boost::optional<EndpointReference> m_ignoredEpr;
        S31::Utils::ObservableSubjectDelegate<LocationContextDiscoveryObserver> m_locationContextDiscoveryObservers;
};


}
