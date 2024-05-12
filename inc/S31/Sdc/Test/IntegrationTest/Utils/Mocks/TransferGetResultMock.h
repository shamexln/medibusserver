#pragma once

#include <S31/Sdc/Private/Client/Metadata/GetDeviceMetadataJob.h>
#include <S31/Utils/Public/Outcome.h>

namespace S31::Sdc::Test
{

/**
 * @brief Class to generate a handler for a \ref S31::Sdc::Impl::GetDeviceMetadataJob for easy access to the resulting \ref S31::Sdc::Impl::GetDeviceMetadataJobResult.
 */
class TransferGetResultMock:
        public S31::Utils::OutcomeConsumer<TransferGetResultMock, S31::Sdc::Impl::GetDeviceMetadataJobResult>,
        public std::enable_shared_from_this<TransferGetResultMock>
{
    public:
        S31::Utils::OutcomeConsumer<TransferGetResultMock, S31::Sdc::Impl::GetDeviceMetadataJobResult>::HandlerPtr makeHandler()
        {
            auto handler = makeOutcomeHandler([this](S31::Utils::Outcome<S31::Sdc::Impl::GetDeviceMetadataJobResult>& outcome)
            {
                if (auto result = std::move(outcome.result()))
                {
                    m_jobResult = std::make_shared<S31::Sdc::Impl::GetDeviceMetadataJobResult>(std::move(*result));
                }
            });

            return handler;
        }

        std::shared_ptr<S31::Sdc::Impl::GetDeviceMetadataJobResult> jobResult() const
        {
            return m_jobResult;
        }
    private:
        std::shared_ptr<S31::Sdc::Impl::GetDeviceMetadataJobResult> m_jobResult;
};

}
