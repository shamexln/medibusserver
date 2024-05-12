#pragma once

#include <S31/Log/Private/S31LogExImp.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}

namespace S31::Log
{
class KeyValue;

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31Log
 */
S31_LOG_EXPIMP std::ostream& operator<<(std::ostream& out, const KeyValue& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31Log
 */
S31_LOG_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const KeyValue& data);

}
