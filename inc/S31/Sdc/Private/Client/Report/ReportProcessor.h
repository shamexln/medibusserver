#pragma once

#include <S31/BicepsXml/S31Only/Report.h>
#include <S31/Safety/Public/Requirement.h>
#include <S31/Safety/Public/Requirements.h>
#include <S31/Sdc/Private/Client/RemoteMdibAccess.h>
#include <S31/Sdc/Private/Client/RemoteMdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Private/Client/Report/ModificationQueue.h>
#include <S31/Sdc/Private/Client/Report/ReportVersionTracker.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <mutex>
#include <string>

namespace S31::Sdc::Impl::Report
{

/**
 * @brief Operating modes of the ReportProcessor.
 * @ingroup S31SdcCommon
 */
enum class ReportProcessorMode
{
    BufferingOnly, ///< Buffer reports only (initial mode).
    SkipOldReports, ///< if the the initial %MDIB was provided, old reports can still be somewhere in the system, if they arrive in the ReportProcessor now, they will be skipped.
    ImmediateApplying, ///< Apply reports immediately, no buffering. Old report will lead to error.
    Stopped ///<  Final mode, for ensuring that %MDIB observers get no more updates after error/offline.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ReportProcessorMode, (BufferingOnly)(SkipOldReports)(ImmediateApplying)(Stopped))

/**
 * @brief Encapsulate the mode of a @ref ReportProcessor.
 * @details
 * Checks transitions of modes - so it's a mini state machine.
 */
class ReportProcessorModeWrapper
{
    public:
        ReportProcessorModeWrapper();

        ReportProcessorModeWrapper(const ReportProcessorModeWrapper&) = delete;
        ReportProcessorModeWrapper(const ReportProcessorModeWrapper&&) = delete;
        ReportProcessorModeWrapper& operator=(const ReportProcessorModeWrapper&) = delete;
        ReportProcessorModeWrapper& operator=(ReportProcessorModeWrapper&&) = delete;

        ReportProcessorModeWrapper& operator=(ReportProcessorMode mode);

        bool operator==(ReportProcessorMode mode) const noexcept;
        bool operator!=(ReportProcessorMode mode) const noexcept;
        ReportProcessorMode get() const noexcept;
    private:
        ReportProcessorMode m_mode{ReportProcessorMode::BufferingOnly};
};



/**
 * @brief When writing to the Mdib, allow result SuccessWithEmptyChangeSet.
 * @details The initial %MDIB can be legally empty.
 * @ingroup S31SdcCommon
 */
enum class AllowSuccessWithEmptyChangeSet
{
    True,
    False
};

/**
 * @brief When write reports to Mdib, should seeing old version be an error?
 * @details When applying the initially queued reports old versions are not an error.
 */
enum class SkipOldVersions
{
    True,
    False
};

/**
 * @brief Sink for eventing reports of subscriptions belonging to one remote device %MDIB.
 *
 * Currently report processing is synchronous. If push() is called then all existing queue elements
 * are processed according to the current operating mode. An optimization could be to make this asynchronous
 * i.e. having a queue the does the %MDIB changes in a separate thread.
 *
 * This class holds the %MDIB for the node/endpoint reference. This @ref DFL::Mdib::MdibAccess is created
 * when the initial %MDIB is provided.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ReportProcessor final
{
    public:
        /**
         * @brief Constructor, initially it will buffer reports only until the initial %MDIB is provided.
         */
        ReportProcessor();

        ~ReportProcessor();

        /**
         *  @brief Returns the %MDIB.
         *  @returns The %MDIB; if there is not yet a %MDIB, nullptr.
         */
        Sdc::Impl::RemoteMdibAccessSharedPtr mdibAccess() const;

        /**
         *  @brief Push a description or state modification report to the processor.
         *  @details
         *  Throws an error if operations fails but only if the processor is in immediate applying mode.
         *  @param modification data the report, either description modifications or state updates
         */
        template <class Mod>
        void push(Mod&& modification);

        /**
         *  @brief To be used when the first %MDIB is received.
         */
        void setInitialMdibAndGoToImmediateApplyingMode(
                const DFL::Mdib::MdibChangeSet& initialMdib,
                const DFL::Mdib::MdibVersion& initialMdibVersion,
                DFL::NotNull<std::unique_ptr<Safety::Requirements>> safetyRequirements);

         /**
          * @brief To be used when the first %MDIB is received without contexts.
          */
         void setInitialMdibAndGoToImmediateApplyingMode(
                 const DFL::Mdib::MdibChangeSet& initialMdib,
                 const DFL::Mdib::MdibVersion& initialMdibVersion,
                 DFL::NotNull<std::unique_ptr<Safety::Requirements>> safetyRequirements,
                 const StateModifications& contextStatesMods);

        /**
         * @brief No further reports will be processed. Object can not recover from this state.
         */
        void stop();

        /**
         * @brief Returns @c true if the processor is already stoped, see @ref stop().
         */
        bool isStopped() const;

    private:
        template <class Mod>
        void writeToMdib(const Mod& modification, SkipOldVersions skipOldVersions);
        static void writeToMdib(
                DFL::Mdib::RemoteMdibAccess&         mdibAccess,
                DFL::Mdib::MdibChangeType            changeType,
                const DFL::Mdib::MdibChangeSet&      changeSet,
                const DFL::Mdib::VersionCounter&     version,
                const AllowSuccessWithEmptyChangeSet allowSuccessWithEmptyChangeSet);

        void writeAllQueueToMdib(SkipOldVersions skipOldVersions);
        void writeMissingContextStates(const StateModifications& contextStatesMods);

        void logBufferingDuration() const;

        ReportVersionTracker m_versionTracker;
        ModificationQueue m_queue;
        ReportProcessorModeWrapper m_operatingMode;
        RemoteMdibAccessSharedPtr m_mdibAccess;
        mutable std::mutex m_operatingModeAndQueueMutex;
        std::mutex m_mdibWriteMutex;
        DFL::Chrono::SteadyClock::TimePoint m_startBuffering;
};


}
