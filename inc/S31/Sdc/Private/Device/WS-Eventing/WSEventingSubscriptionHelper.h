#pragma once

#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingSubscriptionEndJob.h>
#include <S31/Utils/Public/UniquePtrVector.h>

#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <string>
#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief An erase_if that returns the keys of the removed elements.
 * @details see also: https://en.cppreference.com/w/cpp/container/map/erase_if
 * @ingroup S31SdcDevice
 */
template<class Key, class T, class Compare, class Alloc, class Pred>
std::vector<Key> erase_if(std::map<Key,T,Compare,Alloc>& map, Pred pred)
{
    std::vector<Key> result;
    for (auto it = map.begin(), last = map.end(); it != last;)
    {
        if (pred(*it))
        {
            result.push_back(it->first);
            it = map.erase(it);
        }
        else
        {
            ++it;
        }
    }
    return result;
}

/**
 * @brief Removes the expired subscription from the given container.
 * @returns The subscription IDs of the removed subscriptions.
 * @ingroup S31SdcDevice
 */
template <typename Subscription>
std::vector<std::string> removeExpiredSubscriptions(std::map<std::string, DFL::NotNull<std::shared_ptr<Subscription>>>& subscriptions)
{
    return S31::Sdc::Impl::erase_if(subscriptions,
                   [](const auto& keyValue)
                   {
                       return keyValue.second->isSubscriptionExpired();
                   });
}

/**
 * @brief Creates a EndSubscription job for the given subscription
 * @ingroup S31SdcDevice
 */
template <typename Subscription, typename OutcomeHandler>
std::unique_ptr<OutgoingBlockingHttpRequest> createSubscriptionEndJob(
        const OutcomeHandler& handler,
        const Subscription& subscription,
        SubscriptionEndReason endReason,
        const DFL::Locale::Utf8& reasonMessage)
{
    std::unique_ptr<OutgoingBlockingHttpRequest> job;
    {
        if (subscription.endToEpr())
        {
            job = std::make_unique<WSEventingSubscriptionEndJob>(
                    handler,
                    SubscriptionId{subscription.subscriptionId()},
                    EndToEpr{subscription.endToEpr()},
                    SubscriptionManagerEpr{subscription.subscriptionManagerAddress()},
                    endReason,
                    reasonMessage);
        }
    }
    return job;
}

/**
 * @brief Creates a EndSubscription job for each subscription.
 * @ingroup S31SdcDevice
 */
template <typename Subscription, typename OutcomeHandler>
Utils::UniquePtrVector<OutgoingBlockingHttpRequest> createShutdownEndJobs(
        std::map<std::string, DFL::NotNull<std::shared_ptr<Subscription>>>& subscriptions,
        const OutcomeHandler& handler)
{
    Utils::UniquePtrVector<OutgoingBlockingHttpRequest> jobs;
    for (const auto& [id, subscription] : subscriptions)
    {
        std::ignore = id;
        if (subscription->endToEpr())
        {
            jobs.pushBackIfNotNull(
                    createSubscriptionEndJob(
                            handler,
                            *subscription,
                            SubscriptionEndReason::SourceShuttingDown,
                            DFL::Locale::Utf8("Event source is going offline.")
                            ));
        }
    }
    return jobs;
}

}
