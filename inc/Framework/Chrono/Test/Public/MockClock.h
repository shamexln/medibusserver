#pragma once

#include <Framework/Chrono/Public/Convert.h>
#include <Framework/Chrono/Public/LocalDateTime.h>
#include <Framework/Chrono/Public/Registry.h>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Chrono/Test/Public/FrozenSteadyMockClock.h>
#include <Framework/Chrono/Test/Public/FrozenSystemMockClock.h>
#include <Framework/Chrono/Test/Public/RunningSteadyMockClock.h>
#include <Framework/Chrono/Test/Public/RunningSystemMockClock.h>

#include <Framework/Config/Public/Attributes.h>

#include <ctime>
#include <stdexcept>

DFL_HEADER_DEPRECATED("use *SystemMockClock instead")

namespace DFL
{
namespace Chrono
{
namespace Test
{
namespace Impl
{
static Chrono::SystemClock::TimePoint toTimePoint(LocalDateTime const& date)
{
    std::tm localTimeStruct{};
    localTimeStruct.tm_sec = static_cast<int>(date.second());
    localTimeStruct.tm_min = date.minute();
    localTimeStruct.tm_hour = date.hour();
    localTimeStruct.tm_mday = date.day();
    localTimeStruct.tm_mon = date.month() - 1;
    localTimeStruct.tm_year = date.year() - 1900;
    localTimeStruct.tm_wday = 0;
    localTimeStruct.tm_yday = 0;

    const time_t localTime = std::mktime(&localTimeStruct);
    if (localTime == -1)
    {
        throw std::runtime_error{
            "Call to mktime with parameter: " + date.toIso8601() + " failed."};
    }
    return Chrono::Impl::SystemClockImpl::from_time_t(localTime);
}
}

/**
 * @deprecated
 */
class DFL_ATTRIBUTE_DEPRECATED("use FrozenSystemMockClock instead")
    SystemMockClock
{
public:
    /**
     * @deprecated
     */
    inline SystemMockClock()
    {
        tempConvertToLocal() = Registry::SystemClock::toLocal;
        Registry::SystemClock::toLocal = Chrono::Impl::SystemClock::toLocal;
    }

    /**
     * @deprecated
     */
    inline ~SystemMockClock()
    {
        Registry::SystemClock::toLocal = tempConvertToLocal();
    }

    /**
     * @param date
     * @deprecated
     */
    inline void setClock(LocalDateTime const& date)
    {
        m_mockClock.setClock(Impl::toTimePoint(date));
    }

private:
    static Registry::SystemClock::ToLocal& tempConvertToLocal()
    {
        static Registry::SystemClock::ToLocal s_toLocal;
        return s_toLocal;
    }

    FrozenSystemMockClock m_mockClock{};
};

}
}
}
