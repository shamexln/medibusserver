#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/Jobs/GetMdibJob.h>
#include <S31/Sdc/Private/Client/RemoteMdibAccessSmartPtrTypes.h>
#include <S31/Utils/Public/Outcome.h>

namespace S31Test::Sdc
{

/**
 * @brief Class to generate a Handler for a \ref S31::Sdc::Impl::GetMdibJob for easy access to the resulting \ref S31::Sdc::Impl::GetMdibJobResult.
 */
class GetMdibOutcomeConsumer:
            public S31::Utils::OutcomeConsumer<GetMdibOutcomeConsumer, S31::Sdc::Impl::GetMdibJobResult>,
            public std::enable_shared_from_this<GetMdibOutcomeConsumer>
{
    public:
        S31::Utils::OutcomeConsumer<GetMdibOutcomeConsumer, S31::Sdc::Impl::GetMdibJobResult>::HandlerPtr makeHandler()
        {
            auto handler = makeOutcomeHandler([this](S31::Utils::Outcome<S31::Sdc::Impl::GetMdibJobResult>& outcome)
            {
                if (auto result = std::move(outcome.result()))
                {
                    m_jobResult = std::make_shared<S31::Sdc::Impl::GetMdibJobResult>(std::move(*result));
                }
                else
                {
                    if(outcome.hasError())
                    {
                        S31_STREAM_ERROR_LOGGER("Test", outcome.errorMessage());
                    }
                }

            });

            return handler;
        }

        std::shared_ptr<S31::Sdc::Impl::GetMdibJobResult> jobResult() const
        {
            return m_jobResult;
        }
    private:
        std::shared_ptr<S31::Sdc::Impl::GetMdibJobResult> m_jobResult;
};

}
