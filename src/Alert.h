#pragma once

#include <ContinuousBase.h>


#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <string>

namespace S31::Samples
{
class Alert : public ContinuousBase
{
public:
    Alert(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess)
        : ContinuousBase(localMdibAccess) {}
    
    void initMdib(DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> vmd, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel)
        const override;


private:
    void metricUpdateThread() override;

    void writeAlertConditionsAndSignals(const DFL::Mdib::VmdAlertSystemHandle& handle, bool alertPresent);
};
}  // namespace S31::Samples
