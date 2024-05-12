#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc
{
/**
 * @brief   Subscription types for MDIB updates
 * @ingroup S31SdcClient
 */
enum class SubscriptionReports
{
    /**
     * @brief All MDIB change reports.
     * @details
     * Covers the following MDIB change reports:
     * - DescriptionModificationReport
     * - EpisodicAlertReport
     * - EpisodicComponentReport
     * - EpisodicMetricReport
     * - EpisodicOperationalStateReport
     * - EpisodicContextReport
     * - WaveformStream
     */
    AllMdibChanges,

    /**
     * @brief All MDIB change reports except WaveformStream.
     * @details
     * Covers the following MDIB change reports:
     * - DescriptionModificationReport
     * - EpisodicAlertReport
     * - EpisodicComponentReport
     * - EpisodicMetricReport
     * - EpisodicOperationalStateReport
     * - EpisodicContextReport
     */
    AllMdibChangesExceptWaveforms,

    /**
     * @brief All MDIB change reports except WaveformStream and EpisodicMetricReport.
     * @details
     * Covers the following MDIB change reports:
     * - DescriptionModificationReport
     * - EpisodicAlertReport
     * - EpisodicComponentReport
     * - EpisodicOperationalStateReport
     * - EpisodicContextReport
     *
     * Due to the fact that no metric and waveform MDIB changes are subscribed only a few updates are received.
     */
    AllMdibChangesExceptMetrics
};
DFL_ENUM_CLASS_STREAM_OPERATOR(
        SubscriptionReports,
        (AllMdibChanges)(AllMdibChangesExceptWaveforms)(AllMdibChangesExceptMetrics))

}
