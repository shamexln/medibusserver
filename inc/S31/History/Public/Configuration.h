#pragma once

namespace S31::History
{
/**
 * @brief Configuration for the history service regarding storing of data locally.
 *
 * @ingroup S31CoreHistory
 */
class Configuration
{
public:
    /**
     * @brief Compression level (0..9).
     * @details
     * 0 is no compression, while 9 is best compression.
     * A value of -1 is the default compression from the lib internally used.
     */
    int compressionLevel{-1};

    /**
     * @brief Number of MDIB changes that shall be bundled.
     * @details
     * Most MDIB changes have very similar XML. So have a better compression ratio it makes sense to bundle multiple
     * MDIB changes (change reports like EpisodicMetricReport) together.
     *
     * The bundling is across all kind of MDIB change reports (waveforms, metrics, alerts, ...).
     * For example, when having 16 waveform reports per second, one metric report every second and one alert report
     * every 5 seconds, within 10 seconds 172 MDIB reports are created.
     * So a value of 172 would lead to combining the reports from approximately 10 seconds into one report bundle.
     * This bundle would be compressed afterwards.
     */
    unsigned int reportBundleSize{200U};

    /**
     * @brief Specify maximum number of bundles to hold.
     * @details
     * To avoid unlimited grow of historic data, the maximum number of stored report bundles needs to be configured.
     * As soon as the maximum number is reached, the oldest report bundle is removed.
     */
    unsigned int maxNumberOfBundles{60U};

    /**
     * @brief Specifies how often a complete MDIB snapshot shall be taken.
     *
     * @details
     * A value of 1 specifies that an MDIB snapshot shall be taken with every report bundle.
     * A value of 2 specified that one for every second report bundle of MDIB changes such an MDIB snapshot is taken.
     * A larger value thus save memory with the cost of transmitting more MDIB changes when requesting with initial MDIB
     * snapshot.
     */
    unsigned int mdibSnapshotPeriod{20U};
};
}  // namespace S31::History
