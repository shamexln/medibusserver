#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Mdib/Public/WriteResult.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8.h>

#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @ingroup Mdib
 */
enum class CheckerStatus
{
    CheckOk,
    CheckFailed
};
DFL_ENUM_CLASS_STREAM_OPERATOR(CheckerStatus, (CheckOk)(CheckFailed))

/**
 * @ingroup Mdib
 */
enum class ModifierStatus
{
    ChangeSetUnchanged,
    ChangeSetModified,
    ModifyFailed
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ModifierStatus, (ChangeSetUnchanged)(ChangeSetModified)(ModifyFailed))


/**
 * @brief Result object of a @ref MdibChangeSet check operation.
 * @ingroup Mdib
 */
class CheckerResult
{
    public:
        CheckerResult(CheckerStatus status, Locale::Utf8 message):
                m_status(status),
                m_message(std::move(message))
        {
        }

        CheckerStatus status() const
        {
            return m_status;
        }

        /**
         * @brief A text describing why the check failed or empty.
         */
        const Locale::Utf8& message() const
        {
            return m_message;
        }

        static CheckerResult ok();

    private:
        CheckerStatus m_status;
        Locale::Utf8 m_message;
};

/**
 * @brief Result object of a @ref MdibChangeSet modify operation.
 * @ingroup Mdib
 */
class ModifierResult
{
    public:
        static ModifierResult unchanged()
        {
            return {ModifierStatus::ChangeSetUnchanged, Locale::Utf8(), nullptr};
        }

        ModifierResult(ModifierStatus status, Locale::Utf8 message, MdibChangeSetSharedPtr modifiedChangeSet):
            m_status(status), m_message(std::move(message)), m_modifiedChangeSet(std::move(modifiedChangeSet)) {}
        ModifierStatus status() const
        {
            return m_status;
        }

        /**
         * @brief A text describing why modification failed or empty.
         */
        const Locale::Utf8& message() const
        {
            return m_message;
        }

        /**
         * @brief If modification was done then this is set.
         */
        const MdibChangeSetSharedPtr& modifiedChangeSet()
        {
            return m_modifiedChangeSet;
        }
    private:
        ModifierStatus m_status;
        Locale::Utf8 m_message;
        MdibChangeSetSharedPtr m_modifiedChangeSet;
};

/**
 * @brief Result object for multiple change set modify and check operations.
 * @ingroup Mdib
 */
struct ModifiersAndCheckersResult
{
    public:
        ModifiersAndCheckersResult(
                PlugIn::ModifierStatus modifierStatus, PlugIn::CheckerStatus checkerStatus, MdibChangeSetSharedPtr newChangeSet, DFL::Locale::Utf8 errorMessage):
            m_modifierStatus(modifierStatus),
            m_checkerStatus(checkerStatus),
            m_newChangeSet(std::move(newChangeSet)),
            m_errorMessage(std::move(errorMessage)) {}

        PlugIn::ModifierStatus modifierStatus() const
        {
            return m_modifierStatus;
        }

        PlugIn::CheckerStatus checkerStatus() const
        {
            return m_checkerStatus;
        }

        MdibChangeSetSharedPtr newChangeSet() const
        {
            return m_newChangeSet;
        }

        const DFL::Locale::Utf8& errorMessage() const
        {
            return m_errorMessage;
        }

    private:
        PlugIn::ModifierStatus m_modifierStatus;
        PlugIn::CheckerStatus m_checkerStatus;
        MdibChangeSetSharedPtr m_newChangeSet;
        DFL::Locale::Utf8 m_errorMessage;
};


/**
 * @brief Base class for @ref MdibChangeSet check operations.
 * @ingroup Mdib
 */
class Checker
{
    public:
        virtual ~Checker() = default;
        /**
         * @brief Checker implementation have to implement the check here.
         */
        virtual CheckerResult check(MdibChangeType changeType,
                                    const NotNull<MdibSharedPtr> &mdib,
                                    const MdibTreeStore &mdibTreeStore,
                                    const MdibChangeSet& changes) = 0;
};

/**
 * @brief Base class for @ref MdibChangeSet modify operations.
 * @details E.g., tree remover functionality.
 * @ingroup Mdib
 */
class Modifier
{
    public:
        virtual ~Modifier() = default;
        /**
         * @name Implementation of modify functions.
         *
         * Derived classes have to implement two ways to perform modification. MdibAccess will call exactly one of this
         * for a change set.  Note that a modifier must not make changes that would alter the MdibChangeType of a write
         * operation, since multiple reports cannot be made for the same MdibVersion.
         */
        ///@{
        /**
        * @brief Perform modification.
        *
        * @param changeType Provides information about which write operation was called
        * @param mdib Current Mdib
        * @param time Write time of the local Mdib changes
        * @param changes Immutable changeset. If there is a change to be performed the modifier has to make a copy
        * of the change set first.
        */
        virtual ModifierResult modifyFromConstChangeSet(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            std::optional<Timestamp> time,
            const MdibChangeSet& changes) = 0;
        /**
        * @brief Perform modification.
        *
        * @param changeType Provides information about which write operation was called
        * @param mdib Current Mdib
        * @param time Write time of the local Mdib changes
        * @param changes Mutable changeset. If there is a change to be performed the modifier has to make the changes on this change set
        */
        virtual ModifierResult modifyFromMutableChangeSet(
            MdibChangeType changeType,
            const NotNull<MdibSharedPtr>& mdib,
            std::optional<Timestamp> time,
            const NotNull<MdibChangeSetSharedPtr>& changes) = 0;
        ///@}

};

/**
 * @brief Sequence of \ref DFL::Mdib::Impl::PlugIn::Checker.
 * @ingroup Mdib
 */
using Checkers = std::vector<NotNull<std::unique_ptr<Checker> > >;

/**
 * @brief Sequence of \ref DFL::Mdib::Impl::PlugIn::Modifier.
 * @ingroup Mdib
 */
using Modifiers = std::vector<NotNull<std::unique_ptr<Modifier> > >;

}
