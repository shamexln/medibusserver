#pragma once

#include <Framework/Chrono/Private/BasicDateTime.h>
#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/SystemClock.h>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
namespace Convert
{
DFL_CHRONO_EXPIMP LocalDateTime toLocal(const Chrono::SystemClock::TimePoint& tp);
}
}
}
}
