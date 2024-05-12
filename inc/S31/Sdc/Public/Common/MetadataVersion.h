#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

#include <cstdint>

namespace S31::Sdc
{

namespace Impl
{
struct MetadataVersionTag;
}

/**
 * @brief StrongTypedef for MetadataVersion as described in <a href="http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231821">Ws-Discovery</a>.
 * @details See <a href="https://www.w3.org/TR/2004/REC-xmlschema-2-20041028/#unsignedInt">Xml Schema</a> for restrictions on the value space.
 * @ingroup S31SdcCommon
 */
using MetadataVersion = DFL::StrongTypedef<std::uint32_t, struct Impl::MetadataVersionTag, DFL::Skill::TotallyOrdered, DFL::Skill::Incrementable, DFL::Skill::Streamable>;


}
