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
 * \brief Result of \ref WSEventingUnsubscribeJob.
 *
 * \ingroup S31SdcClientEventing
 */
struct WSEventingUnsubscribeJobResult
{
    WSEventingClientSubscriptionId subscriptionId;
};

/**
 * \brief WS-Eventing client unsubscribe to a remote DPWS device.
 *
 * \ingroup S31SdcClientEventing
 */
class S31_CORE_EXPIMP WSEventingUnsubscribeJob
    : public OutgoingBlockingHttpRequestWithOutcome<WSEventingUnsubscribeJobResult>
{
        DFL_NOT_COPYABLE(WSEventingUnsubscribeJob)
    public:
        WSEventingUnsubscribeJob(const OutcomeHandlerPtr& handler,
                                 WSEventingClientSubscriptionId subscriptionId,
                                 const GsoapEpr& remoteEpr);

        ~WSEventingUnsubscribeJob() noexcept override;

        void processRequest() override;

        std::string jobName() const override;

    private:
        WSEventingClientSubscriptionId m_subscriptionId;
        GsoapEpr m_remoteEpr;

};

}
