#pragma once

#include <Framework/Log/Private/ExpImp.h>

#include <ostream>

namespace DFL {
namespace Log {

class EventCode;

/**
 * @brief Streams EventCode object to ostream.
 * @param out Stream to put EventCode object in.
 * @param ec EventCode object to be put into stream
 * @return The given stream object.
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out, EventCode const& ec);

}
}
