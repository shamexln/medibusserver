#pragma once

#include <ContinuousBase.h>

#include <string>

namespace S31::Samples
{
class NumericMetric : public ContinuousBase
{
public:
    NumericMetric(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess)
        : ContinuousBase(localMdibAccess){};

    void initMdib(DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> vmd, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel)
            const override;

private:
    void metricUpdateThread() override;

    void writeMetricValue(const std::string& handle, int value);
};
}  // namespace S31::Samples
