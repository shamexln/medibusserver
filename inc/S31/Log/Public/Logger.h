#pragma once


#include <S31/Log/Private/StreamLogger.h>
#include <S31/Log/Public/LoggerHelper.h>

#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/Severity.h>

#include <atomic>
#include <map>
#include <string_view>

namespace S31
{

/**
 * @name LogLevel
 * @brief Set/get the main log level for the component loggers.
 * @details
 * This log level is used for all logger that are not individually configured.
 * This works at runtime.
 * @ingroup S31Log
 */
///@{
/// Set log level given by severity.
void S31_LOG_EXPIMP setLogLevel(DFL::Log::Severity logLevel);

/// Set log level given by severity string.
void S31_LOG_EXPIMP setLogLevel(const std::string& logLevel);

/// Get log level.
DFL::Log::Severity S31_LOG_EXPIMP getLogLevel();
///@}

/**
 * @name ComponentLogLevels
 * @brief Set/get the log levels for single components as a comma-separated string of components=log level pairs.
 * @details E.g.: "S31.DateTime=3,S31.Waveforms=4".
 * Replaces the old configuration. This works at runtime and updates all the existing component loggers.
 * This works at runtime. When calling getLogLevels(), only the log levels of initialized component loggers are returned.
 * @ingroup S31Log
 */
///@{
/// Set component log levels.
void S31_LOG_EXPIMP setLogLevels(const std::string& componentLogLevels);

/// Get component log levels.
std::map<std::string, DFL::Log::Severity> S31_LOG_EXPIMP getLogLevels();
///@}

/**
 * @def S31_LOGGER_NAME
 *
 * @brief Declaration name of the local logger.
 */
#define S31_LOGGER_NAME s31Logger()

#define S31_CHECK_SEVERITY_BEGIN(S) do { if (S31_LOGGER_NAME.is(DFL::Log::S)) {
#define S31_CHECK_SEVERITY_END }} while(0)

#ifdef DEBUG
#define S31_CHECK_SEVERITY_LOGGER_BEGIN(logger, S) do { if (S31::Log::Impl::ComponentLogger::getComponentLogger(logger).is(DFL::Log::S)) {
#else
// In release builds we assume that logging always works
// to allow to log in catch blocks
#define S31_CHECK_SEVERITY_LOGGER_BEGIN(logger, S) do { \
bool logIt = true; try { logIt = S31::Log::Impl::ComponentLogger::getComponentLogger(logger).is(DFL::Log::S); } catch (...) {} \
if (logIt) {
#endif
#define S31_CHECK_SEVERITY_LOGGER_END }} while(0)

/// @brief Logs with log level trace.
/// @ingroup S31Log
#define S31_STREAM_TRACE(...) S31_CHECK_SEVERITY_BEGIN(Trace) S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Trace, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_END

/// @brief Logs with log level info.
/// @ingroup S31Log
#define S31_STREAM_INFO(...) S31_CHECK_SEVERITY_BEGIN(Info) S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Info, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_END

/// @brief Logs with log level warning.
/// @ingroup S31Log
#define S31_STREAM_WARN(...) S31_CHECK_SEVERITY_BEGIN(Warning) S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_END

/// @brief Logs with log level success.
/// @details Log level success is between info and trace.
/// @ingroup S31Log
#define S31_STREAM_SUCCESS(...) S31_CHECK_SEVERITY_BEGIN(Success) S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Success, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_END

/// @brief Logs with log level error.
/// @ingroup S31Log
#define S31_STREAM_ERROR(...) S31_CHECK_SEVERITY_BEGIN(Error) S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_END


/// @brief Short-cut log macro to log the current function name.
/// @ingroup S31Log
#define S31_STREAM_TRACE_F() S31_STREAM_TRACE(__func__, "()")

/// @brief Short-cut log macro to log the current function name.
/// @ingroup S31Log
#define S31_STREAM_SUCCESS_F() S31_STREAM_SUCCESS(__func__, "()")

/// @brief Short-cut log macro to log the current function name.
/// @ingroup S31Log
#define S31_STREAM_INFO_F() S31_STREAM_INFO(__func__, "()")

/// @brief Short-cut log macro to log the current function name.
/// @ingroup S31Log
#define S31_STREAM_WARN_F() S31_STREAM_WARN(__func__, "()")

/// @brief Short-cut log macro to log the current function name.
/// @ingroup S31Log
#define S31_STREAM_ERROR_F() S31_STREAM_ERROR(__func__, "()")

/// @brief Short-cut log macro to log the current function name with given parameters.
/// @details #S31_STREAM_TRACE_P("param") is a short-cut for #S31_STREAM_TRACE("foo(param)")
/// @ingroup S31Log
#define S31_STREAM_TRACE_P(...) S31_STREAM_TRACE(__func__, "(", __VA_ARGS__, ")")

/// @brief Short-cut log macro to log the current function name with given parameters.
/// @details #S31_STREAM_SUCCESS_P("param") is a short-cut for #S31_STREAM_SUCCESS("foo(param)")
/// @ingroup S31Log
#define S31_STREAM_SUCCESS_P(...) S31_STREAM_SUCCESS(__func__, "(", __VA_ARGS__, ")")

/// @brief Short-cut log macro to log the current function name with given parameters.
/// @details #S31_STREAM_INFO_P("param") is a short-cut for #S31_STREAM_INFO("foo(param)")
/// @ingroup S31Log
#define S31_STREAM_INFO_P(...) S31_STREAM_INFO(__func__,"(", __VA_ARGS__, ")")

/// @brief Short-cut log macro to log the current function name with given parameters.
/// @details #S31_STREAM_WARN_P("param") is a short-cut for #S31_STREAM_WARN("foo(param)")
/// @ingroup S31Log
#define S31_STREAM_WARN_P(...) S31_STREAM_WARN(__func__, "(", __VA_ARGS__, ")")

/// @brief Short-cut log macro to log the current function name with given parameters.
/// @details #S31_STREAM_ERROR_P("param") is a short-cut for #S31_STREAM_ERROR("foo(param)")
/// @ingroup S31Log
#define S31_STREAM_ERROR_P(...) S31_STREAM_ERROR(__func__, "(", __VA_ARGS__, ")")


/// @brief Short-cut log macro to log the current function as prefix.
/// @details #S31_STREAM_TRACE_M("message") is a short-cut for #S31_STREAM_TRACE("foo(): message")
/// @ingroup S31Log
#define S31_STREAM_TRACE_M(...) S31_STREAM_TRACE(__func__, "(): ", __VA_ARGS__)

/// @brief Short-cut log macro to log the current function as prefix.
/// @details #S31_STREAM_SUCCESS_M("message") is a short-cut for #S31_STREAM_SUCCESS("foo(): message")
/// @ingroup S31Log
#define S31_STREAM_SUCCESS_M(...) S31_STREAM_SUCCESS(__func__, "(): ", __VA_ARGS__)

/// @brief Short-cut log macro to log the current function as prefix.
/// @details #S31_STREAM_INFO_M("message") is a short-cut for #S31_STREAM_INFO("foo(): message")
/// @ingroup S31Log
#define S31_STREAM_INFO_M(...) S31_STREAM_INFO(__func__, "(): ", __VA_ARGS__)

/// @brief Short-cut log macro to log the current function as prefix.
/// @details #S31_STREAM_WARN_M("message") is a short-cut for #S31_STREAM_WARN("foo(): message")
/// @ingroup S31Log
#define S31_STREAM_WARN_M(...) S31_STREAM_WARN(__func__, "(): warning: ", __VA_ARGS__)

/// @brief Short-cut log macro to log the current function as prefix.
/// @details #S31_STREAM_ERROR_M("message") is a short-cut for #S31_STREAM_ERROR("foo(): message")
/// @ingroup S31Log
#define S31_STREAM_ERROR_M(...) S31_STREAM_ERROR(__func__, "(): error: ", __VA_ARGS__)


/// @name short-cut log macros for gtest test fixtures
/// @ingroup S31Log
///@{
#define S31_STREAM_TRACE_TF() S31_STREAM_TRACE(::testing::UnitTest::GetInstance()->current_test_info()->name(), "()")
#define S31_STREAM_SUCCESS_TF() S31_STREAM_SUCCESS(::testing::UnitTest::GetInstance()->current_test_info()->name(), "()")
#define S31_STREAM_INFO_TF() S31_STREAM_INFO(::testing::UnitTest::GetInstance()->current_test_info()->name(), "()")
#define S31_STREAM_WARN_TF() S31_STREAM_WARN(::testing::UnitTest::GetInstance()->current_test_info()->name(), "()")
#define S31_STREAM_ERROR_TF() S31_STREAM_ERROR(::testing::UnitTest::GetInstance()->current_test_info()->name(), "()")

#define S31_STREAM_TRACE_TP(...) S31_STREAM_TRACE(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(", __VA_ARGS__, ")")
#define S31_STREAM_SUCCESS_TP(...) S31_STREAM_SUCCESS(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(", __VA_ARGS__, ")")
#define S31_STREAM_INFO_TP(...) S31_STREAM_INFO(::testing::UnitTest::GetInstance()->current_test_info()->name(),"(", __VA_ARGS__, ")")
#define S31_STREAM_WARN_TP(...) S31_STREAM_WARN(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(", __VA_ARGS__, ")")
#define S31_STREAM_ERROR_TP(...) S31_STREAM_ERROR(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(", __VA_ARGS__, ")")

#define S31_STREAM_TRACE_TM(...) S31_STREAM_TRACE(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(): ", __VA_ARGS__)
#define S31_STREAM_SUCCESS_TM(...) S31_STREAM_SUCCESS(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(): ", __VA_ARGS__)
#define S31_STREAM_INFO_TM(...) S31_STREAM_INFO(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(): ", __VA_ARGS__)
#define S31_STREAM_WARN_TM(...) S31_STREAM_WARN(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(): warning: ", __VA_ARGS__)
#define S31_STREAM_ERROR_TM(...) S31_STREAM_ERROR(::testing::UnitTest::GetInstance()->current_test_info()->name(), "(): error: ", __VA_ARGS__)
///@}

/// @name short-cut log macros for lambdas
/// @details The lambda versions of the short-cut log macros.<br>
/// They expect the function name stored in a variable 'func'.
/// \code{.cpp}
///   auto func = __func__;
///   [func]()
///   {
///       S31_STREAM_TRACE_LF();
///   }
/// \endcode
/// @ingroup S31Log
///@{
#define S31_STREAM_TRACE_LF() S31_STREAM_TRACE(func, "()")
#define S31_STREAM_SUCCESS_LF() S31_STREAM_SUCCESS(func, "()")
#define S31_STREAM_INFO_LF() S31_STREAM_INFO(func, "()")
#define S31_STREAM_WARN_LF() S31_STREAM_WARN(func, "()")
#define S31_STREAM_ERROR_LF() S31_STREAM_ERROR(func, "()")

#define S31_STREAM_TRACE_LP(...) S31_STREAM_TRACE(func, "(", __VA_ARGS__, ")")
#define S31_STREAM_SUCCESS_LP(...) S31_STREAM_SUCCESS(func, "(", __VA_ARGS__, ")")
#define S31_STREAM_INFO_LP(...) S31_STREAM_INFO(func,"(", __VA_ARGS__, ")")
#define S31_STREAM_WARN_LP(...) S31_STREAM_WARN(func, "(", __VA_ARGS__, ")")
#define S31_STREAM_ERROR_LP(...) S31_STREAM_ERROR(func, "(", __VA_ARGS__, ")")

#define S31_STREAM_TRACE_LM(...) S31_STREAM_TRACE(func, "(): ", __VA_ARGS__)
#define S31_STREAM_SUCCESS_LM(...) S31_STREAM_SUCCESS(func, "(): ", __VA_ARGS__)
#define S31_STREAM_INFO_LM(...) S31_STREAM_INFO(func, "(): ", __VA_ARGS__)
#define S31_STREAM_WARN_LM(...) S31_STREAM_WARN(func, "(): warning: ", __VA_ARGS__)
#define S31_STREAM_ERROR_LM(...) S31_STREAM_ERROR(func, "(): error: ", __VA_ARGS__)
///@}

/// @name header file log macros
/// @details Use this macros to log in header files.
/// @ingroup S31Log
///@{
#define S31_STREAM_TRACE_LOGGER(loggername, ...) S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Trace) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Trace, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_LOGGER_END
#define S31_STREAM_INFO_LOGGER(loggername, ...) S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Info) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Info, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_LOGGER_END
#define S31_STREAM_WARN_LOGGER(loggername, ...) S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Warning) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_LOGGER_END
#define S31_STREAM_ERROR_LOGGER(loggername, ...) S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Error) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_LOGGER_END
#define S31_STREAM_SUCCESS_LOGGER(loggername, ...) S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Success) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Success, __FILE__, __LINE__, __VA_ARGS__); S31_CHECK_SEVERITY_LOGGER_END
///@}

namespace Impl
{

/**
 * @brief The maximum number of occurrences of limited log messages.
 *
 * @details
 * E.g.: Useful for messages like "unit not convertible" which if they happen they may happen
 * multiple times per second. With this type of log there are only 50 of such log messages.
 *
 * \ingroup S31Log
 */
static const int NumberOfOccurrencesIfLimitedLogMessages = 50;

static const char* const LastLogMessageHere = "[last message from this log point] ";

using LimitedLogMessagesInt = std::atomic_int;

}

/*!
 * @name component logs limited
 * Macro to log a service log entry for an error/waring/information.
 *
 * Messages of this type have limited occurrences in the log (per log point in the source).
 *
 * \ingroup S31Log
 */
///@{
///
#define S31_STREAM_ERROR_LIMITED(...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31_CHECK_SEVERITY_BEGIN(Error) \
    if (logCountLeft > 0) { \
    S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__); \
    } else { \
    S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Error, __FILE__, __LINE__, S31::Impl::LastLogMessageHere, __VA_ARGS__); \
    } \
    S31_CHECK_SEVERITY_END;} \
    } while (0)

