#pragma once

#include <S31/Sdc/Public/Discovery/RemoteDeviceInfo.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::Sdc
{

/**
 * @brief Observer for location context changes of devices in the network.
 * @details To be used together with @ref LocationContextDiscoveryRegistry.
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP LocationContextDiscoveryObserver
{
    public:
        virtual ~LocationContextDiscoveryObserver() = default;

        /**
         * @brief Gets called if a device joins the location.
         */
        virtual void joinsLocation(const RemoteDeviceInfo& device) = 0;

        /**
         * @brief Gets called if a device leaves the location.
         */
        virtual void leavesLocation(const EndpointReference& epr) = 0;
};

struct DiscoveryTimeoutTag;
/**
 * @brief The time after if no discovery message was received, a device is considered gone.
 * @details to be used together with @ref ProbeInterval.
 * @ingroup S31SdcDiscovery
 */
using DiscoveryTimeout = DFL::StrongTypedef<DFL::Chrono::Seconds, DiscoveryTimeoutTag, DFL::Skill::Streamable>;

struct ProbeIntervalTag;
/**
 * @brief The interval in which probe discovery messages are sent.
 * @details To detect silently gone devices. See @ref DiscoveryTimeout.
 * @ingroup S31SdcDiscovery
 */
using ProbeInterval = DFL::StrongTypedef<DFL::Chrono::Seconds, ProbeIntervalTag, DFL::Skill::Streamable>;

/**
 * @brief A Registry that tracks remote devices via WS-Discovery messages.
 * @details Also notifies the observers about @ref DFL::Mdib::Mds type changes through leave and rejoin.
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP LocationContextDiscoveryRegistry
{
    public:
        virtual ~LocationContextDiscoveryRegistry() = default;

        /**
         * @brief Clears the list of devices on the location - which then will be refilled again.
         * @details Can be used when registering an observer to have a clean start.
         */
        virtual void reset() = 0;

        /**
         * @brief Returns all the devices which are currently on the location.
         */
        virtual std::vector<RemoteDeviceInfo> devices() const = 0;

        /**
         * @brief Register an observer that notifies about joining and leaving devices.
         */
        virtual void registerObserver(const std::shared_ptr<LocationContextDiscoveryObserver>& observer) = 0;

        /**
         * @brief Unregistrer an observer.
         */
        virtual void unregisterObserver(const std::shared_ptr<LocationContextDiscoveryObserver>& observer) = 0;
};

}
