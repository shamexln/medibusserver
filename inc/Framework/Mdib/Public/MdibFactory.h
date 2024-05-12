#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/RemoteMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Utils/Public/NotNull.h>
#include <memory>

namespace DFL
{
namespace Mdib
{

class MdibVersion;
class MdibChangeSet;

/**
 * @brief Constructs \ref LocalMdibAccess "local" and \ref RemoteMdibAccess "remote" %MDIB instances.
 * @details Local and remote differ in consistency checks and auto versioning for example.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP MdibFactory
{
    public:

        /**
         * @brief Creates a new %MDIB representing the local device to provide medical data.
         * @details The %MDIB start with version 0 and a random UUID as sequence identifier.
         *
         * Depending on the configuration of the constraints different consistency checks are added to
         * the MDIB to ensure consistent data. It is customizable due to the fact that not all
         * instances have the same consistency requirements. Without specifying any role only
         * basic consistency checks are done.
         *
         * @param constraints Roles that apply to the MDIB instance.
         */
        static NotNull<LocalMdibAccessUniquePtr> createLocalMdibAccess(const MdibConstraints& constraints);

        /**
         * @brief Creates a new %MDIB representing the local device to provide medical data.
         * @details The %MDIB start with version 0 and a random UUID as sequence identifier. See
         * @ref createLocalMdibAccessWithConsistencyChecks() and @ref createLocalMdibAccessLean(), which
         * create %MDIBs with different handling of checking/ensuring consistency requirements.
         *
         * @deprecated Use ctor with \ref DFL::Mdib::MdibConstraints "MdibConstraints".
         */
        DFL_ATTRIBUTE_DEPRECATED("Use MdibFactory::createLocalMdibAccess(const MdibConstraints&) instead")
        static NotNull<LocalMdibAccessUniquePtr> createLocalMdibAccess();

        /**
         * @brief Creates a new %MDIB representing the local device to provide medical data.
         * @details The %MDIB start with version 0 and a random UUID as sequence identifier. The
         * %MDIB will check certain consistency requirements. In contrast to @ref createLocalMdibAccess()
         * it will not modify write operation to ensure requirements. E.g. setting an @ref Mds to @b Off will
         * fail if some child is not @b Off. An %MDIB created with @ref createLocalMdibAccess() will handle this
         * and set all children @b Off.
         *
         * @deprecated Use ctor with \ref DFL::Mdib::MdibConstraints "MdibConstraints".
         */
        DFL_ATTRIBUTE_DEPRECATED("Use MdibFactory::createLocalMdibAccess(const MdibConstraints&) instead")
        static NotNull<LocalMdibAccessUniquePtr> createLocalMdibAccessWithConsistencyChecks();

        /**
         * @brief Creates a new %MDIB representing the local device to provide medical data.
         * @details The %MDIB start with version 0 and a random UUID as sequence identifier. The %MDIB will have
         * no checks of requirements or ensure requirements from standard. Users of this %MDIB must ensure that all
         * changes fulfill requirements from the standard, e.g. that an inactive MDS does not contain active metrics.
         *
         * @deprecated Use ctor with \ref DFL::Mdib::MdibConstraints "MdibConstraints".
         */
        DFL_ATTRIBUTE_DEPRECATED("Use MdibFactory::createLocalMdibAccess(const MdibConstraints&) instead")
        static NotNull<LocalMdibAccessUniquePtr> createLocalMdibAccessLean();

        /**
         * @brief Creates a new %MDIB representing a remote device for local access to the remote data.
         * @param mdibVersion Initial %MDIB version (typically from network).
         */
        static NotNull<RemoteMdibAccessUniquePtr> createRemoteMdibAccess(const MdibVersion& mdibVersion);
};

}
}
