#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Public/Device/ClientSubscriptionObserver.h>
#include <S31/Sdc/Public/Device/SubscriptionInfo.h>

#include <Framework/Utils/Public/Oids.h>

#include <atomic>
#include <mutex>
#include <vector>

namespace S31::Sdc::Test
{

class DeviceSubscriptionInfoObserverMock : public S31::Sdc::ClientSubscriptionObserver
{
    public:
        void clientSubscriptionsChanged() override
        {
            callCount++;
        }

        void clientSubscriptionFailed(const SubscriptionInfo& info) override
        {
            std::lock_guard lock(m_errorMutex);
            m_failedSubscriptions.push_back(info);
        }

        std::size_t failedCount() const
        {
            std::lock_guard lock(m_errorMutex);
            return m_failedSubscriptions.size();
        }

        std::vector<SubscriptionInfo> failedSubscriptions() const
        {
            std::lock_guard lock(m_errorMutex);
            return m_failedSubscriptions;
        }

        void reset()
        {
            callCount = 0;

            std::lock_guard lock(m_errorMutex);
            m_failedSubscriptions.clear();
        }

        std::atomic_int callCount;

    private:
        mutable std::mutex m_errorMutex;
        std::vector<SubscriptionInfo> m_failedSubscriptions;
};

}
