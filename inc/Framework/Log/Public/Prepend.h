#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Public/Message.h>

#include <string>

namespace DFL
{
namespace Log
{
/**
 * @brief Functor that puts a prefix in front of a log message.
 * @details
 * A typical use case is to prepend a log message with some context information
 * like a sub-system name:
 * \snippet Log/Sample/Sample.cpp PrependLogger
 * @ingroup Log
 */
class DFL_LOG_EXPIMP Prepend
{
    public:
        /**
         * @brief Constructor of the log prepender.
         * @param prefix Prefix for log messages
         */
        explicit Prepend(std::string prefix);

        /**
         * @brief Functor for DFL logging
         * @param message the message to be prefixed.
         */
        Message operator()(Message const& message) const;

    private:
        std::string m_prefix;
};
}
}