#define S31_STREAM_WARN_LIMITED(...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31_CHECK_SEVERITY_BEGIN(Error) \
    if (logCountLeft > 0) { \
    S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); \
    } else { \
    S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Warning, __FILE__, __LINE__, S31::Impl::LastLogMessageHere, __VA_ARGS__); \
    } \
    S31_CHECK_SEVERITY_END;} \
    } while (0)

#define S31_STREAM_WARN_LIMITED_M(...) S31_STREAM_WARN_LIMITED(__func__, "(): warning: ", __VA_ARGS__)

#define S31_STREAM_INFO_LIMITED(...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31_CHECK_SEVERITY_BEGIN(Error) \
    if (logCountLeft > 0) { \
    S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Info, __FILE__, __LINE__, __VA_ARGS__); \
    } else { \
    S31::Log::Impl::writeStreamLogMessage(S31_LOGGER_NAME, DFL::Log::Info, __FILE__, __LINE__, S31::Impl::LastLogMessageHere, __VA_ARGS__); \
    } \
    S31_CHECK_SEVERITY_END;} \
    } while (0)

#define S31_STREAM_ERROR_LOGGER_LIMITED(loggername, ...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Error) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__);S31_CHECK_SEVERITY_LOGGER_END;} \
    } while (0)

#define S31_STREAM_WARN_LOGGER_LIMITED(loggername, ...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31_CHECK_SEVERITY_LOGGER_BEGIN(loggername, Warning) S31::Log::Impl::writeStreamLogMessageToLoggerByName(loggername, DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__);S31_CHECK_SEVERITY_LOGGER_END;} \
    } while (0)

