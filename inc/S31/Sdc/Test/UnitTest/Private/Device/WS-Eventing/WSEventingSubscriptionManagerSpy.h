#pragma once

#include <S31/Sdc/Private/Device/WS-Eventing/IWSEventingSubscriptionManager.h>

namespace S31::Sdc::Impl::Test
{

/**
 * @brief Simple spy to for checking incoming WS-Eventing messages.
 */
class WSEventingSubscriptionManagerSpy: public IWSEventingSubscriptionManager
{
    public:
        SubscribeResult subscribe(
                const DFL::Chrono::Seconds& expiration,
                const DFL::NotNull<std::shared_ptr<const HttpSessionContext>>& /*httpSessionContext*/,
                SubscriptionFilterDialect /*dialect*/,
                SubscriptionFilterContent /*content*/,
                DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::GsoapEpr>> /*notifyTo*/,
                std::shared_ptr<S31::Sdc::Impl::GsoapEpr> /*endTo*/,
                const std::string& /*subManagerAddress*/,
                EncodingType encoding) override
        {
            m_subscribedEncodings.push_back(encoding);

            SubscribeResult result{};
            result.isSuccess = true;
            result.subscriptionId = "sub-id";
            result.actualExpires = expiration;
            return result;
        }

        boost::optional<DFL::Chrono::Seconds> getStatus(const std::string& /*subscriptionId*/) override
        {
            return boost::none;
        }

        boost::optional<DFL::Chrono::Seconds> renew(const std::string& /*subscriptionId*/, DFL::Chrono::Seconds /*requestedExpiration*/) override
        {
            return boost::none;
        }

        void unsubscribe(const std::string& /*subscriptionId*/) override
        {
        }

        const std::vector<EncodingType>& encodings() const
        {
            return m_subscribedEncodings;
        }
    private:
        std::vector<EncodingType> m_subscribedEncodings;
};

}
