#pragma once

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Format/Public/StdContainerIo.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Indicates which limits of an alert condition are monitored to trigger alert signals.
 * @details This enum has negative semantics for some elements ('...Off'). See also the convenience functions
 *          @ref setMonitoredLimitHigh() and @ref setMonitoredLimitLow() to use it the other way.
 * @ingroup Mdib
 */
enum class AlertConditionMonitoredLimits
{
    /**
     * @brief Both (lower and upper) alert limits are monitored.
     */
    All,

    /**
     * @brief Low-limit violation detection is either currently turned off
     * if the the enclosing alert state possesses a low-limit value or is not supported at all.
     */
    LowOff,

    /**
     * @brief High-limit violation detection is either currently turned off
     * if the enclosing alert state possesses a high-limit value or is not supported at all.
     */
    HighOff,

    /**
     * @brief No alert limits are monitored.
     */
    None
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AlertConditionMonitoredLimits, (All)(LowOff)(HighOff)(None))


/**
 * @brief Sets 'high limit is monitored' in a @ref AlertConditionMonitoredLimits enum.
 * @ingroup Mdib
 */
inline AlertConditionMonitoredLimits setMonitoredLimitHigh(AlertConditionMonitoredLimits current, bool isMonitored)
{
    if (isMonitored)
    {
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::HighOff)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::All;
        }
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::None)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::LowOff;
        }
    }
    else
    {
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::All)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::HighOff;
        }
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::LowOff)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::None;
        }
    }
    return current;
}

/**
 * @brief Sets 'low limit is monitored' in a @ref AlertConditionMonitoredLimits enum.
 * @ingroup Mdib
 */
inline AlertConditionMonitoredLimits setMonitoredLimitLow(AlertConditionMonitoredLimits current, bool isMonitored)
{
    if (isMonitored)
    {
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::LowOff)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::All;
        }
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::None)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::HighOff;
        }
    }
    else
    {
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::All)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::LowOff;
        }
        if (current == DFL::Mdib::AlertConditionMonitoredLimits::HighOff)
        {
            return DFL::Mdib::AlertConditionMonitoredLimits::None;
        }
    }
    return current;
}

}
}