///@}

/*!
 * @brief Compile time check if logger name is in list of valid logger
 *
 * @ingroup S31Log
 */
struct LoggerName
{
    /*!
    * @brief Generic test if string is in list of strings
    */
    template <typename... Strings>
    static constexpr bool contains(std::string_view str, Strings... strings)
    {
        return ((str == strings) || ...);
    }

    /*!
    * @brief Check if name is in list of valid logger names
    *
    * @param name Logger name
    *
    * @return true if logger name is valid
    */
    static constexpr bool isValid(std::string_view name)
    {
        return contains(name, "Adt", "Test.Alert", "PI.Alert", "Alert", "Asio", "AsioDispatch", "Test.AudioPause", "PI.AudioPause", "AudioPause", "Test.ColorScheme", "PI.ColorScheme", "ColorScheme",
            "Test.Config", "Config", "PI.DateTime", "Test.Datetime", "DateTime", "PI.Device", "Device", "DualChannel", "Test.Error", "Error", "Expat", "Incoming", "Localization", "PI.Location", "Location",
            "Mdib", "Test.Measurement", "PI.Measurement", "Measurement", "PI.Metric", "Metric", "MultiDevice", "Test.Mib", "PI.Mib", "Mib", "PI.Mdib", "Mdib", "Nomenclature", "Osf", "Parsing",
            "Test.Patient", "PI.Patient", "Patient", "Test.RecruitmentTab", "PI.RecruitmentTab", "RecruitmentTab", "Scheduling", "Test.Sdc", "PI.Sdc", "Sdc", "Sdc.Test", "Sdc.Client",
            "Test.Sdc.Device", "PI.Sdc.Device","Sdc.Device", "SetService", "PI.Setting", "Setting", "Soap", "Soap.Interface", "Soap.Mapper", "Soap.WS",  "PI.SystemState", "SystemState", "Test",
            "Datetime", "Test.Ntp", "Ntp", "TestDevice", "Test.Utils", "PI.Utils", "Utils", "Test.Waveform", "Test.Waveform", "PI.Waveform", "Waveform");
    }
};

