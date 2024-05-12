#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesSubject.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc
{
class DiscoveryProvider;
class RemoteDevicesProvider;

namespace Impl
{
class WorkplaceDeviceProviderImpl;

/**
 * @brief The WorkplaceDeviceProvider(WPDP) connects with one workplace device.
 * @details
 * Based on WS-Discovery messages the WPDP connects a suiting device by location.
 * Generally:
 * - at one time at most one device is connected
 * - if connection to this device is lost, the class starts again looking for another device
 * - if the remote device's Mds type or count changes the WPDP disconnects the device
 * - if own location changes a connected device will be disconnected
 * - devices can be blocked for connection by giving the own EPR and the own Mds type
 * - if an own local Mdib access given, the own Mds type will be tracked by the WPDP
 * - if own Mds type is given the WPDP will also set a RemoS code for duplicate devices on own
 *   location if such devices are discovered
 */
class S31_CORE_EXPIMP WorkplaceDeviceProvider: public S31::Sdc::RemoteDevicesSubject
{
    public:
        WorkplaceDeviceProvider(std::weak_ptr<Sdc::DiscoveryProvider> discoveryProvider,
                                std::weak_ptr<Sdc::RemoteDevicesProvider> nodeProvider,
                                const std::shared_ptr<DFL::Mdib::MdibAccess>& localMdibAccess);

        void setOwnLocation(const DFL::Mdib::LocationDetail& location);
        void clearOwnLocation();

        void setOwnMdsType(const DFL::Mdib::CodedValue& mdsType);
        void clearOwnMdsType();

        void blacklistOwnEpr(const EndpointReference& epr);

        void registerObserver(const std::weak_ptr<Sdc::RemoteDevicesObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<Sdc::RemoteDevicesObserver>& observer) override;

    private:
        std::shared_ptr<WorkplaceDeviceProviderImpl> m_impl;
};


}
}
