#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}


namespace S31::Utils
{

class Error;

/**
 * @brief Streams the Error.
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP std::ostream& operator<<(std::ostream& out, Error const& data);

/**
 * @brief Streams the Error.
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, Error const& data);

}
