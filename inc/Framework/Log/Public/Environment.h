#pragma once

#include <Framework/Log/Private/ExpImp.h>

/**
 * @ingroup Log
 * @{
 */
namespace DFL
{
namespace Log
{

/**
 * @brief Environment for the log library is configured here.
 */
class DFL_LOG_EXPIMP Environment
{
public:
    /**
     * @brief Initializes the environment for the log library.
     *
     * This method shall be called prior to any usage of any logger.
     */
    static void init();

    /**
     * @brief Shuts the environment of the log library down.
     *
     * This method shall be called when there are no logs to be expected.
     */
    static void shutdown();
};

}
}
/** @} */
