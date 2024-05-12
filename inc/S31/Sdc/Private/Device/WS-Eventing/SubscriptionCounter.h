#pragma once

#include <atomic>
#include <memory>

namespace S31::Sdc::Impl
{

class SubscriptionCounter;

using SharedSubscriptionCounter = std::shared_ptr<SubscriptionCounter>;
using WeakSubscriptionCounter = std::weak_ptr<SubscriptionCounter>;

/**
 * @brief Counter to limit the number of active subscriptions.
 * @ingroup S31SdcDevice
 */
class SubscriptionCounter
{
    public:

        /**
         * @brief Try to increment the counter.
         * @return true if the counter was incremented, false if the the limit was already reached and the counter could not increment.
         */
        bool increment()
        {
            const auto oldValue = m_value.fetch_add(1);
            if (oldValue >= m_limit)
            {
                // we hit the limit, revert the add
                m_value.fetch_sub(1);
                return false;
            }
            return true;
        }

        void decrement()
        {
            m_value.fetch_sub(1);
        }

        unsigned int limit() const
        {
            return m_limit;
        }

        /**
         * @brief Factory function
         * @param limit Limit to which the counter can be incremented (including).
         */
        static SharedSubscriptionCounter make(unsigned int limit)
        {
            return std::shared_ptr<SubscriptionCounter>(new SubscriptionCounter(limit));
        }

    private:
        explicit SubscriptionCounter(unsigned int limit):
            m_limit(limit)
        {}

        std::atomic_uint m_value{0};
        unsigned int m_limit{0};
};

}
