#pragma once

#include <S31/SetService/Public/Common/Argument.h>

#include <S31/S31CoreExImp.h>

#include <Framework/Format/Public/Stream.h>

#include <iosfwd>

namespace S31::SetService
{

/**
 * @brief Generates a human readable representation.
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const Argument& data);

/**
 * @brief Stream operator for \ref Argument.
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, const Argument& data);
}
