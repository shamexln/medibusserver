#pragma once

#include <S31/BicepsXml/S31Only/Report.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Result of @ref GetMdStateJob.
 * @ingroup S31SdcClient
 */
struct GetMdStateJobResult
{
    GetMdStateJobResult() = default;
    GetMdStateJobResult(const GetMdStateJobResult&) = delete;
    GetMdStateJobResult& operator= (const GetMdStateJobResult&) = delete;
    GetMdStateJobResult(GetMdStateJobResult&&) = default;
    GetMdStateJobResult& operator= (GetMdStateJobResult&&) = default;

    Report::StateModifications states;
};

/**
 * @brief Asynchronous job to retrieve Mdib states of another device in the network.
 *
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP GetMdStateJob : public OutgoingBlockingHttpRequestWithOutcome<GetMdStateJobResult>
{
    public:
        GetMdStateJob(const OutcomeHandlerPtr& handler,
                      const S31::Sdc::EndpointReference& deviceEndpointRef, // NOLINT(modernize-pass-by-value)
                      const std::string& getServiceAdd);
        ~GetMdStateJob() override = default;
        void processRequest() override;
        std::string jobName() const override;

    private:
        S31::Sdc::EndpointReference m_deviceEndpointRef;
        std::string m_getServiceEpr;
};

}
