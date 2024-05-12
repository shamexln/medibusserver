#pragma once

#include <S31/Log/Public/Logger.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <regex>

namespace S31::Sdc::Test
{

/**
 * @brief Base class for matchers.
 * @details To match the content of service log mmessages.
 */
class TextMatcher
{
    public:
        explicit TextMatcher(std::string pattern):
            m_pattern(std::move(pattern))
        {}

        virtual ~TextMatcher() = default;

        virtual bool match(const std::string& text) const = 0;

        const std::string& pattern() const&
        {
            return m_pattern;
        }

        std::string& pattern() &&
        {
            return m_pattern;
        }

    private:
        std::string m_pattern;
};

/**
 * @brief Uses std::regex_match for pattern matching.
 */
class RegexMatch: public TextMatcher
{
    public:
        using TextMatcher::TextMatcher;

        bool match(const std::string& text) const override
        {
            return std::regex_match(text, std::regex(pattern()));
        }
};

/**
 * @brief Matcher for substrings.
 */
class SubString: public TextMatcher
{
    public:
        using TextMatcher::TextMatcher;

        bool match(const std::string& text) const override
        {
            return text.find(pattern()) != std::string::npos;
        }
};

/**
 * @brief Matcher requires equality.
 */
class Equals: public TextMatcher
{
    public:
        using TextMatcher::TextMatcher;

        bool match(const std::string& text) const override
        {
            return text == pattern();
        }
};

/**
 * @brief Matches everything
 */
class Any: public TextMatcher
{
    public:
        Any() :
            TextMatcher("")
        {}

        using TextMatcher::TextMatcher;

        bool match(const std::string& /*text*/) const override
        {
            return true;
        }
};

/**
 * @brief Enum indicating the the status of the invocation
 * @ingroup S31SdcCommon
 */
enum class InvocationStatus
{
    NotInvoked, ///< Message has not been invoked yet.
    Invoked ///< Message has been invoked.
};

class LogMessageInvocation;
using LogMessageInvocationPtr = std::shared_ptr<LogMessageInvocation>;

/**
 * @brief Helper class to keep track of the log message invocation status
 * @ingroup S31SdcCommon
 */
class LogMessageInvocation
{
    public:
        /// Factory function to get a LogMessageInvocation in a shared_ptr.
        static LogMessageInvocationPtr make()
        {
            class LogMessageInvocationPublicCtor : public LogMessageInvocation
            {
                public:
                    using LogMessageInvocation::LogMessageInvocation;
            };

            return std::make_shared<LogMessageInvocationPublicCtor>();
        }

        /**
         * @brief Resets the invocation status to InvocationStatus::NotInvoked.
         */
        void resetInvocationStatus()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_invocationStatus = InvocationStatus::NotInvoked;
        }

        /**
         * @brief Sets the invocation status to InvocationStatus::Invoked and notifies all threads waiting for this condition.
         */
        void setInvocationStatus()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_invocationStatus = InvocationStatus::Invoked;
            m_cond.notify_all();
        }

        /**
         * @brief Checks whether the hook's invocation status is \ref S31::Sdc::Test::InvocationStatus::Invoked "invoked".
         * @details Checks at the beginning. If that check fails, this function waits for either the thread to be notified or timer to expire and then checks again.
         * @returns true if invocation status is InvocationStatus::Invoked, false otherwise.
         */
        bool isLogMessageInvoked() const
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            bool result = (m_invocationStatus == InvocationStatus::Invoked);
            if (!result)
            {
                result = m_cond.wait_for(lock, std::chrono::seconds(10), [&]{return m_invocationStatus == InvocationStatus::Invoked;});
            }
            S31_STREAM_INFO_LOGGER("Test", "isLogMessageInvoked() result is ", result ? "True" : "False");
            return result;
        }

        /**
         * @brief Sets the invocation status to InvocationStatus::Invoked if the regex pattern matches.
         * @param messageTxt input message.
         * @param matcher matcher for the given message.
         */
        void setInvocationStatusIfMessageMatches(const std::string& messageTxt, const TextMatcher& matcher)
        {
            if (matcher.match(messageTxt))
            {
                setInvocationStatus();
            }
            else
            {
                S31_STREAM_WARN_LOGGER("Test", "Service log message does not match pattern.'");
                S31_STREAM_WARN_LOGGER("Test", "Pattern:'", matcher.pattern(), "'");
                S31_STREAM_WARN_LOGGER("Test", "Service log message:'", messageTxt, "'");
            }
        }

    protected:
        /**
         * @brief Constructor to initialize invocation status to InvocationStatus::NotInvoked.
         */
        LogMessageInvocation() :
                m_invocationStatus(InvocationStatus::NotInvoked)
        {}

    private:

        InvocationStatus m_invocationStatus;
        mutable std::mutex m_mutex;
        mutable std::condition_variable m_cond;
};

}
