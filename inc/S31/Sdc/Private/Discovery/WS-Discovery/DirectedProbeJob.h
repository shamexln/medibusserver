#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/HttpDiscoveryJob.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeHttpJobResult.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeTargetType.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/Utils/Public/Outcome.h>
#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <Framework/Utils/Public/Uri.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * \brief Job to request WS-Discovery probe data via HTTP.
 *
 * \ingroup S31SdcWsDiscovery
 */
class S31_CORE_EXPIMP DirectedProbeJob:
        public HttpDiscoveryJob<DirectedProbeJobResults, DirectedProbeJob>
{
    public:
        /**
         * @brief gSoap ProbeMatch type
         */
        using T_MatchOp = __wsd11__ProbeMatchOp;
        /**
         * @brief Results of parsing a ResolveMatch using gSoap.
         */
        using GSoapProbeMatch = GSoapDiscoveryMatch<T_MatchOp>;

        DirectedProbeJob(
                const OutcomeHandlerPtr& handler,
                const DFL::Net::Uri& targetAddress,
                ProbeTargetType targetType,
                LocalUdpEndpointPort localUdpEndpointPort,
                WSDiscoveryScopes scopes);

        std::string jobName() const override;

        /**
         * @brief Process ProbeMatch soap messages into objects of type @ref GSoapProbeMatch using gSoap.
         */
        static GSoapProbeMatch parseSoapMessage(struct soap* soapHandle);

        /**
         * @brief Process objects of type @ref T_MatchOp into @ref DirectedProbeJobResults.
         */
        static boost::optional<DirectedProbeJobResults> processMatches(const T_MatchOp& matchOp);

        /**
         * @brief Create a Probe message.
         */
        CreateRequestBody createSoapMessage(DFL::NotNull<struct soap*> soapHandle) const;

    private:
        ProbeTargetType m_targetType;
        LocalUdpEndpointPort m_localUdpEndpointPort;
        WSDiscoveryScopes m_scopes;
};

}
