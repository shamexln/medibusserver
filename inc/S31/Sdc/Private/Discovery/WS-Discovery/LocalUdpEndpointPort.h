#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::Sdc::Impl
{
struct LocalUdpEndpointPortTag;
using LocalUdpEndpointPort = DFL::StrongTypedef<unsigned short, LocalUdpEndpointPortTag, DFL::Skill::Streamable>;

inline constexpr auto NoLocalUdpEndpointPort = LocalUdpEndpointPort{0};
}
