#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/SetService/Public/Common/ProposedAlertStates.h>

#include <Framework/Format/Public/Stream.h>

#include <iosfwd>

namespace S31::SetService
{

/**
 * @brief Generates a human readable representation.
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const ProposedAlertStates& data);

/**
 * @brief Stream operator for \ref ProposedAlertStates.
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, const ProposedAlertStates& data);
}
