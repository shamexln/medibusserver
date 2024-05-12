#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/HttpDiscoveryJob.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ResolveHttpJobResult.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Utils/Public/Outcome.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <Framework/Utils/Public/Uri.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Job to request WS-Discovery resolve data via HTTP to a discovery proxy.
 *
 * @ingroup S31SdcWsDiscovery
 */
class ResolveHttpJob:
        public HttpDiscoveryJob<ResolveHttpJobResult, ResolveHttpJob>
{
    public:
        /**
         * @brief gSoap ResolveMatch type.
         */
        using T_MatchOp = __wsd11__ResolveMatchOp;
        /**
         * @brief Results of parsing a ResolveMatch using gSoap.
         */
         using GSoapResolveMatch = GSoapDiscoveryMatch<T_MatchOp>;

        ResolveHttpJob(
                const OutcomeHandlerPtr& handler,
                const DFL::Net::Uri& targetAddress,
                S31::Sdc::EndpointReference endpoint,
                LocalUdpEndpointPort localUdpEndpointPort);

        std::string jobName() const override;

        /**
         * @brief Process ResolveMatch soap messages into objects of type @ref GSoapResolveMatch using gSoap.
         */
        static GSoapResolveMatch parseSoapMessage(struct soap* soapHandle);

        /**
         * @brief Process objects of type @ref T_MatchOp into @ref ResolveHttpJobResult.
         */
        static boost::optional<ResolveHttpJobResult> processMatches(const T_MatchOp& matchOp);

        /**
         * @brief Create a Resolve message.
         */
        CreateRequestBody createSoapMessage(DFL::NotNull<struct soap*> soapHandle) const;

        // For test access by TestDpwsEndpointImpl
        using Utils::OutcomeProvider<ResolveHttpJobResult>::setOutcomeResult;
        using Utils::OutcomeProvider<ResolveHttpJobResult>::setOutcomeError;

    private:
        S31::Sdc::EndpointReference m_endpoint;
        LocalUdpEndpointPort m_localUdpEndpointPort;
};

}
