#pragma once

#include <S31/S31CoreExImp.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}

namespace S31::Sdc
{
class DpwsDeviceMetadata;

/**
 * @brief Stream operator for output.
 * @param out returned output stream
 * @param data content to stream
 * @return the passed stream (first argument)
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, DpwsDeviceMetadata const& data);

/**
 * @brief Stream operator for debug output.
 * @param out returned output stream
 * @param data content to stream
 * @return the passed stream (first argument)
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, DpwsDeviceMetadata const& data);

}
