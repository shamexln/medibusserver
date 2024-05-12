#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Public/EventCode.h>
#include <Framework/Log/Public/SecurityState.h>
#include <Framework/Log/Public/Severities.h>
#include <Framework/Log/Public/Severity.h>
#include <Framework/Log/Public/Text.h>

#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Thread/Public/Thread.h>
#include <Framework/Utils/Public/Key.h>

#include <boost/optional.hpp>

#include <iosfwd>
#include <regex>
#include <string>
#include <tuple>

namespace DFL
{
namespace Log
{
class MessageBuilder;
/**
 * @brief Holds the attributes connected to a log message.
 *
 * Instances of this class traverse the process chain of a logger.
 * Once an object has been created it is immutable. To change an attribute one
 * has to construct a new message with modificated attributes.
 * For such tasks it is advised to use @ref DFL::Log::MessageBuilder.
 *
 * @snippet Log/Test/UnitTest/TestMessage.cpp protoBuilder
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP Message
{
public:
    /**
     * @brief The type of the text attribute of a message.
     */
    using TextType = Text;
    /**
     * @brief Creates a message with default values.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp DefaultCtor
     */
    Message() = default;
    /**
     * @brief Constructs a message from given attributes.
     *
     * Although this is a complete constructor which initializes every field
     * of a message it should be used very rarely.
     * Most of the times a new message is created from existing one.
     * Then please use the provided @ref DFL::Log::MessageBuilder for creating
     * messages.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp protoBuilder
     */
    Message(
        Severity msgSeverity,
        TextType msgText,
        Component::Key msgComponentKey,
        EventCode msgEventCode,
        const char* msgFile,
        int msgLine,
        const char* assembly,
        Chrono::SystemClock::TimePoint timestamp = Chrono::SystemClock::now(),
        SecurityState securityState = SecurityState::None,
        Thread::Id threadId = Thread::ThisThread::id());
    /**
     * @brief Equality comparison.
     *
     * Two messages are equal if all attributes except the timestamp are equal.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp Equality
     *
     * So why is the timestamp excluded. Because it is very volatile and thus
     * make it very unlikely that two messages will be equal.
     * The typical use-cases we could think of where two messages
     * are compared typically ignore the value of the timestamp
     * e.g. a log-spam-filter, checking that messages have been emitted, ...
     * and the fact that the timestamp attribute was added years after
     * all the other ones shows its importance.
     * Nonetheless if you have use-cases where the timestamp is important
     * than please use the @ref DFL::Log::MessageComparator.
     * There you can explicitly state which values of which attributes
     * are important for your comparison and which are not.
     * In general you could always use this utility since it frees you from
     * adapting your code if further attributes are added.
     */
    bool operator==(Message const& other) const;
    /**
     * @brief Returns !(*this == other);
     */
    bool operator!=(Message const& other) const;
    /**
     * @brief Getter for text attribute.
     * @return Text of message.
     */
    const TextType& text() const;
    /**
     * @brief Getter for file attribute.
     * @return Name of file where message was created.
     */
    char const* file() const;
    /**
     * @brief Getter for line attribute.
     * @return Line number where message was created.
     */
    int line() const;
    /**
     * @brief Getter for severity attribute.
     * @return Severity of message.
     */
    Severity severity() const;
    /**
     * @brief Getter for component key attribute.
     * @return Componentkey of this message.
     */
    Component::Key componentKey() const;
    /**
     * @brief Getter for event code attribute.
     * @return Event code of this message.
     */
    EventCode eventCode() const;
    /**
     * @brief Getter for the assembly attribute.
     * @return String which specifies the logging assembled component.
     */
    char const* assemblyId() const;
    /**
     * @brief Getter for the timestamp attribute.
     * @return Chrono::SystemClock::TimePoint which specifies the timestamp of
     * this message.
     */
    const Chrono::SystemClock::TimePoint& timestamp() const;
    /**
     * @brief Getter for the security state attribute.
     * @return Security state of this message.
     */
    SecurityState securityState() const;
    /**
     * @brief Getter for the thread id.
     * @return ID of thread in which this message was created.
     */
    Thread::Id threadId() const;

private:
    friend class MessageBuilder;

