#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/LocalTime.h>
#include <Framework/Chrono/Public/SystemTime.h>

namespace DFL
{
namespace Chrono
{
class TimeZone;
struct SystemInfo;
namespace Impl
{
struct LocalInfo;
DFL_CHRONO_EXPIMP TimeZone utcZone();
DFL_CHRONO_EXPIMP TimeZone offsetZone(Seconds utcOffset);
DFL_CHRONO_EXPIMP SystemInfo calcSystemInfo(SystemSeconds tp, const TimeZone& zone);
DFL_CHRONO_EXPIMP LocalInfo calcLocalInfo(LocalTime lt, const TimeZone& zone);
}
}
}
