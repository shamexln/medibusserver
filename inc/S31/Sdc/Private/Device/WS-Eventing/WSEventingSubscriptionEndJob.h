#pragma once

#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionEndReason.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc::Impl
{
class GsoapEpr;

/**
 * @brief Result of @ref WSEventingSubscriptionEndJob.
 * @ingroup S31SdcDevice
 */
struct WSEventingSubscriptionEndJobResult
{
};

struct SubscriptionIdTag{};
struct EndToEprTag{};
struct SubscriptionManagerEprTag{};

/**
 * @brief Typesafe subscription ID.
 * @ingroup S31SdcDevice
 */
using SubscriptionId = DFL::StrongTypedef<std::string, SubscriptionIdTag, DFL::Skill::Streamable>;

/**
 * @brief Typesafe (optional) EndTo endpoint reference.
 * @ingroup S31SdcDevice
 */
using EndToEpr = DFL::StrongTypedef<std::shared_ptr<GsoapEpr>, EndToEprTag, DFL::Skill::Streamable>;

/**
 * @brief Typesafe subscription manager endpoint reference.
 * @ingroup S31SdcDevice
 */
using SubscriptionManagerEpr = DFL::StrongTypedef<std::string, SubscriptionManagerEprTag, DFL::Skill::Streamable>;

/**
 * @brief Send a WS-Eventing SubscriptionEnd message to the event sink (client).
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP WSEventingSubscriptionEndJob: public OutgoingBlockingHttpRequestWithOutcome<WSEventingSubscriptionEndJobResult>
{
    DFL_NOT_COPYABLE(WSEventingSubscriptionEndJob)
public:
    WSEventingSubscriptionEndJob(const OutcomeHandlerPtr& handler,
            SubscriptionId subscriptionId,
            const EndToEpr& endToEpr,
            SubscriptionManagerEpr subscriptionManager,
            SubscriptionEndReason reason,
            DFL::Locale::Utf8 reasonMessage);

    void processRequest() override;
    std::string jobName() const override;

private:
    const char* provideMessageOrDefault(const char* defaultMsg) const;

    const SubscriptionId m_subscriptionId;
    const EndToEpr m_epr;
    const SubscriptionManagerEpr m_subscriptionManagerAddr;
    const DFL::Locale::Utf8 m_reasonMessage;
    const SubscriptionEndReason m_reason;
};

}
