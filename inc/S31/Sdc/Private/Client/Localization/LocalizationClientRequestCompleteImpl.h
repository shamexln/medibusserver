#pragma once

#include <S31/Sdc/Public/Client/LocalizationClientRequestComplete.h>

#include <condition_variable>
#include <mutex>

namespace S31::Sdc::Impl::LocalizationImpl
{

/**
 * @brief Implementation of @ref LocalizationClientRequestComplete
 * @ingroup S31SdcClient
 */
class LocalizationClientRequestCompleteImpl: public LocalizationClientRequestComplete
{
    public:
        bool waitForCompletion(const std::chrono::milliseconds& maxWaitTime) override;
        void registerCallback(const NotifyFunction& callback) override;

        /// Trigger notification about completion
        void complete();
    private:

        bool m_isCompleted = false;
        NotifyFunction m_callback;
        std::mutex m_mutex;
        std::condition_variable m_waitConditionVar;
};

}
