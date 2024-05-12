#pragma once

#include <Framework/Chrono/Private/ExpImp.h>
#include <Framework/Chrono/Public/Duration.h>

#include <functional>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
class DFL_CHRONO_EXPIMP Registry
{
public:
    class DFL_CHRONO_EXPIMP SteadyClock
    {
    public:
        using TimeSinceEpoch = std::function<Microseconds()>;
        static TimeSinceEpoch& timeSinceEpoch();
    };

    class DFL_CHRONO_EXPIMP SystemClock
    {
    public:
        using TimeSinceEpoch = std::function<Microseconds()>;
        static TimeSinceEpoch& timeSinceEpoch();
    };
};
}
}
}
