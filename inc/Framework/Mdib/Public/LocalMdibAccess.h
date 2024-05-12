#pragma once

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/WriteResult.h>

namespace DFL
{
namespace Mdib
{

class MdibChangeSet;
class MdibConstraints;

/**
 * @brief MDIB access with automatic version increment.
 * @ingroup Mdib
 */
class LocalMdibAccess: public virtual MdibAccess
{
    public:
        /**
         * @brief Writes all alert states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::AlertConditionState
         * - \ref DFL::Mdib::AlertSignalState
         * - \ref DFL::Mdib::AlertSystemState
         * - \ref DFL::Mdib::LimitAlertConditionState
         *
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeAlertStates(const MdibChangeSet& changes) = 0;

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
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeComponentStates(const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all context states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::EnsembleContextState
         * - \ref DFL::Mdib::LocationContextState
         * - \ref DFL::Mdib::PatientContextState
         *
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeContextStates(const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all (non-waveform) metric states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::EnumStringMetricState
         * - \ref DFL::Mdib::NumericMetricState
         * - \ref DFL::Mdib::StringMetricState
         * - \ref DFL::Mdib::DistributionSampleArrayMetricState
         *
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeMetricStates(const MdibChangeSet& changes) = 0;

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
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeOperationStates(const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all sample array metric states from the given change set.
         * @details This comprises
         *
         * - \ref DFL::Mdib::RealTimeSampleArrayMetricState
         *
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeSampleArrayMetricStates(const MdibChangeSet& changes) = 0;

        /**
         * @brief Writes all operation descriptors and states from the given change set.
         * @details This write operation shall only be used if the descriptor really changed since it might cause a lot of data movement.
         *
         * \note Affected versions are incremented accordingly.
         */
        virtual WriteResult writeDescription(const MdibChangeSet& changes) = 0;

        /**
         * @brief Provides the \ref DFL::Mdib::MdibConstraints of the Mdib
         */
        [[nodiscard]] virtual const MdibConstraints& constraints() const = 0;
};



} /* namespace Mdib */
} /* namespace DFL */
