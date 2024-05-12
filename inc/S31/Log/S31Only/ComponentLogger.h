#pragma once

#include <S31/Log/Private/S31LogExImp.h>

#include <Framework/Format/Public/Stream.h>
#include <Framework/Log/Public/Logger.h>
#include <Framework/Log/Public/Severities.h>
#include <Framework/Log/Public/Severity.h>

#include <string>
#include <map>
#include <vector>

namespace S31::Log::Impl
{

/*!
 * @brief Central unit to process component based logging.
 *
 * @ingroup S31Log
 */
class S31_LOG_EXPIMP ComponentLogger
{
    public:
        /*!
         * @brief Prints a component based log message to the attached log sinks.
         */
        static void writeBufferMessage(const DFL::Log::Logger& logger,
                                    const DFL::Log::Severity& level,
                                    const char* file,
                                    int line,
                                    const char* buffer);

        /*!
         * @brief Prints a component based log message to the attached log sinks.
         *
         * @brief This function signature is needed by the stream logging macros
         *
         * @see StreamLogger.h
         */
        template<class A>
        static void writeBufferMessage(const DFL::Log::Logger& logger,
                                    const DFL::Log::Severity& level,
                                    const char* file,
                                    int line,
                                    A const& a,
                                    const char* buffer);

        /*!
         * @brief Retrieves the S31 module logger.
         *
         * Like `DFL::Log::Registry::createOrGet()`, only use this method once and keep a reference.
         *
         * @return the global logger element by reference. It is guaranteed that this reference will never be invalid.
         *         Make sure to not create a copy of this logger, because it will not be registered in the global log
         *         registry.
         */
        static DFL::Log::Logger& getS31ModuleLogger();

        /*!
         * @brief Retrieves a component logger by component name.
         *
         * Like `DFL::Log::Registry::createOrGet()`, only use this method once for each logger and keep a reference.
         *
         * @param componentName Name of the logging component
         * @return a reference to the corresponding logger object. It is guaranteed that this reference will never be
         *         invalid. Make sure to not create a copy of this logger, because it will not be registered in the
         *         global log registry.
         */
        static DFL::Log::Logger& getComponentLogger(const std::string& componentName);

        /**
         * @name LogLevels
         * @brief Set/get the log levels for single components as a comma-separated string of components=log level pairs.
         * @details E.g.: "S31.DateTime=3,S31.Waveforms=4".
         * Replaces the old configuration. This works at runtime and updates all the existing component loggers.
         */
        ///@{
        /// @param componentLogLevels the component log levels as a comma-separated string
        static void setLogLevels(const std::string& componentLogLevels);

        /// @return A map with component logger names and their currently assigned to a log level.
        static std::map<std::string, DFL::Log::Severity> getLogLevels();
        ///@}

        /**
         * @name LogLevel
         * @brief Set/get the loglevel to all component loggers that are not individually configured with @ref setLogLevels.
         * @param severity
         */
        ///@{
        static void setLogLevel(DFL::Log::Severity severity);
        static DFL::Log::Severity getLogLevel();
        ///@}
};


template<class A>
inline void ComponentLogger::writeBufferMessage(const DFL::Log::Logger& logger,
                            const DFL::Log::Severity& level,
                            const char* file,
                            int line,
                            A const& a,
                            const char* buffer)
{
    if (!logger.is(level))
    {
        return;
    }
    DFL::Format::Stream const stream;
    stream << a << std::string(buffer);
    writeBufferMessage(logger, level, file, line, stream.cStr());
}

}
