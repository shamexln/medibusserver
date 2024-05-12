#pragma once

#include <S31/SetService/Public/Client/ClientInvocationReport.h>
#include <S31/SetService/Public/Client/ClientTransactionWriter.h>

namespace S31::SetService::Test
{
/**
 * @brief Mock implementation of \ref ClientTransactionWriter.
 * @ingroup S31SetService
 */
class ClientTransactionWriterMock: public ClientTransactionWriter
{
    public:
        void doNotifyClientError(ClientError /*clientError*/, const std::string& /*errorMessage*/) override
        {
        }
        void doNotifySetOperationResponse(const ClientSetResponse& /*response*/) override
        {
        }
        void onInvocationReport(const ClientInvocationReport& /*report*/) override
        {
        }
};
}
