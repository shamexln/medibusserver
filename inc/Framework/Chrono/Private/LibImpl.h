#pragma once

#include <Framework/Chrono/Private/ExpImp.h>

#include <boost/chrono/ceil.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/floor.hpp>
#include <boost/chrono/round.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/time_point.hpp>

namespace DFL
{
namespace Chrono
{
namespace Impl
{

using boost::ratio;
using boost::chrono::duration;

using Nanoseconds = boost::chrono::nanoseconds;
using Microseconds = boost::chrono::microseconds;
using Milliseconds = boost::chrono::milliseconds;
using Seconds = boost::chrono::seconds;
using Minutes = boost::chrono::minutes;
using Hours = boost::chrono::hours;

using boost::chrono::duration_cast;
using boost::chrono::ceil;
using boost::chrono::floor;
using boost::chrono::round;

using SystemClockImpl = boost::chrono::system_clock;
using SteadyClockImpl = boost::chrono::steady_clock;

using Days = boost::chrono::duration<int, boost::ratio_multiply<boost::ratio<24>, Hours::period> >;
using Weeks = boost::chrono::duration<int, boost::ratio_multiply<boost::ratio<7>, Days::period> >;
// it takes 400 years until the gregorian calendar repeats,
// this are 146097 days, hence one year is 146097days/400years long
using Years = boost::chrono::duration<int, boost::ratio_multiply<boost::ratio<146097, 400>, Days::period> >;
using Months = boost::chrono::duration<int, boost::ratio_divide<Years::period, boost::ratio<12> > >;

using boost::chrono::time_point;

using SystemDays = boost::chrono::time_point<SystemClockImpl, Days>;
using SystemHours = boost::chrono::time_point<SystemClockImpl, Hours>;
using SystemMinutes = boost::chrono::time_point<SystemClockImpl, Minutes>;
using SystemSeconds = boost::chrono::time_point<SystemClockImpl, Seconds>;
using SystemMilliseconds = boost::chrono::time_point<SystemClockImpl, Milliseconds>;
using SystemMicroseconds = boost::chrono::time_point<SystemClockImpl, Microseconds>;

using boost::chrono::time_point_cast;
}
}
}
