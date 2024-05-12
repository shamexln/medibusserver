#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/TimePoint.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/SteadyClock.h>

namespace DFL
{
namespace Mdib
{
namespace Test
{

using Duration = Chrono::SystemClock::Duration;

// used for the update-thread
using ExecutionTimepoint = Chrono::SteadyClock::TimePoint;

// used for timepoints in the Mdib (e.g. determination time)
using MdibTimePoint = Chrono::SystemClock::TimePoint;

}
}
}
