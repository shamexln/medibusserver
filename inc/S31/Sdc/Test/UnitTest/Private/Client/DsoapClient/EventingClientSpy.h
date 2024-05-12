#pragma once

#include <S31/Sdc/Private/Client/Metadata/IRemoteHostedServiceEndpoint.h>
#include <S31/Sdc/Private/Client/WS-Eventing/IEventingClient.h>
#include <S31/Sdc/Private/Client/WS-Eventing/IWSEventingClientListener.h>
#include <S31/Sdc/Private/Common/RandomNumberGenerator.h>

#include <map>
#include <string>

namespace S31::Sdc::Impl::Test
{

/**
 * Helper class for unit tests with remote eventing part.
 */
class EventingClientSpy: public Sdc::Impl::IEventingClient
{
    public:
        EventingClientSpy() :
                m_subscribeCount(0),
                m_unsubscribeCount(0),
                m_renewCount(0)
        {
        }

        virtual Sdc::Impl::WSEventingClientSubscriptionId subscribe(
                const S31::Sdc::Impl::Endpoint::Executor& /*executor*/,
                const std::shared_ptr<Sdc::Impl::IWSEventingClientListener>& callback) override
        {
            m_subscribeCount++;
            auto id(Sdc::Impl::RandomNumberGenerator::getRandomUuidUrn());
            m_subscriptions.insert(std::make_pair(id, callback));
            callback->injectSubscriptionId(Sdc::Impl::WSEventingClientSubscriptionId(id));
            return Sdc::Impl::WSEventingClientSubscriptionId(id);
        }

        virtual Sdc::Impl::WSEventingClientSubscriptionId subscribe(
                const S31::Sdc::Impl::Endpoint::Executor& executor,
                const SoapActions& /*actions*/,
                const std::shared_ptr<Sdc::Impl::IWSEventingClientListener>& callback) override
        {
            return subscribe(executor, callback);
        }

        virtual void unsubscribe(const Sdc::Impl::WSEventingClientSubscriptionId&, const DFL::Locale::Utf8&) override
        {
            m_unsubscribeCount++;
        }

        virtual void triggerRenew(const Sdc::Impl::WSEventingClientSubscriptionId& /*subId*/) override
        {
            m_renewCount++;
        }

        virtual void triggerGetStatus(const Sdc::Impl::WSEventingClientSubscriptionId& /*id*/) override
        {
        }

        void cancelAllSubscriptionsWithStatus(Sdc::Impl::SubscriptionEndStatus status)
        {
            for (auto it = m_subscriptions.begin(); it != m_subscriptions.end();)
            {
                it->second->subscriptionEnd(status, DFL::Locale::Utf8());
                it = m_subscriptions.erase(it);
            }
        }

        int subscriptionCount() const
        {
            return m_subscribeCount;
        }

        int unsubscriptionCount() const
        {
            return m_unsubscribeCount;
        }

        int renewCount() const
        {
            return m_renewCount;
        }

        void resetSpy()
        {
            m_subscribeCount = 0;
            m_unsubscribeCount = 0;
            m_renewCount = 0;
        }

        void clearSubscriptions()
        {
            m_subscriptions.clear();
        }

        std::vector<std::string> subscriptionIds() const
        {
            std::vector<std::string> result;
            for (const auto& s : m_subscriptions)
            {
                result.push_back(s.first);
            }
            return result;
        }

        size_t subscriptionsActive() const
        {
            return m_subscriptions.size();
        }

        void activateAll(DFL::Chrono::Seconds expiration)
        {
            for (const auto& s : m_subscriptions)
            {
                s.second->expirationResponse(expiration);
            }
        }

    private:
        std::multimap<std::string, std::shared_ptr<Sdc::Impl::IWSEventingClientListener>> m_subscriptions;
        int m_subscribeCount;
        int m_unsubscribeCount;
        int m_renewCount;

};

}
