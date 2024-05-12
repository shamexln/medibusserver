#pragma once

#include <Framework/Chrono/Public/SystemClock.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief %MDIB timestamp based on adjustable system clock.
 * @ingroup Mdib
 */
using Timestamp = Chrono::SystemClock::TimePoint;

} /* namespace Mdib */
} /* namespace DFL */
