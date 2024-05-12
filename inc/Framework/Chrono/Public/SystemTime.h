#pragma once

#include <Framework/Chrono/Private/LibImpl.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief System time point definitions with different periods.
 *
 * @ingroup Chrono
 * @{
 */
using SystemDays = Impl::SystemDays;
using SystemHours = Impl::SystemHours;
using SystemMinutes = Impl::SystemMinutes;
using SystemSeconds = Impl::SystemSeconds;
using SystemMilliseconds = Impl::SystemMilliseconds;
using SystemMicroseconds = Impl::SystemMicroseconds;
/** @} */
}
}
