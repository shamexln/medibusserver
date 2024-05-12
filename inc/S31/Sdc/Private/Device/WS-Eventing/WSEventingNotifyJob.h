#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/DsoapCommon/SoapViewTypes.h>
#include <S31/Sdc/Private/Common/EncodingType.h>
#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{

class IOutgoingMessage;
class GsoapEpr;

/**
 * @brief Result of a @ref WSEventingNotifyJob.
 * @ingroup S31SdcDevice
 */
struct WSEventingNotifyJobResult
{
        std::string subscriptionId;
};

/**
 * @brief Notifies a single event sink.
 * @details The job can be scheduled multiple times for multiple event sinks with the same shared message.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP WSEventingNotifyJob: public OutgoingBlockingHttpRequestWithOutcome<WSEventingNotifyJobResult>
{
        DFL_NOT_COPYABLE(WSEventingNotifyJob)
    public:
        WSEventingNotifyJob(
                const OutcomeHandlerPtr& handler,
                DFL::NotNull<std::shared_ptr<IOutgoingMessage>> event,
                DFL::NotNull<std::shared_ptr<GsoapEpr>> epr,
                SoapActionView soapAction,
                std::string subscriptionId,
                EncodingType encoding);

        void processRequest() override;
        std::string jobName() const override;

    private:
        DFL::NotNull<std::shared_ptr<IOutgoingMessage>> m_event;
        DFL::NotNull<std::shared_ptr<GsoapEpr>> m_epr;
        std::string m_soapAction;
        std::string m_subscriptionId;
        EncodingType m_encoding;
};

}
