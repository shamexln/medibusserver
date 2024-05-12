#pragma once

#include <S31/Sdc/Private/Client/WS-Eventing/WSEventingClientSubscriptionId.h>
#include <S31/Sdc/Private/Common/MessageLayer/GsoapEpr.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc::Impl
{

class SoapContextPool;

/**
 * \brief Result of \ref WSEventingRenewJob.
 * \ingroup S31SdcClientEventing
 */
struct WSEventingRenewJobResult
{
    WSEventingClientSubscriptionId subscriptionId;
    DFL::Chrono::Seconds duration;
};

/**
 * \brief Renew a WS-Eventing subscription (before it ended).
 * \ingroup S31SdcClientEventing
 */
class S31_CORE_EXPIMP WSEventingRenewJob : public OutgoingBlockingHttpRequestWithOutcome<WSEventingRenewJobResult>
{
        DFL_NOT_COPYABLE(WSEventingRenewJob)
    public:
        WSEventingRenewJob(const OutcomeHandlerPtr& handler, WSEventingClientSubscriptionId subscriptionId, const GsoapEpr& endpoint);

        void processRequest() override;

        std::string jobName() const override;

    private:
        WSEventingClientSubscriptionId m_subscriptionId;
        GsoapEpr m_remoteEpr;

};

}