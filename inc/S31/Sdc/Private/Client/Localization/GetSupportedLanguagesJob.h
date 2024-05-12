#pragma once

#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Utils/Public/LanguageTag.h>

#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Alias for language vector.
 * @ingroup S31SdcClient
 */
using Languages = std::vector<DFL::Locale::LanguageTag>;

/**
 * @brief Data for the positive outcome of @ref GetSupportedLanguagesJob.
 * @ingroup S31SdcClient
 */
struct GetSupportedLanguagesJobResult
{
        DFL::Mdib::MdibVersion mdibVersion;
        Languages languages;
};

/**
 * @brief Job for a BICEPS GetSupportedLanguages request.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP GetSupportedLanguagesJob
    : public Sdc::Impl::OutgoingBlockingHttpRequestWithOutcome<GetSupportedLanguagesJobResult>
{
    public:
        GetSupportedLanguagesJob(const OutcomeHandlerPtr& handler, const Endpoint::Url& targetAddress);

        RequestStatus processRequest(std::shared_ptr<OutgoingBlockingHttpRequest> self) override;
        void processHttpResult(const HttpResult& result) override;

        std::string jobName() const override;
    private:
        const std::string m_jobName;
        const Endpoint::Url m_targetAddress;
};

}
