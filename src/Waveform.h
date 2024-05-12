#pragma once

#include <ContinuousBase.h>

#include <string>
#include <vector>

namespace S31::Samples
{
class Waveform : public ContinuousBase
{
public:
    Waveform(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess);

    void initMdib(DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> vmd, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel)
            const override;
    void start() override;

private:
    std::vector<double> m_samples;
    void metricUpdateThread() override;
    void writeWaveformSample(const std::string& handle, DFL::Chrono::SystemClock::TimePoint determinationTime);
};
}  // namespace S31::Samples
