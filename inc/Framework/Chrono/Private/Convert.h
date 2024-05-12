#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Private/SystemClock.h>
#include <Framework/Chrono/Public/SystemInfo.h>
#include <boost/optional.hpp>
#include <string>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
struct StructuredDate
{
    int year{0};
    unsigned month{0};
    unsigned day{0};
    unsigned hours{0};
    unsigned minutes{0};
    unsigned seconds{0};
    unsigned microseconds{0};
    int tzOffsetHours{0};
    int tzOffsetMinutes{0};
};
using OptionalStructuredDate = boost::optional<StructuredDate>;
DFL_CHRONO_EXPIMP OptionalStructuredDate toDateTime(const std::string& timePointAsString);
DFL_CHRONO_EXPIMP std::string removeTrailingZeros(const std::string& txt);
DFL_CHRONO_EXPIMP SystemInfo makeCurrentSystemInfo();
}
}
}
