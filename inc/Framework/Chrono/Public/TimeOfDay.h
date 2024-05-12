#pragma once

#include <Framework/Chrono/Public/Duration.h>

namespace DFL
{
namespace Chrono
{
template <class Duration>
class TimeOfDay;
/**
 * @brief Constructs a @ref DFL::Chrono::TimeOfDay from given duration.
 *
 * The finest resolution is microseconds. Information is cut off
 * if a finer resolution than microseconds is provided.
 * @tparam Duration Type of the given duration.
 * @param d Duration to construct @ref DFL::Chrono::TimeOfDay from.
 * @return @ref DFL::Chrono::TimeOfDay with a precision of microseconds.
 * @ingroup Chrono
 */
template <class Duration>
TimeOfDay<Duration> makeTime(Duration d);
/**
 * @brief Breaksdown a given duration into hours, minutes, seconds and subseconds.
 *
 * The coarsest resolution is hours.
 * The finest resolution is defined by the template parameter.
 * @tparam Duration Type of the finest resolution.
 * @ingroup Chrono
 */
template <class Duration>
class TimeOfDay
{
public:
    /**
     * @brief Precision this type has been instantiated with.
     */
    using Precision = Duration;
    /**
     * @brief Constructs an instance with undefined values.
     */
    TimeOfDay();
    /**
     * @brief Constructs an instance with a given precision.
     *
     * The given duration is broken down into hours, minutes,
     * seconds, subseconds.
     * @param sinceMidnight Duration since midnight.
     */
    explicit TimeOfDay(Precision sinceMidnight);
    /**
     * @brief Constructs an instance from individual durations.
     *
     * @param h Hours.
     * @param m Minutes.
     * @param s Seconds.
     * @param subsec Subseconds.
     */
    explicit TimeOfDay(Hours h, Minutes m, Seconds s, Precision subsec);
    /**
     * @brief Returns the hour part.
     */
    Hours hours() const;
    /**
     * @brief Returns the minutes part.
     */
    Minutes minutes() const;
    /**
     * @brief Returns the seconds part.
     */
    Seconds seconds() const;
    /**
     * @brief Returns the subseconds part.
     */
    Precision subseconds() const;
    /**
     * @brief Returns the sum of all durations.
     */
    Precision toDuration() const;
private:
    Hours m_hours;
    Minutes m_minutes;
    Seconds m_seconds;
    Precision m_subseconds;
};
// Seconds
/**
 * @brief Breaksdown a given duration into hours, minutes, seconds.
 *
 * The coarsest resolution is hours.
 * The finest resolution is seconds.
 * @ingroup Chrono
 */
template <>
class TimeOfDay<Seconds>
{
public:
    /**
     * @brief Precision is seconds.
     */
    using Precision = Seconds;
    /**
     * @brief Constructs an instance with undefined values.
     */
    TimeOfDay();
    /**
     * @brief Constructs an instance with a precision of seconds.
     *
     * The given duration is broken down into hours, minutes, seconds.
     * @param sinceMidnight Seconds since midnight.
     */
    explicit TimeOfDay(Precision sinceMidnight);
    /**
     * @brief Constructs an instance from individual durations.
     *
     * @param h Hours.
     * @param m Minutes.
     * @param s Seconds.
     */
    explicit TimeOfDay(Hours h, Minutes m, Seconds s);
    /**
     * @brief Returns the hour part.
     */
    Hours hours() const;
    /**
     * @brief Returns the minute part.
     */
    Minutes minutes() const;
    /**
     * @brief Returns the second part.
     */
    Seconds seconds() const;
    /**
     * @brief Returns the sum of all durations.
     */
    Precision toDuration() const;
private:
    Hours m_hours;
    Minutes m_minutes;
    Seconds m_seconds;
};

// Minutes
/**
 * @brief Breaksdown a given duration into hours, minutes.
 *
 * The coarsest resolution is hours.
 * The finest resolution is minutes.
 * @ingroup Chrono
 */
template <>
class TimeOfDay<Minutes>
{
public:
    /**
     * @brief Precision is minutes.
     */
    using Precision = Minutes;
    /**
     * @brief Constructs an instance with undefined values.
     */
    TimeOfDay();
    /**
     * @brief Constructs an instance with a precision of minutes.
     *
     * The given duration is broken down into hours, minutes.
     * @param sinceMidnight Minutes since midnight.
     */
    explicit TimeOfDay(Precision sinceMidnight);
    /**
     * @brief Constructs an instance from individual durations.
     *
     * @param h Hours.
     * @param m Minutes.
     */
    explicit TimeOfDay(Hours h, Minutes m);
    /**
     * @brief Returns the hour part.
     */
    Hours hours() const;
    /**
     * @brief Returns the minute part.
     */
    Minutes minutes() const;
    /**
     * @brief Returns the sum of all durations.
     */
    Precision toDuration() const;
private:
    Hours m_hours;
    Minutes m_minutes;
};
// Hours
/**
 * @brief Breaksdown a given duration into hours.
 *
 * @ingroup Chrono
 */
template <>
class TimeOfDay<Hours>
{
public:
    /**
     * @brief Precision is hours.
     */
    using Precision = Hours;
    /**
     * @brief Constructs an instance with undefined values.
     */
    TimeOfDay();
    /**
     * @brief Constructs an instance with a precision of hours.
     *
     * The given duration is broken down into hours.
     * @param sinceMidnight Hours since midnight.
     */
    explicit TimeOfDay(Precision sinceMidnight);
    /**
     * @brief Returns the hour part.
     */
    Hours hours() const;
    /**
     * @brief Returns the sum of all durations.
     */
    Precision toDuration() const;
private:
    Hours m_hours;
};

// Duration
template <class Duration>
inline TimeOfDay<Duration>::TimeOfDay()
    : m_hours()
    , m_minutes()
    , m_seconds()
    , m_subseconds()
{}

template <class Duration>
inline TimeOfDay<Duration>::TimeOfDay(Precision sinceMidnight)
    : m_hours(duration_cast<Hours>(sinceMidnight))
    , m_minutes(duration_cast<Minutes>(sinceMidnight - m_hours))
    , m_seconds(duration_cast<Seconds>(sinceMidnight - m_hours - m_minutes))
    , m_subseconds(sinceMidnight - m_hours - m_minutes - m_seconds)
{}

template <class Duration>
inline TimeOfDay<Duration>::TimeOfDay(Hours h, Minutes m, Seconds s, Precision subsec)
    : m_hours(h)
    , m_minutes(m)
    , m_seconds(s)
    , m_subseconds(subsec)
{}

template <class Duration>
inline Hours TimeOfDay<Duration>::hours() const
{
    return m_hours;
}

template <class Duration>
inline Minutes TimeOfDay<Duration>::minutes() const
{
    return m_minutes;
}

template <class Duration>
inline Seconds TimeOfDay<Duration>::seconds() const
{
    return m_seconds;
}

template <class Duration>
inline typename TimeOfDay<Duration>::Precision TimeOfDay<Duration>::subseconds() const
{
    return m_subseconds;
}

template <class Duration>
inline typename TimeOfDay<Duration>::Precision TimeOfDay<Duration>::toDuration() const
{
    return m_hours + m_minutes + m_seconds + m_subseconds;
}

// Seconds
inline TimeOfDay<Seconds>::TimeOfDay()
    : m_hours()
    , m_minutes()
    , m_seconds()
{}

inline TimeOfDay<Seconds>::TimeOfDay(Precision sinceMidnight)
    : m_hours(duration_cast<Hours>(sinceMidnight))
    , m_minutes(duration_cast<Minutes>(sinceMidnight - m_hours))
    , m_seconds(duration_cast<Seconds>(sinceMidnight - m_hours - m_minutes))
{}

inline TimeOfDay<Seconds>::TimeOfDay(Hours h, Minutes m, Seconds s)
    : m_hours(h)
    , m_minutes(m)
    , m_seconds(s)
{}

inline Hours TimeOfDay<Seconds>::hours() const
{
    return m_hours;
}

inline Minutes TimeOfDay<Seconds>::minutes() const
{
    return m_minutes;
}

inline Seconds TimeOfDay<Seconds>::seconds() const
{
    return m_seconds;
}

inline TimeOfDay<Seconds>::Precision TimeOfDay<Seconds>::toDuration() const
{
    return m_hours + m_minutes + m_seconds;
}

// Minutes
inline TimeOfDay<Minutes>::TimeOfDay()
    : m_hours()
    , m_minutes()
{}

inline TimeOfDay<Minutes>::TimeOfDay(Precision sinceMidnight)
    : m_hours(duration_cast<Hours>(sinceMidnight))
    , m_minutes(duration_cast<Minutes>(sinceMidnight - m_hours))
{}

inline TimeOfDay<Minutes>::TimeOfDay(Hours h, Minutes m)
    : m_hours(h)
    , m_minutes(m)
{}

inline Hours TimeOfDay<Minutes>::hours() const
{
    return m_hours;
}

inline Minutes TimeOfDay<Minutes>::minutes() const
{
    return m_minutes;
}

inline TimeOfDay<Minutes>::Precision TimeOfDay<Minutes>::toDuration() const
{
    return m_hours + m_minutes;
}

// Hours
inline TimeOfDay<Hours>::TimeOfDay()
    : m_hours()
{}

inline TimeOfDay<Hours>::TimeOfDay(Precision sinceMidnight)
    : m_hours(sinceMidnight)
{}

inline Hours TimeOfDay<Hours>::hours() const
{
    return m_hours;
}

inline TimeOfDay<Hours>::Precision TimeOfDay<Hours>::toDuration() const
{
    return this->hours();
}

template <class Duration>
inline TimeOfDay<Duration> makeTime(Duration d)
{
    return TimeOfDay<Duration>(d);
}
}
}
