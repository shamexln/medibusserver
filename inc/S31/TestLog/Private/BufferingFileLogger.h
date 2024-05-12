#pragma once

#include <Framework/Log/Public/Message.h>
#include <Framework/Utils/Public/NotNull.h>

namespace S31::Log::Impl
{
class FileLoggerData;
class MessageBuffer;

/**
 * @brief A logger with a buffer to avoid 'block through log'.
 * @details The buffer size is limited. If the buffer is full then additional messages are dropped. An according
 * message is logged. On shutdown the remaining buffered messages are dropped also. The buffering is done only if
 * the logfile write access is not available.
 */
class BufferingFileLogger
{
    public:
        explicit BufferingFileLogger(DFL::NotNull<std::shared_ptr<FileLoggerData>> fileLoggerData);

        /**
         * @brief Functor for DFL logging
         *
         * @param message the message to be printed
         */
        const DFL::Log::Message& operator()(const DFL::Log::Message& message) const;

    private:
        DFL::NotNull<std::shared_ptr<FileLoggerData>> m_fileLoggerData;

        // There are 2 message buffers (used in a double buffer pattern)
        // These are shared_ptr to have MessageBuffer as incomplete type
        DFL::NotNull<std::shared_ptr<MessageBuffer>> m_messageBufferWrite;
        DFL::NotNull<std::shared_ptr<MessageBuffer>> m_messageBufferRead;
};
}
