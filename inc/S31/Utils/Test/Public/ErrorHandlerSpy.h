#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Utils/Public/Errors.h>

namespace S31::Utils::Test
{

/**
 * @brief Spy/mock for \ref ErrorHandler.
 * @ingroup S31Utils
 */
class ErrorHandlerSpy: public ErrorHandler
{
    public:
        void handleError(const Error& error) override
        {
            m_error = error;
        }

        boost::optional<Error> m_error;
};

}
