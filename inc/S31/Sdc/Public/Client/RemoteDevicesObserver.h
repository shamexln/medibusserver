#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Utils/Public/Errors.h>

#include <memory>

namespace S31::Sdc
{

/**
 * @brief   %RemoteDevicesObserver is used to track remote SDC devices joining and leaving the network.
 * @details Whenever \ref S31::Sdc::RemoteDevicesProvider connects or disconnects to a device, it will notify
 *          registered observers by using %RemoteDevicesObserver.
 *
 *          Use \ref S31::Sdc::RemoteDevicesProvider::registerObserver() and
 *          \ref S31::Sdc::RemoteDevicesProvider::unregisterObserver() to subscribe/unsubscribe
 *          for callbacks provided by %RemoteDevicesObserver.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP RemoteDevicesObserver
{
    public:
        virtual ~RemoteDevicesObserver() = default;

        /**
         * @brief   Online callback for a remote device.
         * @details If an implementation of this interface is registered via
         *          \ref S31::Sdc::RemoteDevicesProvider::registerObserver(), it will receive a
         *          reference to the remote device that goes online..
         *
         *          A remote device is notified as online as soon as the following preconditions are
         *          fulfilled:
         *          - The connection process was explicitly triggered by
         *            S31::Sdc::RemoteDevicesProvider::connectToRemoteDevice()
         *          - The remote device was authenticated properly
         *          - The MDIB of the remote device has been fetched
         *          - Event reports are subscribed according to the given input set.
         */
        virtual void online(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice) = 0;

        /**
         * @brief   Offline callback for a remote device with enclosing error information.
         * @details If an implementation of this interface is registered via
         *          \ref S31::Sdc::RemoteDevicesProvider::registerObserver(), it will receive the endpoint reference
         *          of a remote device that has gone offline.
         *
         *          After an endpoint reference is announced as offline, the behavior of any interaction with
         *          the corresponding remote device is undefined.
         *
         *          A remote device is notified as offline as soon as the following preconditions are
         *          fulfilled:
         *
         *          - An error occurred from where the remote device cannot correctly be restored
         *          - A disconnection process was explicitly triggered by
         *            \ref S31::Sdc::RemoteDevicesProvider::disconnectFromRemoteDevice()
         *
         * @param epr The endpoint reference of the remote device that has gone offline.
         * @param error A reason for offline encoded as an error. If \ref S31::Sdc::RemoteDevicesProvider::disconnectFromRemoteDevice()
         *        was invoked without specifying a reason, the argument matches \ref S31::Sdc::Errors::UserDisconnected.
         */
        virtual void offline(const EndpointReference& epr, const S31::Utils::Error& error) = 0;
};

}
