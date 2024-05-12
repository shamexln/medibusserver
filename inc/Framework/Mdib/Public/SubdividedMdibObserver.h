#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL::Mdib
{
/**
 * @brief Interface to register for \ref MdibChangeSet "MDIB changes" of \ref
 * MdibAccess subject.
 * @details
 * \attention This interface is in accordance to the message model of SDC.
 *            Please do not use it if you are not confident with SDC internals!
 *
 * Right now for a writeDescription() call a DescriptionModificationReport
 * callback as well as optional callbacks for EpisodicAlertReport,
 * EpisodicComponentReport, ... are created. Later on, when that behaviour is
 * changed for SDC, only the DescriptionModificationReport would be required and
 * called on the observer.
 * @ingroup Mdib
 */
class SubdividedMdibObserver
{
    public:
        virtual ~SubdividedMdibObserver() noexcept = default;

        /**
         * @brief Callback for DescriptionModificationReport message event.
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onDescriptionChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;

        /**
         * @brief Callback for EpisodicAlertReport message event.
         * @details Alert changes comprise
         *
         * - \ref DFL::Mdib::AlertCondition "AlertCondition"
         * - \ref DFL::Mdib::AlertSignal "AlertSignal"
         * - \ref DFL::Mdib::AlertSystem "AlertSystem"
         * - \ref DFL::Mdib::LimitAlertCondition "LimitAlertCondition"
         *
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onAlertChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;

        /**
         * @brief Callback for EpisodicComponentReport message event.
         * @details Component changes comprise
         *
         * - \ref DFL::Mdib::Battery "Battery"
         * - \ref DFL::Mdib::Channel "Channel"
         * - \ref DFL::Mdib::Clock "Clock"
         * - \ref DFL::Mdib::Mds "Mds"
         * - \ref DFL::Mdib::Vmd "Vmd"
         *
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onComponentChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;

        /**
         * @brief Callback for EpisodicContextReport message event.
         * @details Context changes comprise
         *
         * - \ref DFL::Mdib::EnsembleContext "EnsembleContext"
         * - \ref DFL::Mdib::LocationContext "LocationContext"
         * - \ref DFL::Mdib::PatientContext "PatientContext"
         *
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onContextChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;

        /**
         * @brief Callback for EpisodicMetricReport message event.
         * @details Metric changes comprise
         *
         * - \ref DFL::Mdib::EnumStringMetric "EnumStringMetric"
         * - \ref DFL::Mdib::NumericMetric "NumericMetric"
         * - \ref DFL::Mdib::StringMetric "StringMetric"
         * - \ref DFL::Mdib::DistributionSampleArrayMetric "DistributionSampleArrayMetric"
         *
         * \todo enable EnumStringMetric reference
         *
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onMetricChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;

        /**
         * @brief Callback for EpisodicOperationalStateReport message event.
         * @details Context changes comprise
         *
         * - \ref DFL::Mdib::ActivateOperation "ActivateOperation"
         * - \ref DFL::Mdib::SetAlertStateOperation "SetAlertStateOperation"
         * - \ref DFL::Mdib::SetComponentStateOperation "SetComponentStateOperation"
         * - \ref DFL::Mdib::SetContextStateOperation "SetContextStateOperation"
         * - \ref DFL::Mdib::SetMetricStateOperation "SetMetricStateOperation"
         * - \ref DFL::Mdib::SetStringOperation "SetStringOperation"
         * - \ref DFL::Mdib::SetValueOperation "SetValueOperation"
         *
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onOperationChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;

        /**
         * @brief Callback for WaveformStream message event.
         * @details Sample array metric changes comprise
         *
         * - \ref DFL::Mdib::RealTimeSampleArrayMetric "RealTimeSampleArrayMetric"
         *
         * @param mdib Whole MDIB on where the changes have been applied. This argument is never \c nullptr
         *             unless a memory allocation error occurs.
         * @param changes Change set that comprises changed entities only. This argument is never \c nullptr
         *                unless a memory allocation error occurs.
         */
        virtual void onSampleArrayMetricChange(const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changes) = 0;
};

}
