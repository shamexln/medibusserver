#pragma once

#include <S31/SetService/Public/Client/ClientTransaction.h>

#include <memory>

namespace S31::SetService::Test
{

/**
 * @brief Mock implementation of \ref ClientTransaction.
 * @ingroup S31SetService
 */
class ClientTransactionMock: public ClientTransaction
{
    public:
        ClientTransactionMock() = default;

        ClientTransactionMock(InvocationState finalReportState, ClientInvocationReports latestReport);

        void registerCallback(InvocationState invocationStateToObserve, TransactionCallback callback) override;

        void registerClientFailCallback(ClientErrorCallback callback) override;

        ClientInvocationReports waitForReports(DFL::Chrono::Milliseconds maxWait) const override;

        boost::optional<ClientInvocationReport> waitForSuccess(DFL::Chrono::Milliseconds maxWait) const override;

        boost::optional<ClientError> clientError() const override;

        InvocationState invocationState() const;

        std::optional<ClientSetResponse> invocationResponse() override;

    private:
        InvocationState m_finalReportState = InvocationState::Failed;
        const ClientInvocationReports m_latestReport;
};

inline ClientTransactionMock::ClientTransactionMock(InvocationState finalReportState,
                                                    ClientInvocationReports latestReport) :
        m_finalReportState(finalReportState),
        m_latestReport(std::move(latestReport))
{
}

inline void ClientTransactionMock::registerCallback(InvocationState /*invocationStateToObserve*/, TransactionCallback /*callback*/)
{
}

inline void ClientTransactionMock::registerClientFailCallback(ClientErrorCallback /*callback*/)
{
}

inline ClientInvocationReports ClientTransactionMock::waitForReports(DFL::Chrono::Milliseconds /*maxWait*/) const
{
    return m_latestReport;
}

inline boost::optional<ClientInvocationReport> ClientTransactionMock::waitForSuccess(DFL::Chrono::Milliseconds /*maxWait*/) const
{
    return boost::none;
}

inline boost::optional<ClientError> ClientTransactionMock::clientError() const
{
    return boost::none;
}

inline InvocationState ClientTransactionMock::invocationState() const
{
    return m_finalReportState;
}

inline std::optional<ClientSetResponse> ClientTransactionMock::invocationResponse()
{
    return {};
}
}
