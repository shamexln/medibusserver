#pragma once


#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/Sdc/Private/Common/Http/BoostAsioSslContextFactory.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>

#include <Framework/Utils/Public/Uri.h>

#include <memory>

namespace S31
{
class CoreConfiguration;
namespace Sdc::Impl
{
struct OutgoingUnicastMessageContext;

struct OutgoingUnicastMessageResult
{
};

/**
 * @brief Outgoing WS-Discovery unicast message.
 * @ingroup S31SdcCommonWebServices
 */
class OutgoingUnicastMessageJob: public OutgoingBlockingHttpRequestWithOutcome<OutgoingUnicastMessageResult>
{
    public:
        explicit OutgoingUnicastMessageJob(
                const OutcomeHandlerPtr& handler,
                const DFL::Net::Uri& discoveryProxyAddress,
                std::weak_ptr<S31::CoreConfiguration> configuration,
                OutgoingUnicastMessageContext m_messageContext);

        void processRequest() override;

        std::string jobName() const override;

        enum class SendStatus{ok, sessionError, httpError};

    private:
        void sendRequest(const DFL::Net::Uri& discoveryProxy);

        std::weak_ptr<S31::CoreConfiguration> m_configuration;
        OutgoingUnicastMessageContext m_messageContext;
};

}
}
