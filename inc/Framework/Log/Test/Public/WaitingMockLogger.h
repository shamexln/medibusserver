#pragma once

#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/LoggerStateSaver.h>
#include <chrono>
#include <condition_variable>
#include <mutex>

namespace DFL
{
namespace Log
{
namespace Test
{
/**
 * @brief Mocks a given Logger by checking all messages against a predicate function.
 * @ingroup Log
 */
class WaitingMockLogger
{
    public:
        /**
         * @brief Constructs a mock for the given logger with predicate function.
         */
        WaitingMockLogger(Logger& logger, std::function<bool(const Message& message)> predicate);

        /**
         * @brief Operator to handle log messages.
         */
        Message operator()(const Message& message);

        /**
         * @brief Wait until given predicate from constructor is matched or time out.
         */
        bool found(std::chrono::milliseconds waitTime);

    private:
        mutable std::mutex m_mutex;
        mutable std::condition_variable m_conditionVariable;
        bool m_found = false;
        std::function<bool(const Message& message)> m_predicate;
        LoggerStateSaver m_stateSaver;
};

inline WaitingMockLogger::WaitingMockLogger(Logger& logger, std::function<bool(const Message& message)> predicate) :
        m_predicate(std::move(predicate)),
        m_stateSaver(logger)
{
    logger.clear();
    logger.pushBack(std::ref(*this));
}

inline Message WaitingMockLogger::operator()(const Message& message)
{
    if (m_predicate(message))
    {
        {
            std::unique_lock<std::mutex> const lock(m_mutex);
            m_found = true;
        }
        m_conditionVariable.notify_all();
    }
    return message;
}

inline bool WaitingMockLogger::found(std::chrono::milliseconds waitTime)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_found)
    {
        return true;
    }
    return m_conditionVariable.wait_for(lock, waitTime, [this]() { return m_found; });
}

}
}
}
