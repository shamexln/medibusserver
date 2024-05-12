#pragma once

#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>

namespace S31::Sdc::Test
{

/**
 * @brief Provides a MDIB timestamp, that is round trip safe regarding SDC network.
 * @ingroup S31SdcCommon
 */
DFL::Mdib::Timestamp now();

/**
 * @brief Rounds a given MDIB timestamp, that is round trip safe regarding SDC network.
 * @ingroup S31SdcCommon
 */
DFL::Mdib::Timestamp roundToSdcResolution(DFL::Mdib::Timestamp timestamp);


inline DFL::Mdib::Timestamp now()
{
    return roundToSdcResolution(DFL::Chrono::SystemClock::now());
}

inline DFL::Mdib::Timestamp roundToSdcResolution(DFL::Mdib::Timestamp timestamp)
{
    return DFL::Chrono::SystemClock::TimePoint{
        // round to milliseconds (BICEPS resolution for timestamps)
        DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(timestamp.time_since_epoch())
    };
}

}
