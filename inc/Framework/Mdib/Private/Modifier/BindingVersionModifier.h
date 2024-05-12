#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>

namespace DFL::Mdib::Impl::PlugIn
{

/**
 * @brief Updates BindingMdibVersion, UnbindingMdibVersion, BindingStartTime, and BindingEndTime if not set.
 * @details
 *
 * Since for \ref DFL::Mdib::LocalMdibAccess the versioning is done automatically,
 * the BindingMdibVersion and UnbindingMdibVersion also has to be set internally,
 * when writing to the %MDIB.
 * Missing required timestamps are also added.
 *
 * S32_SRS_895 and S32_SRS_896:
 * > When the context state of an SDC Provider has been changed from an associated state to an unassociated state (Assoc -> Dis),
 * > then the SDC Provider shall include pm:AbstractContextState/\@BindingEndTime and pm:AbstractContextState/\@UnbindingMdibVersion in the ContextState.
 *
 * ModReq PTSR_21777:
 * > When the patient context state of an SDC Provider has been changed from an unassociated state to an associated
 * > state, then the SDC Provider shall include the current pm:AbstractContextState/\@BindingStartTime and the current
 * > pm:AbstractContextState/\@BindingMdibVersion in its PatientContextState.
 *
 * @ingroup Mdib
 */
class BindingVersionModifier : public Modifier
{
public:
    ModifierResult modifyFromConstChangeSet(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        std::optional<Timestamp> time,
        const MdibChangeSet& changes) override;
    ModifierResult modifyFromMutableChangeSet(
        MdibChangeType changeType,
        const NotNull<MdibSharedPtr>& mdib,
        std::optional<Timestamp> time,
        const NotNull<MdibChangeSetSharedPtr>& changes) override;
};

}
