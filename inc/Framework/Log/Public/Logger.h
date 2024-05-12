#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Private/Loggers.h>
#include <Framework/Log/Public/Severities.h>
#include <Framework/Log/Public/Severity.h>

#include <string>

/**
 * @ingroup Log
 * @{
 */
namespace DFL
{
namespace Log
{

/**
 * @brief Keeps a pipe with filter to process a message.
 *
 * Logger itself is a filter too. This makes it possible
 * to put the complete pipe of a logger into the pipe of
 * another one.
 */
class DFL_LOG_EXPIMP Logger
{
public:
    /**
     * @brief Type representing the name of a logger.
     */
    using NameType = std::string;

    /**
     * @brief Type of a filter in the message process pipe.
     */
    using LoggerType = Impl::Loggers::value_type;

    /**
     * @brief Constructs a logger without a name.
     *
     * @snippet Log/Test/UnitTest/TestLogger.cpp Ctor
     */
    Logger() = default;

    /**
     * @brief Constructs a logger with given name.
     *
     * @snippet Log/Test/UnitTest/TestLogger.cpp CtorName
     */
    explicit Logger(NameType loggerName);

    /**
     * @brief Uses given logger as a prototype and gives it a new name.
     *
     * @snippet Log/Test/UnitTest/TestLogger.cpp CtorProto
     */
    Logger(Logger const& other, NameType loggerName);

    /**
     * @brief Kicks of the message processing pipe.
     * @param m The message to be processed by the pipe.
     * @return The complete processed message.
     */
    Message operator()(Message const& m) const;

    /**
     * @brief Returns the name of a logger.
     * @return Name of logger.
     */
    NameType name() const;

    /**
     * @brief Compares severity of this logger with s.
     * @param s Severity to be compared with this severity.
     * @return True as long as given severity is higher or equal to the
     * severity of this logger. Otherwise false.
     */
    bool is(Severity const& s) const;

    /**
     * @brief Returns currently configured severity.
     *
     * It does not tell you if a message with the returned severity
     * would be logged. If you want to know that
     * than please use @ref DFL::Log::Logger::is.
     */
    Severity severity() const;

    /**
     * @brief Clear the pipe.
     */
    void clear();

    /**
     * @brief A new filter is added to the front of the pipe.
     * @param newLogger New filter to be at the front of pipe.
     */
    void pushFront(LoggerType const& newLogger);

    /**
     * @brief A new filter is added to the back of the pipe.
     * @param newLogger New filter to be at the back of pipe.
     */
    void pushBack(LoggerType newLogger);

    /**
     * @brief Sets the severity of this logger.
     * @param s The new severity of this logger.
     */
    void severity(Severity const& s);

    /**
     * @brief Disables the logger.
     *
     * No messages are forwarded to the pipe anymore.
     */
    void disable();

    /**
     * @brief Enables logger.
     *
     * Messages are forwarded to the pipe.
     */
    void enable();

    /**
     * @brief Checks if logger is enabled.
     * @return True if logger was enabled using Logger::enable();
     * false if logger was disabled using Logger::disable().
     */
    bool enabled() const;

private:
    Impl::Loggers m_loggers{};
    Severity m_severity{Success};
    bool m_enabled{true};
    NameType m_name{};
};

}
}
/** @} */
