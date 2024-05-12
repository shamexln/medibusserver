#pragma once

#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}

namespace S31::Sdc::Impl
{
std::ostream& operator<<(std::ostream& out, const NetworkInterfaceUpdate& data);

DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const NetworkInterfaceUpdate& data);
}
