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

class PublisherObserverSpy: public DFL::Mdib::MdibObserver, public DFL::Mdib::SubdividedMdibObserver
{
    public:
        void onChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes, DFL::Mdib::MdibChangeType changeType) override;

        void onDescriptionChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onAlertChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onComponentChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onContextChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onOperationChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;
        void onSampleArrayMetricChange(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::NotNull<DFL::Mdib::ConstMdibChangeSetSharedPtr>& changes) override;

        unsigned int totalOnChanges() const;

        unsigned int numOnChangeTypeDescription() const;
        unsigned int numOnChangeTypeAlert() const;
        unsigned int numOnChangeTypeComponent() const;
        unsigned int numOnChangeTypeContext() const;
        unsigned int numOnChangeTypeMetric() const;
        unsigned int numOnChangeTypeOperation() const;
        unsigned int numOnChangeTypeWaveform() const;

        unsigned int totalSubdividedChanges() const;
        unsigned int numSubdividedDescChanges() const;
        unsigned int numSubdividedAlertChanges() const;
        unsigned int numSubdividedMetricChanges() const;
        unsigned int numSubdividedComponentChanges() const;
        unsigned int numSubdividedContextChanges() const;
        unsigned int numSubdividedOperationChanges() const;
        unsigned int numSubdividedSampleChanges() const;

        void resetSpy();

    private:
        unsigned int m_totalOnChanges{};
        unsigned int m_onChangeTypeDescription{};
        unsigned int m_onChangeTypeAlert{};
        unsigned int m_onChangeTypeComp{};
        unsigned int m_onChangeTypeContext{};
        unsigned int m_onChangeTypeOperation{};
        unsigned int m_onChangeTypeMetric{};
        unsigned int m_onChangeTypeWaveform{};

        unsigned int m_subdividedDescChanges{};
        unsigned int m_subdividedAlertChanges{};
        unsigned int m_subdividedCompChanges{};
        unsigned int m_subdividedContextChanges{};
        unsigned int m_subdividedOperationChanges{};
        unsigned int m_subdividedMetricChanges{};
        unsigned int m_subdividedWaveformChanges{};
};
}
}
}
