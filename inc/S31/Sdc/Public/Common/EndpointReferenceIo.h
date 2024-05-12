#pragma once

#include <S31/S31CoreExImp.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}

namespace S31::Sdc
{

class EndpointReference;

/**
 * @brief Streams the endpoint reference.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, EndpointReference const& data);

/**
 * @brief Streams the endpoint reference.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, EndpointReference const& data);

}
