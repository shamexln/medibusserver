#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Public/RemoteMdibAccess.h>

#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional/optional.hpp>

#include <optional>

namespace DFL::Mdib::Impl
{
/**
 * @brief Creates a local MDIB instance.
 * @details
 * This factory function is dll exported in contrast to the impl class to avoid
 * having trouble on Windows systems with
 * https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP NotNull<LocalMdibAccessUniquePtr> createLocal(
    const MdibTreeStore& initialMdib,
    const MdibVersion& initialMdibVersion,
    std::optional<Timestamp> timestamp,
    const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
    const boost::optional<MdStateVersion>& mdStateVersion,
    MdibConstraints constraints,
    PlugIn::Checkers&& checkers,
    PlugIn::Modifiers&& modifiers);

/**
 * @brief Creates a remote MDIB instance.
 * @details
 * This factory function is dll exported in contrast to the impl class to avoid
 * having trouble on Windows systems with
 * https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-2-c4275
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP NotNull<RemoteMdibAccessUniquePtr> createRemote(
    const MdibTreeStore& initialMdib,
    const MdibVersion& initialMdibVersion,
    std::optional<Timestamp> timestamp,
    const boost::optional<MdDescriptionVersion>& mdDescriptionVersion,
    const boost::optional<MdStateVersion>& mdStateVersion,
    MdibConstraints constraints,
    PlugIn::Checkers&& checkers,
    PlugIn::Modifiers&& modifiers);
}
