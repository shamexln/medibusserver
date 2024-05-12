#pragma once

#include <Framework/Log/Private/ExpImp.h>

namespace DFL
{
namespace Log
{
class Message;
/**
 * @brief Formats attributes of message according to IN9880.
 *
 * IN9880 only specifies the prefix of the text to be logged. Afterwards the
 * "free text" follows. With this logger all attributes which are not in the
 * prefix are put into "free text" section. Thus making this logger a very
 * detailed one suiteable for e.g. debug log messages.
 *
 * @snippet Log/Test/UnitTest/TestIn9880.cpp debug
 *
 * @ingroup Log
 */
struct DFL_LOG_EXPIMP In9880Logger
{
public:
    /**
     * @brief Returns a message where its text attribute is formatted according
     * to IN9880 and the "free text" is filled with all other attributes.
     */
    Message operator()(Message const& message) const;
};
/**
 * @brief Formats attributes of message according to IN9880.
 *
 * IN9880 only specifies the prefix of the text to be logged. Afterwards the
 * "free text" follows. With this logger all attributes which are not in the
 * prefix are put into "free text" section. Thus making this logger a very
 * detailed one suiteable for debug log messages.
 *
 * @snippet Log/Test/UnitTest/TestIn9880.cpp debug
 *
 * @ingroup Log
 */
using In9880DebugLogger = In9880Logger;
/**
 * @brief Formats attributes of message according to IN9880.
 *
 * IN9880 only specifies the prefix of the text to be logged. Afterwards the
 * "free text" follows. With this logger only the text attribute is added.
 *
 * @snippet Log/Test/UnitTest/TestIn9880.cpp service
 *
 * @ingroup Log
 */
struct DFL_LOG_EXPIMP In9880ServiceLogger
{
public:
    /**
     * @brief Returns a message where its text attribute is formatted according
     * to IN9880 and the "free text" is filled with the text attribute.
     */
    Message operator()(Message const& message) const;
};
}
}
