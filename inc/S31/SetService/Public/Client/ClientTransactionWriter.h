#pragma once

#include <S31/SetService/Public/Client/ClientError.h>
#include <S31/SetService/Public/Client/InvocationReportObserver.h>

namespace S31::SetService
{

class ClientInvocationReport;

/**
 * @brief Enables to write client errors and receive invocation reports.
 * @ingroup S31SetService
 */
class ClientTransactionWriter: public InvocationReportObserver
{
    public:
        /**
         * @brief Communicates a local appearing client error to a \ref ClientTransaction.
         */
        void notifyClientError(ClientError clientError, const std::string& errorMessage);

        /**
         * @brief Communicates an AbstractSetResponse (including the TransactionId) to a \ref ClientTransaction
         */
        void notifySetOperationResponse(const ClientSetResponse& response);


    private:
        virtual void doNotifyClientError(ClientError clientError, const std::string& errorMessage) = 0;
        virtual void doNotifySetOperationResponse(const ClientSetResponse& response) = 0;
};

inline void ClientTransactionWriter::notifyClientError(ClientError clientError, const std::string& errorMessage)
{
    doNotifyClientError(clientError, errorMessage);
}

inline void ClientTransactionWriter::notifySetOperationResponse(const ClientSetResponse& response)
{
    doNotifySetOperationResponse(response);
}

}