    TextType m_text{};
    std::string m_file{};
    int m_line{};
    Severity m_severity{Success};
    Component::Key m_componentKey{};
    EventCode m_eventCode{};
    std::string m_assemblyId{};
    Chrono::SystemClock::TimePoint m_timestamp{};
    SecurityState m_securityState{SecurityState::None};
    Thread::Id m_threadId{};
};
/**
 * @brief Offers a fluent interface for building message objects.
 *
 * This is especially useful when writing your own logging filter.
 * In most cases you just want to update only parts of the given message and
 * leave the rest as is.
 *
 * @snippet Log/Test/UnitTest/TestMessage.cpp protoBuilder
 *
 * This way one cannot forget to copy any attributes.
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP MessageBuilder
{
public:
    /**
     * @brief Creates a message with sane defaults.
     *
     * Sets the thread id to the one from the current thread and the timestamp
     * to now from the system clock.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp defaultBuilder
     */
    MessageBuilder();
    /**
     * @brief Copies all attributes of given message.
     *
     * Very useful when only parts of a message shall be updated, e.g. when
     * writing logging filter.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp protoBuilder
     */
    explicit MessageBuilder(Message msg);
    /**
     * @name Sets the according attribute of message to the given value.
     * @{
     */
    MessageBuilder& text(const Text& txt);
    MessageBuilder& file(const std::string& f);
    MessageBuilder& line(int l);
    MessageBuilder& severity(Severity sev);
    MessageBuilder& componentKey(const Component::Key& key);
    MessageBuilder& eventCode(EventCode evt);
    MessageBuilder& assemblyId(const std::string& assembly);
    MessageBuilder& timestamp(Chrono::SystemClock::TimePoint tp);
    MessageBuilder& securityState(SecurityState sec);
    MessageBuilder& threadId(Thread::Id id);
    /** @} */
    /**
     * @brief Returns a message with all configured attributes.
     */
    Message msg() const;
    /**
     * @brief "Returns" a message with all configured attributes.
     */
    /* implicit */ operator Message() const;

private:
    Message m_msg{};
};
/**
 * @brief Stores given message attributes and compares each given message
 * against those attributes.
 *
 * This is useful if you are only interested in some particular attributes of a
 * message:
 *
 * @snippet Log/Sample/Sample.cpp UsageMockLogger
 *
 * On the other hand if you want to check that all attributes have been left
 * unchanged and only some have been updated:
 *
 * @snippet Log/Test/UnitTest/TestMessage.cpp protoBuilder
 *
 * A default constructed instance always returns true no matter what message it
 * is compared to.
 *
 * @ingroup Log
 */
class DFL_LOG_EXPIMP MessageComparator
{
public:
    /**
     * @brief Type of std::ignore used to ignore message fields to be compared.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp cmpIgnore
     */
    using IgnoreType = decltype(std::ignore);
    /**
     * @brief Always returns true no matter what message it is compared to if no
     * further attributes are set.
     */
    MessageComparator() = default;
    /**
     * @brief "Copies" all attributes of given message to be compared.
     *
     * This is useful if you want to check that all attributes have been left
     * unchanged and only some have been updated.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp protoBuilder
     */
    explicit MessageComparator(const Message& msg);
    /**
     * @name Sets message attributes that shall be used for comparison.
     *
     * @{
     */
    MessageComparator& severity(Severity s);
    MessageComparator& text(const Text& t);
    MessageComparator& textMatch(const std::regex& re);
    MessageComparator& componentKey(const Component::Key& k);
    MessageComparator& eventCode(EventCode ec);
    MessageComparator& assemblyId(const std::string& assembly);
    MessageComparator& timestamp(Chrono::SystemClock::TimePoint tp);
    MessageComparator& securityState(SecurityState sec);
    MessageComparator& line(int l);
    MessageComparator& file(const std::string& f);
    MessageComparator& threadId(Thread::Id id);
    /** @} */
    /**
     * @name Sets the attribute to be ignored on comparison.
     *
     * @snippet Log/Test/UnitTest/TestMessage.cpp cmpIgnore
     *
     * @{
     */
    MessageComparator& severity(IgnoreType);
    MessageComparator& text(IgnoreType);
    MessageComparator& componentKey(IgnoreType);
    MessageComparator& eventCode(IgnoreType);
    MessageComparator& assemblyId(IgnoreType);
    MessageComparator& timestamp(IgnoreType);
    MessageComparator& securityState(IgnoreType);
    MessageComparator& line(IgnoreType);
    MessageComparator& file(IgnoreType);
    MessageComparator& threadId(IgnoreType);
    /** @} */
    /**
     * @brief Returns success if attributes of given message match stored
     * attributes, otherwise failure.
     */
    bool operator()(const Message& msg) const;

private:
    friend DFL_LOG_EXPIMP std::ostream& operator<<(
        std::ostream& out,
        const MessageComparator& msg);

    boost::optional<Severity> m_severity{};
    boost::optional<Text> m_text{};
    boost::optional<std::regex> m_regex{};
    boost::optional<Component::Key> m_componentKey{};
    boost::optional<EventCode> m_eventCode{};
    boost::optional<std::string> m_assembly{};
    boost::optional<Chrono::SystemClock::TimePoint> m_timestamp{};
    boost::optional<SecurityState> m_securityState{};
    boost::optional<int> m_line{};
    boost::optional<std::string> m_file{};
    boost::optional<Thread::Id> m_threadId{};
};
/**
 * @name Sets the according attribute of message to the given value.
 *
 * @snippet Log/Test/UnitTest/TestMessage.cpp MsgCmp
 *
 * @{
 */
DFL_LOG_EXPIMP bool operator==(const MessageComparator& msgCmp,
                               const Message& msg);
DFL_LOG_EXPIMP bool operator==(const Message& msg,
                               const MessageComparator& msgCmp);
DFL_LOG_EXPIMP bool operator!=(const MessageComparator& msgCmp,
                               const Message& msg);
DFL_LOG_EXPIMP bool operator!=(const Message& msg,
                               const MessageComparator& msgCmp);
/** @} */
}
}
