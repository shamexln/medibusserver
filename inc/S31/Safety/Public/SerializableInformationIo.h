#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Format/Public/Stream.h>

#include <iosfwd>

namespace S31::Safety
{
class SerializableInformation;

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31Safety
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, const SerializableInformation& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31Safety
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const SerializableInformation& data);

}