/*!
 * \def S31_LOGGER(FNC, LOGGER)
 *
 * Short-hand macro to produce a file scoped variable as defined in FNC that catches the component logger
 * defined by the LOGGER argument of the macro.
 *
 * Afterwards, you can use this function in your CPP file to retrieve the logger with name "MyComponent".
 *
 * The static_assert at the end forces a semicolon.
 *
 * \ingroup S31Log
 */
#define S31_LOGGER_(FNC, LOGGER) \
    static DFL::Log::Logger& FNC { \
        static_assert(S31::LoggerName::isValid(LOGGER), "Loggername not valid."); \
        static DFL::Log::Logger& logger = S31::Log::Impl::ComponentLogger::getComponentLogger(LOGGER); return logger; } \
    static_assert(true)

/*!
 * \def S31_LOGGER(LOGGER)
 *
 * Short-hand macro to produce a file scoped named `S31_LOGGER_NAME` that catches the logger defined by the LOGGER
 * argument of the macro.
 *
 * Afterwards, you can use this function in your CPP file to retrieve the logger with name "MyComponent".
 *
 * \ingroup S31Log
 */
#define S31_LOGGER(LOGGER) S31_LOGGER_(S31_LOGGER_NAME, LOGGER)

/*!
 * \brief Short-hand macro to check if a log level is set to info.
 * \ingroup S31Log
 */
