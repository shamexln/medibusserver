#pragma once

#include <Framework/Chrono/Private/BasicDateTime.h>
#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/LibImpl.h>
#include <Framework/Chrono/Public/Duration.h>

namespace DFL
{
namespace Chrono
{
namespace Impl
{

class DFL_CHRONO_EXPIMP SystemClock
{
public:
    using TimePoint = SystemClockImpl::time_point;
    using Duration = SystemClockImpl::duration;

    static Microseconds timeSinceEpoch();
    static LocalDateTime toLocal(const Microseconds& sinceEpoch);
};

}
}
}
