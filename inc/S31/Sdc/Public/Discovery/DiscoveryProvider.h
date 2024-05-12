#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Sdc/Public/Discovery/DiscoverySubject.h>
#include <S31/Sdc/Public/Discovery/LocationContextDiscovery.h>

#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>

#include <memory>

namespace S31::Sdc
{

/**
 * @brief Central access point to discover devices on the SDC network.
 *
 * @details Before one can decide to connect to a remote device via @ref S31::Sdc::RemoteDevicesProvider
 * it needs to know an endpoint reference. The endpoint reference can be obtained by
 * @ref S31::Sdc::DiscoveryProvider::probeForRemoteDevices() "triggering the SDC
 * discovery process explicitly" or by getting informed on devices joining the network implicitly.
 *
 * Both explicit and implicit discovery results are delivered to @ref S31::Sdc::DiscoveryObserver instances
 * that have been @ref S31::Sdc::DiscoverySubject::registerObserver() "registered" at the %DiscoveryProvider.
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP DiscoveryProvider: public DiscoverySubject
{
    public:
        ~DiscoveryProvider() noexcept override = default;

        /**
         * @name Probe
         * @brief Trigger a remote device search on the network.
         * @details Registered observers will be notified on every device that is found on the network.
         * Either probe for any device or restrict to a Mds type or one location.
         *
         * A registered observer will be notified about matches of any of this probe calls. No checks are done for these notifications,
         * so the user generally has to re-check the device. Suppose that this relies on unsecure WS-Discovery messages.
         */
        ///@{
        /// @brief Trigger a remote device search on the network without scope restrictions.
        virtual void probeForRemoteDevices() = 0;
        /// @brief Trigger a remote device search on the network restricted to a Mds type.
        virtual void probeForRemoteDevices(const DFL::Mdib::CodedValue& mdsType) = 0;
        /// @brief Trigger a remote device search on the network restricted to a location.
        virtual void probeForRemoteDevices(const DFL::Mdib::LocationDetail& location) = 0;
        ///@}

        /**
         * @brief Returns a new @ref LocationContextDiscoveryRegistry.
         *
         * @details
         * Throws if no instance identifier can be made from the location.
         *
         * If a device announces new @ref DFL::Mdib::Mds types in its discovery message, then the registry
         * will notify a @ref LocationContextDiscoveryObserver::leavesLocation() "leaves" -
         * @ref LocationContextDiscoveryObserver::joinsLocation() "joins" - sequence.
         *
         * ### Probe Interval and Discovery Timeout
         * Obviously both parameters are to be used in a connected way. It's recommended that the probe
         * interval is significantly smaller than the discovery timeout, e.g. 30 sec and 60 sec.
         *
         * Also note that the timeout is checked every half of the timeout time. So the the detection
         * of the timeout can be delayed by this time. E.g.: discovery timeout = 60 sec: it may be take up to
         * 90 sec to be notified after the last discovery message was received.
         *
         * @param location The location that the registry will monitor.
         * @param discoveryTimeout if for a device no discovery message was received for this duration then the
         *                         device is considered gone and will be notified as such
         * @param probeInterval probes for devices in this interval
         * @param ignoredEpr one endpoint reference can be configured to be ignored, so a device using this
         *                   registry can exclude itself
         * @returns the registry, or @c nullptr if the registry could not be created.
         */
        virtual std::unique_ptr<LocationContextDiscoveryRegistry> createLocationContextDiscoveryRegistry(
                const DFL::Mdib::LocationDetail& location,
                DiscoveryTimeout discoveryTimeout = DiscoveryTimeout{DFL::Chrono::Seconds{20}},
                ProbeInterval probeInterval = ProbeInterval{DFL::Chrono::Seconds{15}},
                const boost::optional<EndpointReference>& ignoredEpr = boost::none) = 0;
};

}
