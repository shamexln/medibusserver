#pragma once

#include <Framework/Log/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Log
{
class Message;
class MessageComparator;
/**
 * @brief Streams Message object to ostream.
 *
 * @snippet Log/Test/UnitTest/TestMessage.cpp Stream
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out, const Message& msg);
/**
 * @brief Streams MessageComparator object to ostream.
 *
 * @snippet Log/Test/UnitTest/TestMessage.cpp MsgCmpStream
 *
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out,
                                        const MessageComparator& msg);
}
}
