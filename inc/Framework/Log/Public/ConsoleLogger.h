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

class Message;

/**
 * @brief Prints messages to console.
 */
class DFL_LOG_EXPIMP ConsoleLogger
{
public:
    /**
     * @brief Prints text attribute of message to console.
     * @param m Text of this message is printed to consle.
     * @return The message printed to the console.
     */
    Message operator()(Message const& m) const;
};

}
}
/** @} */
