#pragma once

#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingNotifyJob.h>

#include <Framework/Chrono/Public/SteadyClock.h>

#include <boost/optional/optional.hpp>

#include <deque>
#include <memory>
#include <mutex>

namespace S31::Sdc::Impl
{
/**
 * @brief Handles the logic for maintaining notification of a subscription.
 * @details
 * It takes care that
 * - only one event message at a time will be notified (is in transfer) and
 * - events are notified within 5 seconds (watchdog).
 * @ingroup S31SdcDevice
 */
class NotificationQueue
{
    public:
        /**
         * @brief Constructor to initialize the maximum size of the queue.
         */
        explicit NotificationQueue(unsigned int maxQueueSize);
        /**
         * @brief Add an event to the queue.
         * @details In the case that the queue is full, the event is not added. i.e. pushing
         * events is no longer possible.
         */
        void pushEvent(std::unique_ptr<WSEventingNotifyJob> event);

        /**
         * @brief Provides an event in case one shall be transmitted right now.
         * @details Return \c nullptr in case
         * - an event is in transmission (\ref notifyTransmissionSucceeded() not called)
         * - there is no event in the queue or
         * - the queue already timed out.
         */
        std::unique_ptr<WSEventingNotifyJob> popPendingEvent();

        /**
         * @brief Call this function when last popped event was delivered successfully.
         */
        void notifyTransmissionSucceeded();


        /**
         * @name Watchdog/Timeout handling
         * @{
         */

        /**
         * @brief Returns \c true iff event notification failed within time.
         */
        bool timeout() const;

        /**
         * @brief Provides time point for next timeout check.
         */
        DFL::Chrono::SteadyClock::TimePoint nextTimeoutCheckAt() const;
        /** @} */

        /**
         * @brief Returns true if the queue is full else false.
         */
        bool overflowed() const;

    private:

        void checkTimeoutNoLock() const;

        mutable std::mutex m_mutex;
        mutable bool m_timeout = false;
        bool m_overflow = false;
        bool m_eventInTransmission = false;
        boost::optional<DFL::Chrono::SteadyClock::TimePoint> m_nextTimeout;

        struct JobData
        {
                DFL::Chrono::SteadyClock::TimePoint arrivalTime;
                std::unique_ptr<WSEventingNotifyJob> job;
        };
        std::deque<JobData> m_pendingEvents;
        const unsigned int m_maxQueueSize;
        unsigned int m_totalEventCount{};
};

}
