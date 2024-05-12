#pragma once

#include <S31/SetService/Public/Client/ClientError.h>

#include <boost/optional/optional.hpp>

namespace S31::SetService::Impl
{
/**
 * @brief Container with result of an set request check.
 * @details Different checks have to be done on client side before sending
 * a set request. For all these client side set service checkers this container
 * provides the result (error code and human readable message).
 * @ingroup S31SetService
 */
class CheckerResult
{
    public:
        static CheckerResult success()
        {
            return {ClientError::NoError, ""};
        }
        static CheckerResult failed(ClientError error, std::string errorMessage)
        {
            return {error, std::move(errorMessage)};
        }

        bool hasError() const noexcept
        {
            return m_clientError != ClientError::NoError;
        }

        /**
         * @brief Error code, shall only be called when in error state.
         */
        ClientError errorCode() const
        {
            return m_clientError;
        }

        const std::string& errorMessage() const noexcept
        {
            return m_errorMessage;
        }
    private:
        CheckerResult(ClientError clientError, std::string errorMessage):
                m_clientError(clientError),
                m_errorMessage(std::move(errorMessage))
        {
        }
        ClientError m_clientError = ClientError::NoError;
        std::string m_errorMessage;
};

}
