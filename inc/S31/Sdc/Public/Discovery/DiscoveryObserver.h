#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Sdc/Public/Discovery/RemoteDeviceInfo.h>

namespace S31::Sdc
{

/**
 * @brief Observer to receive information about remote devices.
 * @details The information that is received on @ref DiscoveryObserver::foundDevice() can be used
 * to ultimately connect to a remote device by using @ref S31::Sdc::RemoteDevicesProvider.
 *
 * When using @ref byeFromDevice() it should be considered that this notification is based an a
 * unreliable/unencrypted multicast message.
 *
 * @note
 * The information that is conveyed on @ref DiscoveryObserver::foundDevice() is announced by the
 * @ref S31::Sdc::DiscoveryProvider "discovery provider" without any further communication to the remote device.
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP DiscoveryObserver
{
    public:
        virtual ~DiscoveryObserver() = default;

        /**
         * @brief Callback that is invoked once a remote device has been found either by explicit (probe) or implicit (hello) means of discovery.
         */
        virtual void foundDevice(const RemoteDeviceInfo& device) = 0;

        /**
         * @brief Callback that is invoked if a WS-Discovery @c bye message is received.
         */
        virtual void byeFromDevice(const EndpointReference& device) = 0;
};

}
