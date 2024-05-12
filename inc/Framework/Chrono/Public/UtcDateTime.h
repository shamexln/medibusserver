#pragma once

#include <Framework/Chrono/Private/BasicDateTime.h>
#include <Framework/Config/Public/Attributes.h>

DFL_HEADER_DEPRECATED("use SystemClock::TimePoint from SystemClock.h instead")

namespace DFL
{
namespace Chrono
{
/**
 * @brief DEPRECATED
 *
 * @deprecated Please use @ref DFL::Chrono::YearMonthDay instead.
 *
 * @ingroup Chrono
 */
using UtcDateTime DFL_ATTRIBUTE_DEPRECATED(
    "use YearMonthDay or SystemClock::TimePoint instead") = Impl::UtcDateTime;
}
}
