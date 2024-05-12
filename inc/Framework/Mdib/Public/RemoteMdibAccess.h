#pragma once

#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Public/RemoteMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/WriteResult.h>

namespace DFL
{
namespace Mdib
{

class MdibChangeSet;

/**
 * @brief MDIB access with no version increment.
 * @ingroup Mdib
 */
class RemoteMdibAccess: public virtual MdibAccess
{
    public:
        /**
         * @brief Writes all alert states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::AlertSystemState
         * - \ref DFL::Mdib::AlertConditionState
         * - \ref DFL::Mdib::LimitAlertConditionState
         * - \ref DFL::Mdib::AlertSignalState
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeAlertStates(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all alert component states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::BatteryState
         * - \ref DFL::Mdib::ChannelState
         * - \ref DFL::Mdib::ClockState
         * - \ref DFL::Mdib::MdsState
         * - \ref DFL::Mdib::VmdState
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeComponentStates(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all context states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::EnsembleContextState
         * - \ref DFL::Mdib::LocationContextState
         * - \ref DFL::Mdib::PatientContextState
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeContextStates(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all (non-waveform) metric states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::EnumStringMetricState
         * - \ref DFL::Mdib::NumericMetricState
         * - \ref DFL::Mdib::StringMetricState
         * - \ref DFL::Mdib::DistributionSampleArrayMetricState
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeMetricStates(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all operation states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::ActivateOperationState
         * - \ref DFL::Mdib::SetAlertStateOperationState
         * - \ref DFL::Mdib::SetComponentStateOperationState
         * - \ref DFL::Mdib::SetContextStateOperationState
         * - \ref DFL::Mdib::SetMetricStateOperationState
         * - \ref DFL::Mdib::SetStringOperationState
         * - \ref DFL::Mdib::SetValueOperationState
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeOperationStates(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all sample array metric states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::RealTimeSampleArrayMetricState
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeSampleArrayMetricStates(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all operation descriptors and states from the given change set.
         * @details This write operation shall only be used if the descriptor really changed since it might cause a lot of data movement.
         *
         * \note Versions are applied as defined.
         */
        virtual WriteResult writeDescription(VersionCounter mdibVersion, const MdibChangeSet& changes) = 0;
};

} /* namespace Mdib */
} /* namespace DFL */
