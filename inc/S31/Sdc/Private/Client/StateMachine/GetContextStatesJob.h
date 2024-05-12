#pragma once

#include <S31/BicepsXml/S31Only/Report.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/S31CoreExImp.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Job result of a \ref GetContextStatesJob
 * @ingroup S31SdcClient
 */
struct GetContextStatesJobResult
{
        Report::StateModifications modifications;
};

/**
 * @brief Job to fetch all context states.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP GetContextStatesJob : public OutgoingBlockingHttpRequestWithOutcome<GetContextStatesJobResult>
{
    public:
        GetContextStatesJob(const OutcomeHandlerPtr& handler, const std::string& targetAddress);

        void processRequest() override;

        std::string jobName() const override;

    private:
        const std::string m_jobName;
        const std::string m_targetAddress;
};

}
