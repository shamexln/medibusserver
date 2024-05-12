#pragma once

#include <Framework/Chrono/Public/Stopwatch.h>

#include <boost/chrono/config.hpp>
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
#include <boost/chrono/thread_clock.hpp>
#endif
#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
#include <boost/chrono/process_cpu_clocks.hpp>
#endif

#include <boost/chrono/duration.hpp>

namespace DFL
{
namespace Chrono
{
namespace Boost
{
#if defined(BOOST_CHRONO_HAS_THREAD_CLOCK)
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using boost::chrono::thread_clock as
 * a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using ThreadStopwatchD = BasicStopwatch<boost::chrono::thread_clock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using boost::chrono::thread_clock as
 * a source.
 *
 * @ingroup Chrono
 */
using ThreadStopwatch = ThreadStopwatchD<boost::chrono::thread_clock::duration>;
#endif

#if defined(BOOST_CHRONO_HAS_PROCESS_CLOCKS)
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_real_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using ProcessRealStopwatchD =
    BasicStopwatch<boost::chrono::process_real_cpu_clock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_real_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
using ProcessRealStopwatch =
    ProcessRealStopwatchD<boost::chrono::process_real_cpu_clock::duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_user_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using ProcessUserStopwatchD =
    BasicStopwatch<boost::chrono::process_user_cpu_clock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_user_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
using ProcessUserStopwatch =
    ProcessUserStopwatchD<boost::chrono::process_user_cpu_clock::duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_system_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using ProcessSystemStopwatchD =
    BasicStopwatch<boost::chrono::process_system_cpu_clock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_system_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
using ProcessSystemStopwatch =
    ProcessSystemStopwatchD<boost::chrono::process_system_cpu_clock::duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
template <class Duration>
using ProcessCpuStopwatchD =
    BasicStopwatch<boost::chrono::process_cpu_clock, Duration>;
/**
 * @brief @ref DFL::Chrono::BasicStopwatch using
 * boost::chrono::process_cpu_clock as a source.
 *
 * @ingroup Chrono
 */
using ProcessCpuStopwatch =
    ProcessCpuStopwatchD<boost::chrono::process_cpu_clock::duration>;
#endif
}
}
}
