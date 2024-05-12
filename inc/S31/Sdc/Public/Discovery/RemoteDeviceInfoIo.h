#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Sdc/Public/Discovery/RemoteDeviceInfo.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}

namespace S31::Sdc
{

/**
 * @brief Stream \ref RemoteDeviceInfo::AssociatedLocation to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, RemoteDeviceInfo::AssociatedLocation const& data);

/**
 * @brief Stream \ref RemoteDeviceInfo::AssociatedLocation to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, RemoteDeviceInfo::AssociatedLocation const& data);

/**
 * @brief Stream \ref RemoteDeviceInfo to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, RemoteDeviceInfo const& data);

/**
 * @brief Stream \ref RemoteDeviceInfo to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, RemoteDeviceInfo const& data);

}
