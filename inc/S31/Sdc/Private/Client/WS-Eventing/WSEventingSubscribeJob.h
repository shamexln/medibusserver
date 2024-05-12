#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Private/Common/Endpoint/EndpointUrl.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Crypto/Public/DistinguishedName.h>

#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class IRemoteHostedServiceEndpoint;
class SoapContextPool;

/**
 * \brief Result of \ref WSEventingSubscribeJob.
 * \ingroup S31SdcClientEventing
 */
struct WSEventingSubscribeJobResult
{
    WSEventingClientSubscriptionId subscriptionId;
    std::shared_ptr<GsoapEpr> remoteManger;
    DFL::Chrono::Seconds duration;
    DFL::Crypto::DistinguishedName remoteDeviceDistinguishedName;
};

/**
 * \brief WS-Eventing client subscribe to a remote DPWS device.
 * \ingroup S31SdcClientEventing
 */
class S31_CORE_EXPIMP WSEventingSubscribeJob: public OutgoingBlockingHttpRequestWithOutcome<WSEventingSubscribeJobResult>
{
    public:
        WSEventingSubscribeJob(const WSEventingSubscribeJob&) = delete;
        WSEventingSubscribeJob(WSEventingSubscribeJob&&) = delete;
        WSEventingSubscribeJob& operator=(const WSEventingSubscribeJob&) = delete;
        WSEventingSubscribeJob& operator=(WSEventingSubscribeJob&&) = delete;
        ~WSEventingSubscribeJob() override = default;

        WSEventingSubscribeJob(
                const OutcomeHandlerPtr& handler,
                WSEventingClientSubscriptionId subscriptionId,
                const S31::Sdc::Impl::Endpoint::Url& target,
                SoapActions actions,
                std::string callbackDirname,
                unsigned short callbackPortNumber);

        RequestStatus processRequest(std::shared_ptr<OutgoingBlockingHttpRequest> self) override;
        void processHttpResult(const HttpResult& httpResult) override;

        std::string jobName() const override;

    private:
        WSEventingClientSubscriptionId m_subscriptionId;
        S31::Sdc::Impl::Endpoint::Url m_target;
        SoapActions m_actions;
        std::string m_callbackDirname;
        unsigned short m_callbackPortNumber;
};

}