#define S31_LOG_IS_INFO() (S31_LOGGER_NAME.is(DFL::Log::Info))

/*!
 * \brief Short-hand macro to check if a log level is set to success.
 * \ingroup S31Log
 */
#define S31_LOG_IS_SUCCESS() (S31_LOGGER_NAME.is(DFL::Log::Success))

/*!
 * \brief Short-hand macro to check if a log level is set to trace.
 * \ingroup S31Log
 */
#define S31_LOG_IS_TRACE() (S31_LOGGER_NAME.is(DFL::Log::Trace))

/*!
 * \brief Short-hand macro to check if a log level is set to warn.
 * \ingroup S31Log
 */
#define S31_LOG_IS_WARN() (S31_LOGGER_NAME.is(DFL::Log::Warning))

/*!
 * \brief Short-hand macro to check if a log level is set to error.
 * \ingroup S31Log
 */
#define S31_LOG_IS_ERROR() (S31_LOGGER_NAME.is(DFL::Log::Error))

/// @brief Macro to log a service log entry for an trace message.
/// @ingroup S31Log
#define S31_SERVICE_STREAM_TRACE(...) S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Trace, __FILE__, __LINE__, __VA_ARGS__)

/// @brief Macro to log a service log entry for an info message.
/// @ingroup S31Log
#define S31_SERVICE_STREAM_INFO(...) S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Info, __FILE__, __LINE__, __VA_ARGS__)

/// @brief Macro to log a service log entry for an warning message.
/// @ingroup S31Log
#define S31_SERVICE_STREAM_WARN(...) S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__)

/// @brief Macro to log a service log entry for an success message.
/// @ingroup S31Log
#define S31_SERVICE_STREAM_SUCCESS(...) S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Success, __FILE__, __LINE__, __VA_ARGS__)

/// @brief Macro to log a service log entry for an error message.
/// @ingroup S31Log
#define S31_SERVICE_STREAM_ERROR(...) S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__)

/*!
 * @name Service entry limited
 * Macro to log a service log entry for an error/waring/information.
 *
 * Messages of this type have limited occurrences in the log (per log point in the source).
 *
 * \ingroup S31Log
 */
///@{
#define S31_SERVICE_STREAM_ERROR_LIMITED(...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Error, __FILE__, __LINE__, __VA_ARGS__); \
    }} while (0)

#define S31_SERVICE_STREAM_WARN_LIMITED(...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Warning, __FILE__, __LINE__, __VA_ARGS__); \
    }} while (0)

#define S31_SERVICE_STREAM_INFO_LIMITED(...)  do { \
    static S31::Impl::LimitedLogMessagesInt logCountLeft{S31::Impl::NumberOfOccurrencesIfLimitedLogMessages}; \
    if (logCountLeft > 0) { \
    logCountLeft--; \
    S31::Log::Impl::writeServiceStreamLogMessage(DFL::Log::Info, __FILE__, __LINE__, __VA_ARGS__); \
    }} while (0)

} /* namespace S31 */
