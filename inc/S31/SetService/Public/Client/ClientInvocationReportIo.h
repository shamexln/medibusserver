#pragma once

#include <S31/S31CoreExImp.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}

namespace S31::SetService
{

class ClientInvocationReport;

/**
 * @brief Stream data to given stream.
 */
S31_CORE_EXPIMP std::ostream& operator<<(std::ostream& out, const ClientInvocationReport& data);

/**
 * @brief Stream data to given stream.
 */
S31_CORE_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const ClientInvocationReport& data);

}
