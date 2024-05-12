#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <ostream>

namespace DFL {
namespace Component {

class Kind;

/**
 * @brief Streams Kind object to ostream.
 * @param out Stream to put Kind object in.
 * @param kind Kind object to be put into stream
 * @return The given stream object.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, Kind const& kind);

}
}
