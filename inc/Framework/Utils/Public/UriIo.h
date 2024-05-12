#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{

namespace Net
{

class Uri;

/**
 * @brief Streams the URI string.
 * @details Usage:
 *          @snippet Utils/Test/UnitTest/TestUri.cpp IoStreaming
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, Uri const& data);

}

namespace Format
{

class Stream;

/**
 * @brief Streams the URI string.
 * @details Usage:
 *          @snippet Utils/Test/UnitTest/TestUri.cpp FormatStreamStreaming
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& out, Net::Uri const& data);

}

}
