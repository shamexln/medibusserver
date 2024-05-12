#pragma once

#include <S31/Sdc/Private/Client/SetService/SetOperationBaseJob.h>
#include <S31/Utils/Public/Outcome.h>

namespace S31Test::Sdc
{
class SetOperationResultMock:
            public S31::Utils::OutcomeConsumer<SetOperationResultMock, S31::Sdc::Impl::SetOperationJobResult>,
            public std::enable_shared_from_this<SetOperationResultMock>
{
    public:
        S31::Utils::OutcomeConsumer<SetOperationResultMock, S31::Sdc::Impl::SetOperationJobResult>::HandlerPtr makeHandler()
        {
            auto handler = makeOutcomeHandler([this](S31::Utils::Outcome<S31::Sdc::Impl::SetOperationJobResult>& outcome)
            {
                if (outcome.hasError())
                {
                    m_error = outcome.error();
                }
                else
                {
                    m_error = boost::none;
                }

            });

            return handler;
        }

        bool hasError() const
        {
            if (m_error)
            {
                return true;
            }
            return false;
        }
    private:
        boost::optional<S31::Utils::Error> m_error;
};

}
