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
 * \brief Result of a \ref WSEventingGetStatusJob.
 * \ingroup S31SdcClientEventing
 */
struct WSEventingGetStatusJobResult
{
    WSEventingClientSubscriptionId subscriptionId;
    DFL::Chrono::Seconds duration;
};

/**
 * \brief Retrieve the status of a WS-Eventing subscription.
 * \ingroup S31SdcClientEventing
 */
class S31_CORE_EXPIMP WSEventingGetStatusJob
    : public OutgoingBlockingHttpRequestWithOutcome<WSEventingGetStatusJobResult>
{
        DFL_NOT_COPYABLE(WSEventingGetStatusJob)
    public:
        WSEventingGetStatusJob(const OutcomeHandlerPtr& handler, WSEventingClientSubscriptionId subscriptionId, const GsoapEpr& endpoint);

        void processRequest() override;

        std::string jobName() const override;

    private:
        WSEventingClientSubscriptionId m_subscriptionId;
        GsoapEpr m_remoteEpr;

};

}
