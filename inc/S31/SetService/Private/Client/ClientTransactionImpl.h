#pragma once

#include <S31/SetService/Public/Client/ClientInvocationReport.h>
#include <S31/SetService/Public/Client/ClientTransaction.h>
#include <S31/SetService/Public/Client/ClientTransactionWriter.h>

#include <condition_variable>
#include <list>
#include <map>
#include <mutex>
#include <optional>

namespace S31::SetService::Impl
{

/**
 * @brief Default implementation of \ref ClientTransaction.
 * @ingroup S31SetService
 */
class ClientTransactionImpl: public ClientTransaction, public ClientTransactionWriter
{
    public:
        void registerCallback(InvocationState invocationStateToObserve, TransactionCallback callback) override;

        void registerClientFailCallback(ClientErrorCallback callback) override;

        ClientInvocationReports waitForReports(DFL::Chrono::Milliseconds maxWait) const override;

        boost::optional<ClientInvocationReport> waitForSuccess(DFL::Chrono::Milliseconds maxWait) const override;

        boost::optional<ClientError> clientError() const override;

        void doNotifyClientError(ClientError clientError, const std::string& errorMessage) override;

        void doNotifySetOperationResponse(const ClientSetResponse& response) override;

        void onInvocationReport(const ClientInvocationReport& invocationReport) override;

        std::optional<ClientSetResponse> invocationResponse() override;

        /**
         * @brief In case of a client error it provides human readble information.
         */
        const std::string& clientErrorMessage() const;
    private:
        mutable std::mutex m_callbackMutex;
        std::map<InvocationState, TransactionCallback> m_invocationReportCallbacks;
        ClientErrorCallback m_clientFailCallback;

        mutable std::mutex m_reportMutex;
        mutable std::condition_variable m_reportCondition;

        boost::optional<TransactionId> m_transactionId;
        boost::optional<ClientError> m_clientError;
        std::string m_clientErrorMessage;
        boost::optional<ClientError> m_pendingClientError;
        ClientInvocationReports m_invocationReports;
        ClientInvocationReports m_bufferedInvocationReports;
        std::map<InvocationState, ClientInvocationReport> m_pendingInvocationReports;
        bool m_hasFinalReport = false;

        // std::list used for queue to ensure reference to front element is not invalidated when pushing to back
        std::list<ClientInvocationReport> m_reportsQueuedForCallback;
        std::optional<ClientSetResponse> m_invocationResponse;
        bool m_callbacksAreRunning = false;

        void wakeUpReportCallFromClientError(ClientError clientError);
        void invokeClientErrorCallback(ClientError clientError);

        void invokeAvailableInvocationReportCallbacks();
        void invokeInvocationReportCallback(const ClientInvocationReport& invocationReport);

        void wakeUpReportCallFromInvocationReportNoLock(const ClientInvocationReport& invocationReport);
        void wakeUpCallFromSetOperationResponseNoLock(const ClientSetResponse& response);
        bool isInvocationReportAcceptableNoLock(const ClientInvocationReport& newInvocationReport) const;

        void handleBufferedInvocationReportsNoLock();
};

}
