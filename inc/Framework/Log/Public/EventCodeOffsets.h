#pragma once

#include <Framework/Log/Private/ExpImp.h>

namespace DFL
{
namespace Log
{
namespace SecurityEventCodeOffsets
{
// Event codes used for security events are in the range from
// 2000 to 2999 by convention. It is not enforced, but we will follow it.
constexpr int firstSecurityEventCode = 2000;
constexpr int lastSecurityEventCode = 2999;

constexpr int securityCodesPerLibrary{50};

enum Libraries
{
    Password = firstSecurityEventCode,
    // NextLib = PreviousLib + securityCodesPerLibrary,
    LastOffsetValue
};

static_assert((LastOffsetValue + securityCodesPerLibrary) <= (lastSecurityEventCode + 1),
              "Security event codes need to be in range 2000 to 2999");
}
}
}
