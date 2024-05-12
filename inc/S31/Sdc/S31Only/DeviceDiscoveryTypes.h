#pragma once

#include <Framework/Utils/Public/QName.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <vector>

namespace S31::Sdc::Impl
{

struct DeviceDiscoveryTypesTag{};

/**
 * @brief Types for WS-Discovery.
 * @ingroup S31SdcCommon
 */
using DeviceDiscoveryTypes = DFL::StrongTypedef<std::vector<DFL::QName>, DeviceDiscoveryTypesTag>;

}
