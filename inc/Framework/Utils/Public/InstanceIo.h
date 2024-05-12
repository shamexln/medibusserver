#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <ostream>

namespace DFL {
namespace Component {

class Instance;

/**
 * @brief Streams Instance object to ostream.
 * @param out Stream to put Instance object in.
 * @param instance Instance object to be put into stream
 * @return The given stream object.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, Instance const& instance);

}
}
