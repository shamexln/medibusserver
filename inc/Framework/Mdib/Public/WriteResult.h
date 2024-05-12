#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Config/Public/Attributes.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
class ErrorHandles;
}
/**
 * @brief Definition of a result status that ensues from any MDIB access write operation.
 * @ingroup Mdib
 */
enum class DFL_ATTRIBUTE_NODISCARD WriteStatus
{
    Success,                        //!< %Operation succeed, all elements of the change set were processed
    /// @brief %Operation succeeded but change set contains unprocessed entities
    /// @details E.g. Let the change set contain changed numeric metrics and alert conditions. This change set
    /// is called with @ref LocalMdibAccess::writeAlertStates(). Then @c SuccessWithUnusedEntities is returned
    /// because this call only processes the alert conditions and not the numeric metrics.
    ///
    /// When getting this status then the %MDIB maybe changed or not.
    SuccessWithUnusedEntities,
    SuccessWithEmptyChangeSet,      //!< %Operation succeeded but the change set was empty. The %MDIB was not changed.
    Fail,                           //!< %Operation failed, unspecified error
    DuplicateHandle,                //!< Duplicate handle (inserting not possible, entity already exists)
    HandleNotFound,                 //!< A handle was not found (on update or remove)
    MdibVersionAlreadySeen,         //!< Try to insert data with older MdibVersion in remote MDIBs
    ConsistencyError,               //!< Consistency problem, e.g., given parent does not exists for inserted entity
    InvalidHandle,                  //!< Handle contains empty or invalid characters ( U+0000 to U+0020 or U+FFFD )
    WrongParameter,                 //!< @ref WriteResult::fail() was called with a success code or @ref WriteResult::success() with a error code.
    ModifyPluginError,              //!< Generic change set modifier error, error message should contain details
    CheckPluginError,               //!< Generic change set checker error, error message should contain details
    ExtensionMustUnderstandError    //!< Error processing an unknown MustUnderstand extension
};
DFL_ENUM_CLASS_STREAM_OPERATOR(WriteStatus, (Success)(SuccessWithUnusedEntities)(SuccessWithEmptyChangeSet)(Fail)(DuplicateHandle) \
                               (HandleNotFound)(MdibVersionAlreadySeen)(ConsistencyError)(InvalidHandle)(WrongParameter) \
                               (ModifyPluginError)(CheckPluginError)(ExtensionMustUnderstandError))

/**
 * @brief Definition of a result set that enclose a status plus a change set.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP DFL_ATTRIBUTE_NODISCARD WriteResult
{
    public:
        /**
         * @brief Creates a \ref WriteStatus::Success "successful" write result with the given \ref Mdib::Mdib "MDIB" and \ref MdibChangeSet "change set".
         */
        static WriteResult success(WriteStatus writeStatus, const NotNull<MdibSharedPtr>& mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changeSet);

        /**
         * @brief Creates a failed write result with missing \ref Mdib::Mdib "MDIB" and \ref MdibChangeSet "change set".
         * @param writeStatus The status of the operation
         * @param errorHandles The errorHandles consists of the handle and the parent handle of the failed entity.
         */
        static WriteResult fail(WriteStatus writeStatus, const Impl::ErrorHandles& errorHandles);

        /// Create a failed write result with an generic error message. To be used from plugins.
        static WriteResult fail(WriteStatus writeStatus, const DFL::Locale::Utf8& errorDescription);

        /**
         * @brief Checks if a write result is one that succeeded.
         * @return \c true if the write status is \ref WriteStatus::Success, \ref WriteStatus::SuccessWithUnusedEntities
         * or \ref WriteStatus::SuccessWithEmptyChangeSet, otherwise \c false.
         */
        [[nodiscard]] bool isSuccess() const;

        /**
         * @brief Returns the write status of the write result.
         */
        const WriteStatus& status() const;

        /**
         * @brief Returns the \ref Mdib::Mdib "Mdib" of the write result in case of success, otherwise \c nullptr.
         */
        MdibSharedPtr mdib() const;

        /**
         * @brief Returns the change set of the write result in case of success, otherwise \c nullptr.
         */
        ConstMdibChangeSetSharedPtr changeSet() const;

        /**
         * @brief Provides debug message for error discovery.
         */
        const DFL::Locale::Utf8& error() const;

    private:

        WriteResult(WriteStatus writeStatus, const NotNull<MdibSharedPtr> &mdib, const NotNull<ConstMdibChangeSetSharedPtr>& changeSet);
        WriteResult(WriteStatus status, const Impl::ErrorHandles& errorHandles);
        WriteResult(WriteStatus status, DFL::Locale::Utf8 errorDescription);
        DFL::Locale::Utf8 errorMessage(const DFL::Mdib::Handle& errorHandle, const DFL::Mdib::Handle& parentHandle);

        WriteStatus m_status;
        MdibSharedPtr m_mdib;
        ConstMdibChangeSetSharedPtr m_changeSet;
        DFL::Locale::Utf8 m_error;
};

} /* namespace Mdib */
} /* namespace DFL */
