#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/LibImpl.h>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
class DFL_CHRONO_EXPIMP SteadyClock
{
public:
    using TimePoint = SteadyClockImpl::time_point;
    using Duration = SteadyClockImpl::duration;

    static Microseconds timeSinceEpoch();
};
}
}
}
