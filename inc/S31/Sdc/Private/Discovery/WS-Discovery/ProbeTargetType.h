#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Enum for distinguishing the target of a probe
 * @details Depending on the target type of the probe, the To field of the soap header must be set to either
 * "urn:docs-oasis-open-org:ws-dd:ns:discovery:2009:01" if the target is a known service or the address of a targeted discovery proxy.
 */
enum class ProbeTargetType
{
    /// Probe being sent to a targetService (known device)
    TargetService,
    /// Probe being sent to a DiscoveryProxy
    DiscoveryProxy
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ProbeTargetType, (TargetService)(DiscoveryProxy))

}
