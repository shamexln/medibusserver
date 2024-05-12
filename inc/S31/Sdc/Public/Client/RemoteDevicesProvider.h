#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Public/Client/MdibSubscriptionType.h>
#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <S31/Sdc/Public/Client/RemoteDevicesSubject.h>
#include <S31/Sdc/Public/Client/SubscriptionReports.h>

#include <memory>
#include <string>

namespace S31::Sdc
{

/**
 * @brief Central access point to connect and disconnect remote devices.
 *
 * @details
 * For one endpoint reference there is at most one remote device (see @ref remoteDevice()). Triggering 'connect' on an already connected device
 * has no effect. This also holds if 'connect' was triggered but the connection is not fully established yet.
 *
 * If 'disconnect' for a connected device was triggered then a new 'connect' is only possible if 'Offline' was notified. Generally it is possible to
 * connect to an endpoint reference within an 'Offline' notification about the same endpoint reference (e.g. to try to repair a broken connection).
 *
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP RemoteDevicesProvider: public RemoteDevicesSubject
{
    public:
        ~RemoteDevicesProvider() override = default;

        /**
         * @brief Starts to connect to a remote device.
         * @details Calls \ref S31::Sdc::RemoteDevicesObserver::online() if a connection could be established.
         */
        virtual void connectToRemoteDevice(const EndpointReference& endpointReference) = 0;

        /**
         * @brief Starts to asynchronously connect to a remote device by subscribing to the specified set of reports.
         * @details Calls \ref S31::Sdc::RemoteDevicesObserver::online() if a connection could be established.
         * @deprecated This function is deprecated, becaus it relies on different BICEPS service types instead of MDIB
         * changes. The benefit is relatively low and the new over load with @ref SubscriptionReports provides a better
         * solution to skip metric reports for example, which is not possible with this solution.
         *
         * @param endpointReference The remote device's endpoint reference to connect to.
         * @param subscriptions A set of MDIB subscriptions the user is interested in. Please note that description and
         *                      context updates are always subscribed regardless of their presence in the subscriptions set.
         */
        virtual void connectToRemoteDevice(const EndpointReference& endpointReference,
                                           const MdibSubscriptionTypes& subscriptions) = 0;

        /**
         * @brief Starts to asynchronously connect to a remote device by subscribing to the specified set of reports.
         * @details Calls \ref S31::Sdc::RemoteDevicesObserver::online() if a connection could be established.
         * @param endpointReference The remote device's endpoint reference to connect to.
         * @param reports An enum value specifying a useful set of MDIB change reports.
         */
        virtual void connectToRemoteDevice(const EndpointReference& endpointReference, SubscriptionReports reports);

        /**
         * @brief Starts to disconnect from a connected device.
         * @details Calls \ref S31::Sdc::RemoteDevicesObserver::offline() once the operation is finished.
         */
        virtual void disconnectFromRemoteDevice(const EndpointReference& endpointReference) = 0;

        /**
         * @brief Waits until the remote device with the given endpoint reference is connected.
         * @param endpointReference Identifier of the remote device to wait for.
         * @param waitTime Timeout in milliseconds to wait for the remote device.
         * @return Returns \c nullptr if device was not found within waitTime, otherwise a valid pointer.
         */
        virtual std::shared_ptr<RemoteDevice> waitForRemoteDevice(const EndpointReference& endpointReference, DFL::Chrono::Milliseconds waitTime) = 0;

        /**
         * @brief Returns a %RemoteDevice instance.
         * @return Returns pointer to the remote device with \c endpointReference if existing, otherwise \c nullptr.
         */
        virtual std::shared_ptr<RemoteDevice> remoteDevice(const EndpointReference& endpointReference) = 0;
};

inline void
RemoteDevicesProvider::connectToRemoteDevice(const EndpointReference& /*endpointReference*/, SubscriptionReports /*reports*/)
{
    // no default implementation
}
}
