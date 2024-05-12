#pragma once

#include <S31/Nomenclature/Public/Credentials.h>

#include <Framework/Utils/Public/EnumClass.h>

#include <set>
#include <utility>
#include <vector>

namespace S31::Sdc
{

/**
 * @brief Subscription information of a client.
 * @details Subscription information contains subscriber certificate and the subscription types.
 * @ingroup S31SdcDevice
 */
class SubscriptionInfo
{
    public:
        /**
         * @brief Enumerate the BICEPS report types which may be provided by a subscription.
         */
        enum class ReportType
        {
            AlertState,
            ComponentState,
            ContextState,
            DescriptionModification,
            MetricState,
            OperationalState,
            OperationInvoked,
            SystemError,
            WaveformStream
        };

        SubscriptionInfo(std::string subscriptionId,
                         Nomenclature::Credentials subscriberCredentials,
                         std::vector<std::string> subscriptionActions);

        /**
         * @deprecated Internal details of subscription shall be removed in the future.
         * Use @ref clientCertificate() instead for subscriber identifiers (e.g. DistinguishedName).
         */
        const std::string& subscriptionId() const;

        /**
         * @deprecated Internal details of subscription shall be removed in the future.
         * Use @ref subscribedReportTypes() to find subscription information items.
         */
        const std::vector<std::string>& subscriptionActions() const;

        /**
         * @brief The subscriber client certificate.
         */
        const DFL::Crypto::Certificate& clientCertificate() const;

        /**
         * @brief The BICEPS report types which are provided by this subscription.
         */
        const std::set<ReportType>& subscribedReportTypes() const;

    private:
        static std::set<ReportType> actionsToReportTypes(const std::vector<std::string>& actions);

        std::string m_subscriptionId;
        Nomenclature::Credentials m_subscriberCredentials;
        std::vector<std::string> m_subscriptionActions;
        std::set<ReportType> m_subscribedReportTypes;
};

using ClientSubscriptions = std::vector<SubscriptionInfo>;

DFL_ENUM_CLASS_STREAM_OPERATOR(
        SubscriptionInfo::ReportType,
        (AlertState)(ComponentState)(ContextState)(DescriptionModification)(MetricState)(OperationalState)(OperationInvoked)(SystemError)(WaveformStream))

inline SubscriptionInfo::SubscriptionInfo(
        std::string               subscriptionId,
        Nomenclature::Credentials subscriberCredentials,
        std::vector<std::string>  subscriptionActions)
    : m_subscriptionId(std::move(subscriptionId))
    , m_subscriberCredentials(std::move(subscriberCredentials))
    , m_subscriptionActions(std::move(subscriptionActions))
    , m_subscribedReportTypes(actionsToReportTypes(m_subscriptionActions))
{
}

inline const std::string& SubscriptionInfo::subscriptionId() const
{
    return m_subscriptionId;
}

inline const std::vector<std::string>& SubscriptionInfo::subscriptionActions() const
{
    return m_subscriptionActions;
}

inline const DFL::Crypto::Certificate& SubscriptionInfo::clientCertificate() const
{
    return m_subscriberCredentials.peerCertificate();
}

inline const std::set<SubscriptionInfo::ReportType>& SubscriptionInfo::subscribedReportTypes() const
{
    return m_subscribedReportTypes;
}

}
