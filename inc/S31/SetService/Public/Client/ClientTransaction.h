#pragma once

#include <S31/SetService/Public/Client/ClientError.h>
#include <S31/SetService/Public/Client/ClientInvocationReport.h>
#include <S31/SetService/Public/Common/InvocationState.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <optional>

namespace S31::SetService
{

/**
 * @brief A callback that is invoked when a new invocation reports comes in.
 * @ingroup S31SetService
 */
using TransactionCallback = std::function<void (const ClientInvocationReport &)>;

/**
 * @brief A callback that is invoked when a client error occurs.
 * @ingroup S31SetService
 */
using ClientErrorCallback = std::function<void (const ClientError &)>;

/**
 * @brief Transaction context on the client side.
 * @ingroup S31SetService
 */
class ClientTransaction
{
    public:
        virtual ~ClientTransaction() = default;

        /**
         * @brief Registers a callback for a specific invocation state.
         */
        virtual void registerCallback(InvocationState invocationStateToObserve, TransactionCallback callback) = 0;

        /**
         * @brief Registers callback for any received success invocation report.
         * @details Enclosed invocation states:
         *
         * - \ref InvocationState::Finished
         * - \ref InvocationState::FinishedWithModification
         */
        virtual void registerSuccessCallback(const TransactionCallback& callback);

        /**
         * @brief Registers callback for any received unsuccessful invocation report.
         *  @details Enclosed invocation states:
         *
         * - \ref InvocationState::Cancelled
         * - \ref InvocationState::CancelledManually
         * - \ref InvocationState::Failed
         */
        virtual void registerFailCallback(const TransactionCallback& callback);

        /**
         * @brief Registers callback for any received client errors.
         * @details Client errors occur are caught on the client side whereas other errors are created by the device and received from the network. Hence,
         * client errors possess no transaction identifier.
         */
        virtual void registerClientFailCallback(ClientErrorCallback callback) = 0;

        /**
         * @brief Returns received reports.
         * @details
         * - If a final report is received before \c maxWait expires, then the function immediately returns all received reports.
         * - If no final report is received before \c maxWait expires, then the function returns all reports that have been received within \c maxWait
         *   no matter whether it is a final or an intermediate report.
         */
        virtual ClientInvocationReports waitForReports(DFL::Chrono::Milliseconds maxWait) const = 0;

        /**
         * @brief Returns a successful invocation report or a boost::none on timeout
         * @details
         * - If a success result is received before \c maxWait expires, then the function returns the last \ref ClientInvocationReport
         * - If no successful result is received before \c maxWait expires, then the function returns a boost::none
         */
        virtual boost::optional<ClientInvocationReport> waitForSuccess(DFL::Chrono::Milliseconds maxWait) const = 0;

        /**
         * @brief Returns a client error if existing.
         * @details Can be called after \ref ClientTransaction::waitForReports() returned an empty list to see if there was a problem at the client side.
         */
        virtual boost::optional<ClientError> clientError() const = 0;

        /**
        * @brief Returns the Invocation Response
        * 
        * @return std::optional<ClientInvocationReport> The InvocationResponse.
        */
        virtual std::optional<ClientSetResponse> invocationResponse() = 0;
};

inline void ClientTransaction::registerSuccessCallback(const TransactionCallback& callback)
{
    registerCallback(InvocationState::Finished, callback);
    registerCallback(InvocationState::FinishedWithModification, callback);
}

inline void ClientTransaction::registerFailCallback(const TransactionCallback& callback)
{
    registerCallback(InvocationState::Cancelled, callback);
    registerCallback(InvocationState::CancelledManually, callback);
    registerCallback(InvocationState::Failed, callback);
}

}
