#pragma once

#include <atomic>
#include <iterator>
#include <mutex>
#include <string>
#include <vector>

namespace S31::Log::Impl
{
/**
 * @brief Buffer for log messages.
 * @details This is thread safe except for reading.
 * @ingroup S31Log
 */
class MessageBuffer
{
        const int MessageBufferSize = 20;
        using RawMessageBuffer = std::vector<std::string>;
    public:
        MessageBuffer() :
                m_buffer(static_cast<RawMessageBuffer::size_type>(MessageBufferSize)),
                m_lastElement(-1),
                m_overflow(false)
        {}

        void push_back(std::string&& msg)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_lastElement < MessageBufferSize - 1)
            {
                m_lastElement++;
                m_buffer[static_cast<RawMessageBuffer::size_type>(m_lastElement)] = std::move(msg);
            }
            else
            {
                m_overflow = true;
            }
        }

        bool overflow() const
        {
            return m_overflow;
        }

        bool empty() const
        {
            return m_lastElement < 0;
        }

        void clear()
        {
            m_lastElement = -1;
            m_overflow = false;
        }

        friend void swap(MessageBuffer& lhs, MessageBuffer& rhs)
        {
            if (&lhs == &rhs)
            {
                return;
            }
            std::lock(lhs.m_mutex, rhs.m_mutex);
            std::lock_guard<std::mutex> lockL(lhs.m_mutex, std::adopt_lock);
            std::lock_guard<std::mutex> lockR(rhs.m_mutex, std::adopt_lock);
            {
                int temp = lhs.m_lastElement;
                lhs.m_lastElement = static_cast<int>(rhs.m_lastElement);
                rhs.m_lastElement = temp;
            }
            {
                bool temp = lhs.m_overflow;
                lhs.m_overflow = static_cast<bool>(rhs.m_overflow);
                rhs.m_overflow = temp;
            }
            std::swap(lhs.m_buffer, rhs.m_buffer);
        }

        RawMessageBuffer::iterator begin()
        {
            return m_buffer.begin();
        }

        RawMessageBuffer::iterator end()
        {
            auto end = m_buffer.begin();
            std::advance(end, m_lastElement + 1);
            return end;
        }

    private:
        mutable std::mutex m_mutex;
        std::vector<std::string> m_buffer;
        std::atomic_int m_lastElement;
        std::atomic_bool m_overflow;

};

}
