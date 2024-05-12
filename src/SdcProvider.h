#pragma once

#include <NumericMetric.h>
#include <StringMetric.h>
#include <Waveform.h>

#include <S31/Sdc/S31Only/CommandLineOptions.h>
#include <Alert.h>

namespace S31
{
namespace Sdc
{
class IDispatcher;
class LocalDevice;
}  // namespace Sdc
namespace Samples
{
/**
 * @brief Sample SDC provider for metric values, waveforms and alarms.
 */
class SampleProvider
{
public:
    explicit SampleProvider(CommandLineOptions options);
    ~SampleProvider();

    void start();
    void stop();
    void shutdownMdsAndWaitReportSent();

private:
    bool m_started{false};
    void initMetadata();
    void initPatient();
    void initLocation();

    NumericMetric m_numericMetric;
    Waveform      m_waveform;
    StringMetric  m_stringMetric;
    Alert         m_alert;

    void initMdib();

    int                                               m_paramValue;
    CommandLineOptions                                m_options;
    std::shared_ptr<S31::Sdc::LocalDevice>            m_dpwsDevice;
    DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_localMdibAccess;
    std::shared_ptr<S31::Sdc::IDispatcher>            m_dispatcher;
};
}  // namespace Samples
}  // namespace S31
