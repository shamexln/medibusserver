#pragma once

#include <S31/Test/Private/S31TestUtilsExImp.h>
#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/LoggerStateSaver.h>
#include <Framework/Log/Public/Message.h>

#include <mutex>
#include <vector>

namespace S31::Log
{

/**
 * @brief Intercept all messages sent to a given Logger to save them in a container.
 * @details Logging a message is thread safe.  Logger is added to the front of the chain
 * of loggers to avoid interfering with normal logging behavior.
 * @ingroup Log
 */
class S31_TESTUTILS_EXPIMP ThreadSafeLoggerSpy
{
    public:
        using Container = std::vector<DFL::Log::Message>;

        /**
         * @brief Constructs a mock for the given logger.
         */
        ThreadSafeLoggerSpy(DFL::Log::Logger& logger);

        /**
         * @brief Log a message
         */
        const DFL::Log::Message& operator()(const DFL::Log::Message& message);

        /**
         * @brief Get the so far intercepted messages.
         */
        Container messages() const;

        /**
         * @brief Clear the intercepted messages.
         */
        void clear();
    private:
        DFL::Log::LoggerStateSaver m_stateSaver;
        Container m_messages;
        mutable std::mutex m_mutex;
};

}
