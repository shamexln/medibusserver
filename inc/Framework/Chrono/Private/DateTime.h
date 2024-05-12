#pragma once

#include <Framework/Chrono/Private/LibImpl.h>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/Round.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Public/TimeOfDay.h>
#include <Framework/Chrono/Public/TimePoint.h>
#include <Framework/Chrono/Public/YearMonthDay.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Format/Public/ToString.h>
#include <ostream>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
template<class Duration>
class DateTime
{
public:
    DateTime(const YearMonthDay& ymd_, const TimeOfDay<Duration>& tod_);
    YearMonthDay ymd;
    TimeOfDay<Duration> tod;
    time_point<Impl::SystemClockImpl, Duration> systemTime() const;
};

template<class U, class T>
DateTime<U> makeDateTime(const time_point<Impl::SystemClockImpl, T>& tp);
template<class U, class T>
DateTime<U> makeDateTime(const time_point<LocalType, T>& tp);

template<class Duration>
std::ostream& operator<<(std::ostream& str, const DateTime<Duration>& d);
}
}
}

namespace DFL
{
namespace Format
{
template<class Duration>
Stream& operator<<(Stream& str, const Chrono::Impl::DateTime<Duration>& d);
}
}

namespace DFL
{
namespace Chrono
{
namespace Impl
{
template<class Duration>
inline DateTime<Duration>::DateTime(const YearMonthDay& ymd_, const TimeOfDay<Duration>& tod_)
    : ymd(ymd_)
    , tod(tod_)
{}

template<class Duration>
inline time_point<Impl::SystemClockImpl, Duration> DateTime<Duration>::systemTime() const
{
  return ymd.systemDays() + tod.toDuration();
}

template<class Duration>
inline DateTime<Duration> makeDateTime(const time_point<Impl::SystemClockImpl, Duration>& tp)
{
    const YearMonthDay ymd = Chrono::floor<Days>(tp);
    const TimeOfDay<Duration> tod = makeTime(tp - ymd.systemDays());
    return DateTime<Duration>(ymd, tod);
}

template<class Duration>
inline DateTime<Duration> makeDateTime(const time_point<LocalType, Duration>& tp)
{
    const YearMonthDay ymd = Chrono::floor<Days>(tp);
    const TimeOfDay<Duration> tod = makeTime(tp - ymd.localDays());
    return DateTime<Duration>(ymd, tod);
}

template<class Duration>
inline std::ostream& operator<<(std::ostream& str, const DateTime<Duration>& d)
{
    str << Format::toString(d);
    return str;
}
}
}
}

namespace DFL
{
namespace Format
{
template<class Duration>
inline Stream& operator<<(Stream& str, const Chrono::Impl::DateTime<Duration>& d)
{
    str << d.ymd << ' ' << d.tod;
    return str;
}
}
}
