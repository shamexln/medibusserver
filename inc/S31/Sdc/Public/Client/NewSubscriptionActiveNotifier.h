#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>

#include <functional>

namespace S31::Sdc
{

/**
 * @brief Notification object for subscription activation.
 *
 * @note There is only (real) waiting for activation if really a new subscription is needed. If the scope
 * of the synchronizer call is already covered then no waiting is needed.
 *
 * In case of subscription error there will the notification too! However the error is propagated through
 * the error handlers.
 *
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP NewSubscriptionActiveNotifier
{
    public:
        virtual ~NewSubscriptionActiveNotifier() = default;

        using NotifyFunction = std::function<void()>;

        /// Use for synchronous wait for activation.
        /// @returns false if activation was not in given time
        virtual bool waitForActivation(const DFL::Chrono::Milliseconds& maxWaitTime) = 0;

        /// Use for asynchronous wait for activation.
        /// Is invoked immediately if the activation already happened.
        virtual void registerCallback(const NotifyFunction& callback) = 0;
};

}
