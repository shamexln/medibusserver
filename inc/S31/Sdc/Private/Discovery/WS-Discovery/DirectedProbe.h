#pragma once

#include <S31/Sdc/Private/Common/OutcomeConsumerProxy.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/DirectedProbeJob.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeHttpJobResult.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeTargetType.h>

#include <Framework/Utils/Public/Uri.h>

namespace S31::Sdc::Impl
{
/**
 * @brief Wrapper class around an DirectedProbe OutcomeConsumer that flags when the outcome is delivered
 * \ingroup S31SdcWsDiscovery
 */
class DirectedProbe : public Utils::OutcomeConsumer<DirectedProbe, DirectedProbeJobResults>,
    public std::enable_shared_from_this<DirectedProbe>
{
    public:

        DirectedProbe(ProbeTargetType targetType,
                      const DFL::Net::Uri& address, // NOLINT(modernize-pass-by-value)
                      LocalUdpEndpointPort localUdpEndpointPort,
                      CallbackFunction callback,
                      WSDiscoveryScopes scopes);

        std::unique_ptr<DirectedProbeJob> makeJob();

        bool resultReceived();

        using HttpDirectedProbeOutcomeConsumer = OutcomeConsumerProxy<DirectedProbeJobResults>;

    private:
        ProbeTargetType m_targetType;
        DFL::Net::Uri m_address;
        LocalUdpEndpointPort m_localUdpEndpointPort;
        CallbackFunction m_callbackFunction;
        WSDiscoveryScopes m_scopes;
        bool m_outcomeDelivered{false};
        std::shared_ptr<HttpDirectedProbeOutcomeConsumer> m_outcomeConsumer;
        HandlerPtr m_handler;
        std::mutex m_mutex;
};

}
