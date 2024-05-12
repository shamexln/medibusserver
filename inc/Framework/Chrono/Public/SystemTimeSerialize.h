#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemClock.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Chrono::SystemClock::TimePoint)

BOOST_CLASS_VERSION(::DFL::Chrono::SystemClock::TimePoint, 0)

namespace DFL
{
namespace Chrono
{
/**
 * @brief Type to be used for serializing @ref DFL::Chrono::SystemClock::TimePoint
 *
 * Do not use @ref DFL::Chrono::SystemClock::Duration for serialization.
 * @ref DFL::Chrono::SystemClock::Duration is plattform specific e.g.
 * nanoseconds on VxWorks and 10th microseconds on Windows.
 * So a time point serialized on Windows would lead to wrong values
 * if read on VxWorks and vice versa.
 *
 * @snippet Chrono/Test/UnitTest/TestSystemTimeSerialize.cpp serialize
 *
 * @ingroup Chrono
 */
using SystemClockSerializationDuration = Microseconds;
}
}
namespace boost
{
namespace serialization
{
template<class Archive>
void save(Archive & ar, const ::DFL::Chrono::SystemClock::TimePoint& tp, const unsigned int /*version*/)
{
    using ::DFL::Chrono::SystemClockSerializationDuration;
    using ::DFL::Chrono::duration_cast;

    const SystemClockSerializationDuration sinceEpoch(
        duration_cast<SystemClockSerializationDuration>(tp.time_since_epoch()));
    const SystemClockSerializationDuration::rep countSinceEpoch(sinceEpoch.count());

    ar & make_nvp("SinceEpoch", countSinceEpoch);
}

template<class Archive>
void load(Archive & ar, ::DFL::Chrono::SystemClock::TimePoint& tp, const unsigned int /*version*/)
{
    using ::DFL::Chrono::SystemClockSerializationDuration;
    using ::DFL::Chrono::duration_cast;

    SystemClockSerializationDuration::rep countSinceEpoch(0);

    ar & make_nvp("SinceEpoch", countSinceEpoch);

    const SystemClockSerializationDuration sinceEpoch(countSinceEpoch);
    tp = ::DFL::Chrono::SystemClock::TimePoint(
        duration_cast<::DFL::Chrono::SystemClock::Duration>(sinceEpoch));
}
}
}
