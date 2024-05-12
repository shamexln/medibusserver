#pragma once

#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>
#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Data for the positive outcome of @ref GetLocalizedTextJob.
 * @ingroup S31SdcClient
 */
struct GetLocalizedTextJobResult
{
        DFL::Mdib::MdibVersion mdibVersion;
        DFL::Mdib::LocalizedTexts texts;
};

/**
 * @brief Job for a BICEPS GetLocalizedText request.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP GetLocalizedTextJob : public OutgoingBlockingHttpRequestWithOutcome<GetLocalizedTextJobResult>
{
    public:
        GetLocalizedTextJob(const OutcomeHandlerPtr& handler, const Endpoint::Url& targetAddress, S31::Localization::LocalizedTextFilter filter = S31::Localization::LocalizedTextFilter());

        void processRequest() override;

        std::string jobName() const override;

    private:
        const std::string m_jobName;
        const Endpoint::Url m_targetAddress;
        S31::Localization::LocalizedTextFilter m_filter;

};

}
