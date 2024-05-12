#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Sdc/Private/Common/EncodingType.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionEndReason.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionFilterHandler.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Oids.h>
#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional/optional.hpp>

#include <optional>
#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class GsoapEpr;
class HttpSessionContext;

/**
 * @brief Result of a @ref IWSEventingSubscriptionManager::subscribe() call.
 * @ingroup S31SdcDevice
 */
struct SubscribeResult
{
        explicit operator bool() const noexcept
        {
            return isSuccess;
        }

        bool isSuccess{false};
        std::string subscriptionId{};
        DFL::Chrono::Seconds actualExpires{};

        /// Not empty in case of error.
        DFL::Locale::Utf8 errorMessage;
        std::string errorQname;
};


/**
 * @brief Interface for device side WS-Eventing subscription manager.
 *
 * @ingroup S31SdcDevice
 */
class IWSEventingSubscriptionManager
{
    public:
        virtual ~IWSEventingSubscriptionManager() noexcept = default;

        /**
         * @name Handling of incoming WS-Eventing messages.
         */
        ///@{

        /**
         * @param[in] requestedExpiration   Set with requested value. The actual expriration value is returned in the
         * function result.
         * @param[in] httpSessionContext    Client credentials (roles, ...), ip address, port, ...
         * @param[in] dialect               Filter dialect
         * @param[in] content               Filter content
         * @param[in] notifyTo              EPR for notification.
         * @param[in] endTo                 EPR for SubscriptionEnd.
         * @param[in] subManagerAddress     Transport address where the subscription should be send to.
         * @param[in] encoding              Encoding (compression) type of outgoing message (or none)
         */
        virtual SubscribeResult subscribe(
                const DFL::Chrono::Seconds&                                    requestedExpiration,
                const DFL::NotNull<std::shared_ptr<const HttpSessionContext>>& httpSessionContext,
                SubscriptionFilterDialect                                      dialect,
                SubscriptionFilterContent                                      content,
                DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GsoapEpr>>        notifyTo,
                std::shared_ptr<S31::Sdc::Impl::GsoapEpr>                      endTo,
                const std::string&                                             subManagerAddress,
                EncodingType                                                   encoding) = 0;

        /**
         * @brief Remaining subscription time (or none for non-existing subscription).
         */
        virtual boost::optional<DFL::Chrono::Seconds> getStatus(const std::string& subscriptionId) = 0;

        /**
         * @brief Renew an existing subscription on the subscription manager.
         *
         * @param subscriptionId identifier to identify an existing subscription.
         * @param requestedExpiration the duration the WS-Eventing client wants to set for the expiration
         * @return returns the accepted expiration duration (if subscription exists)
         */
        virtual boost::optional<DFL::Chrono::Seconds> renew(const std::string& subscriptionId, DFL::Chrono::Seconds requestedExpiration) = 0;

        /**
         * @brief Unsubscribe given subscription.
         */
        virtual void unsubscribe(const std::string& subscriptionId) = 0;
        ///@}

};

}
