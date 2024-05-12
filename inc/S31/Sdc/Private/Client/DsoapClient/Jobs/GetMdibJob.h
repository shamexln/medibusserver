#pragma once

#include <S31/Safety/Public/Requirement.h>
#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Private/Client/RemoteMdibAccess.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>
#include <S31/Utils/S31Only/StopWatch.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * \brief Result of a @ref GetMdibJob
 * \ingroup S31SdcClient
 */
struct GetMdibJobResult
{
        S31::Sdc::EndpointReference urn;
        DFL::Mdib::MdibChangeSet changeSet;
        DFL::Mdib::MdibVersion mdibVersion;
        DFL::NotNull<std::unique_ptr<S31::Safety::Requirements>> safetyRequirements;
        boost::optional<DFL::Mdib::VersionCounter> mdDescriptionVersion;
        boost::optional<DFL::Mdib::VersionCounter> mdStateVersion;
};

/**
 * \brief Asynchronous job to retrieve the MDIB of another device in the network.
 *
 * \ingroup S31SdcClient
 */
class S31_CORE_EXPIMP GetMdibJob : public OutgoingBlockingHttpRequestWithOutcome<GetMdibJobResult>
{
    public:
        GetMdibJob(const OutcomeHandlerPtr& handler, S31::Sdc::EndpointReference urn, const std::string& getServiceAddr);
        ~GetMdibJob() override = default;

        RequestStatus processRequest(std::shared_ptr<OutgoingBlockingHttpRequest> self) override;
        void processHttpResult(const HttpResult& result) override;

        std::string jobName() const override;

    private:
        S31::Sdc::EndpointReference m_deviceUrn;
        std::string m_getServiceEpr;
        Utils::StopWatch m_requestTime;

        static void mapSafetyRequirementsFromOperationsFromGsoap(S31::Safety::Requirements& dest, const DFL::Mdib::MdibChangeSet& changes, const pm__Mdib& src);
};

}
