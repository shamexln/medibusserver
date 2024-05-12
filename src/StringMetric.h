#pragma once

#include <ContinuousBase.h>

#include <Framework/Mdib/Public/Model/Metric/StringMetric.h>

#include <string>

namespace S31::Samples
{
class StringMetric : public ContinuousBase
{
public:
    StringMetric(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess)
        : ContinuousBase(localMdibAccess)
    {
    }
    void initMdib(DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> vmd, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel)
            const override;

private:
    void metricUpdateThread() override;
    void writeMetricValue(const DFL::Mdib::StringMetricHandle& handle, const std::string& value);
};
}  // namespace S31::Samples
