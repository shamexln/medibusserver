#pragma once

#include <Framework/Chrono/Private/ExpImp.h>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Tag-Type for creating the "last" value of a calendaric type.
 *
 * e.g YearMonthDay(Year(2000)/feb/last) which is 2000-feb-29 in that case.
 */
class LastSpec
{
};
}
}

namespace DFL
{
namespace Chrono
{
/**
 * @brief Constant for representing the last day of a month or year-month.
 * @ingroup Chrono
 */
const LastSpec last;
}
}
