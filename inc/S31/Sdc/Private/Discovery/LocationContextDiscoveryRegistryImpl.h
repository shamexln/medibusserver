#pragma once

#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Discovery/LocationContextDiscoveryTracker.h>
#include <S31/Sdc/Public/Discovery/DiscoveryProvider.h>
#include <S31/Sdc/Public/Discovery/LocationContextDiscovery.h>


namespace S31::Sdc::Impl
{

/**
 * @brief Implementation of The Location Context Discovery Registry.
 * @details
 * ### Features
 * - probes for devices in the configured interval
 * - checks timeout: if for a device no discovery message was received with the configured duration then the
 *   device is considered gone and will be notified as such
 * - one endpoint reference can be configured to be ignored, so a device using this registry
 *   can exclude itself
 *
 * @ingroup S31SdcDiscovery
 */
class LocationContextDiscoveryRegistryImpl: public LocationContextDiscoveryRegistry
{
    public:
        LocationContextDiscoveryRegistryImpl(
                DFL::NotNull<std::shared_ptr<S31::Sdc::DiscoveryProvider>> discovery,
                DFL::NotNull<std::shared_ptr<Impl::IScheduling>> scheduling,
                const DFL::Mdib::LocationDetail& location,
                DiscoveryTimeout discoveryTimeout,
                ProbeInterval probeInterval,
                const boost::optional<EndpointReference>& ignoredEpr);

        void reset() override;
        std::vector<RemoteDeviceInfo> devices() const override;

        void registerObserver(const std::shared_ptr<LocationContextDiscoveryObserver>& observer) override;
        void unregisterObserver(const std::shared_ptr<LocationContextDiscoveryObserver>& observer) override;

    private:
        DiscoveryTimeout m_discoveryTimeout;
        DFL::NotNull<std::shared_ptr<LocationContextDiscoveryTracker>> m_tracker;
};

}
