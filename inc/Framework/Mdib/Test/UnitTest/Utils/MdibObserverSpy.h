#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Mdib/Public/SubdividedMdibObserver.h>
#include <memory>

namespace DFLTest
{
namespace Mdib
{
namespace UnitTest
{

class MdibObserverSpy: public DFL::Mdib::MdibObserver, public DFL::Mdib::SubdividedMdibObserver
{
    public:
        // from DFL::Mdib::MdibObserver
        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) override;

        // from DFL::Mdib::SubdividedMdibObserver
        void onDescriptionChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onAlertChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onComponentChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onContextChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onOperationChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onSampleArrayMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;

        struct Change
        {
            Change(DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdib,
                   DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr> changes,
                   DFL::Mdib::MdibChangeType changeType) :
                    mdib(std::move(mdib)),
                    changes(std::move(changes)),
                    changeType(changeType)
            {
            }

            DFL::NotNull<DFL::Mdib::MdibSharedPtr> mdib;
            DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr> changes;
            DFL::Mdib::MdibChangeType changeType;
        };

        boost::optional<Change> latestChange() const;
        boost::optional<Change> latestDescriptionChange() const;
        boost::optional<Change> latestAlertChange() const;
        boost::optional<Change> latestComponentChange() const;
        boost::optional<Change> latestContextChange() const;
        boost::optional<Change> latestMetricChange() const;
        boost::optional<Change> latestOperationChange() const;
        boost::optional<Change> latestSampleArrayMetricChange() const;

        void resetSpy();

    private:
        boost::optional<Change> m_latestChange;
        boost::optional<Change> m_latestDescriptionChange;
        boost::optional<Change> m_latestAlertChange;
        boost::optional<Change> m_latestComponentChange;
        boost::optional<Change> m_latestContextChange;
        boost::optional<Change> m_latestMetricChange;
        boost::optional<Change> m_latestOperationChange;
        boost::optional<Change> m_latestWaveformChange;
};

}
}
}
