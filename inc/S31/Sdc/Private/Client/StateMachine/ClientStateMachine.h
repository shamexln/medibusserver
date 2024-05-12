#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Public/Client/MdibSubscriptionType.h>
#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/Utils/Public/ObservableSubject.h>


namespace S31::Sdc::Impl::Csm
{

/**
 * @brief Observer interface to listen for any events fired by a client state machine.
 * @ingroup S31SdcClient
 */
class ClientStateMachineObserver
{
    public:
        virtual ~ClientStateMachineObserver() noexcept = default;

        /**
         * @brief Notified if remote device is not longer available for interaction.
         * @param epr The endpoint reference of the remote device that has gone offline.
         * @param error A reason why offline was triggered.
         */
        virtual void offline(const EndpointReference& epr, const Utils::Error& error) = 0;

        /**
         * @brief Notified if remote device is available for interaction.
         * @param epr The endpoint reference of the remote device that has gone online.
         * @param remoteDevice A shared resource to access remote device functionality.
         */
        virtual void online(const EndpointReference& epr, const DFL::NotNull<std::shared_ptr<RemoteDevice>>& remoteDevice) = 0;
};

/**
 * @brief Defines a state machine interface to orchestrate the connection process for \ref S31::Sdc::RemoteDevice "remote devices".
 * @details The client state machine looks like depicted in the following picture.
 *
 * @startuml
 * !include S31Sdc-ClientStateMachine.iuml
 * @enduml
 *
 * The state machine starts in an *Offline* state. If a \ref ClientStateMachine::connect "connection is triggered", a multi-step process is initiated
 * that ends up in an *Online* state. Being in the *Online* state, at any time you can either \ref ClientStateMachine::disconnect "disconnect" or
 * \ref ClientStateMachine::handleError "throw an error" to stop the state machine.
 *
 * \attention The state machine is thread-safe. Only after a new state is reached the next event is accepted.
 *            There is no queuing implemented at the moment!
 *
 * @ingroup S31SdcClient
 */
class ClientStateMachine: public Utils::ObservableSubject<ClientStateMachineObserver>, public Utils::ErrorHandler
{
    public:
        ~ClientStateMachine() override = default;

        /**
         * @brief Starts to connect a remote device.
         * @details \note Asynchronous call - function will return immediately.
         * @param mdibChangeReports The SOAP actions for the MDIB Subscribe request.
         */
        virtual void connect(const SoapActions& mdibChangeReports) = 0;

        /**
         * @brief Disconnects from a connected remote device.
         * @details \attention The %ClientStateMachine forms the context for Unsubscribe requests. Do not destroy the state machine until proper disconnect event is notified.
         *          \note Asynchronous call - function will return immediately.
         * @param error Reason for disconnect.
         */
        virtual void disconnect(const Utils::Error& error) = 0;

        /**
         * @brief Triggers a revalidation of the connected \ref S31::Sdc::Impl::Endpoint::DpwsEndpoint "DPWS endpoint".
         */
        virtual void validate() = 0;

        /**
         * @brief Returns the resolved remote device if existing or \c nullptr ohterwise.
         */
        virtual std::shared_ptr<RemoteDevice> remoteDevice() const = 0;

        /**
         * @brief Invalidates the state machine.
         * @details Any error that is handed over here prevails on the %ClientStateMachine to go into a terminating state and forwards the error given to all subscribers.
         */
        void handleError(const Utils::Error& error) override = 0;

        /**
         * @brief Register for any events fired by %ClientStateMachine.
         */
        void registerObserver(const std::weak_ptr<ClientStateMachineObserver>& observer) override = 0;

        /**
         * @brief Unregister any events fired by %ClientStateMachine.
         */
        void unregisterObserver(const std::weak_ptr<ClientStateMachineObserver>& observer) override = 0;
};

}
