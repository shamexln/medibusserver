#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/LibImpl.h>

#include <boost/tuple/tuple.hpp>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
DFL_CHRONO_EXPIMP Days daysSinceUnixEpoch(int year, unsigned month, unsigned day);
DFL_CHRONO_EXPIMP boost::tuple<int, unsigned, unsigned> yearMonthDayFromDaysSinceUnixEpoch(const Days& days);
DFL_CHRONO_EXPIMP bool isLeapYear(int year);
DFL_CHRONO_EXPIMP unsigned lastDayOfMonth(int year, unsigned month);
}
}
}
