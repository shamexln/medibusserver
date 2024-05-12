#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Public/Logger.h>
#include <vector>

/**
 * @ingroup Log
 * @{
 */
namespace DFL
{
namespace Log
{

/**
 * @brief Holds the registry where all loggers are located.
 *
 * Loggers can be retrieved from the registry by a name.
 * By default a new logger inherits the message process chain from debug.
 * The debug logger is special because it is guaranteed to be always available
 * and at least log to the console.
 */
class DFL_LOG_EXPIMP Registry
{
public:
    Registry() = delete;
    ~Registry() = delete;

    /**
     * @brief Type of a collection of logger names.
     */
    using NamesType = std::vector<Logger::NameType>;

    /**
     * @brief Puts the debug logger into the registry.
     *
     * This method shall be called prior to any usage of any logger.
     */
    static void init();

    /**
     * @brief Deletes all loggers from the registry.
     *
     * This method shall be called when there are no logs to be expected.
     */
    static void shutdown();

    /**
     * @brief Retrieves logger with name from registry or creates a new logger.
     *
     * If the logger is already in the registry it is returned.
     * If the logger is not in the registry a copy of the debug logger is put
     * into the registry and is associated with the given name.
     *
     * @param loggerName Name of the logger to be retrieved or created.
     * @return Logger from registry.
     */
    static Logger& createOrGet(Logger::NameType const& loggerName);

    /**
     * @brief Retrieves logger with name from registry or creates a new logger.
     *
     * If the logger is already in the registry it is returned.
     * If the logger is not in the registry a copy of the service logger is put
     * into the registry and is associated with the given name.
     *
     * @param loggerName Name of the logger to be retrieved or created.
     * @return Logger from registry.
     */
    static Logger& createOrGetService(Logger::NameType const& loggerName);

    /**
     * @brief Retrieves logger with name from registry or creates a new logger.
     *
     * If the logger is already in the registry it is returned.
     * If the logger is not in the registry a copy of the security logger is put
     * into the registry and is associated with the given name.
     *
     * @param loggerName Name of the logger to be retrieved or created.
     * @return Logger from registry.
     */
    static Logger& createOrGetSecurity(Logger::NameType const& loggerName);

    /**
     * @brief Getter for registered logger names.
     * @return The names of all registered loggers.
     */
    static NamesType names();

    /**
     * @brief Removes all loggers from registry.
     */
    static void clear();
    /**
     * @brief Getter for the debug logger.
     * @return The debug logger.
     */
    static Logger& debug();

    /**
     * @brief Getter for the service logger.
     * @return The service logger.
     */
    static Logger& service();

    /**
     * @brief Getter for the security logger.
     * @return The security logger.
     */
    static Logger& security();
};

}
}
/** @} */
