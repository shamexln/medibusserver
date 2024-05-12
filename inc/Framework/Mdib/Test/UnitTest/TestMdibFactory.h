#pragma once

#include <Framework/Mdib/Private/MdibAccessPlugIn.h>
#include <Framework/Mdib/Private/MdibFactoryImpl.h>
#include <Framework/Mdib/Private/MdibTreeStore.h>
#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Mdib/Public/Model/MdibVersion.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief Creates a \ref LocalMdibAccess instance with specific checkers for
 * Tests.
 *
 * @details Since checkers may impede each other in different testing scenarios
 * when using the regular \ref MdibFactory, this utility class creates a \ref
 * LocalMdibAccess with only the specific checker to be tested.
 *
 * NOTE: It is still a good idea to include a test making sure the new checker
 * is included in \ref MdibFactory.
 * @ingroup Mdib
 */
class TestMdibFactory
{
public:
    /**
     * @brief Create an MdibAccess with a single checker.
     */
    static NotNull<LocalMdibAccessUniquePtr> createLocalMdibAccess(
        NotNull<std::unique_ptr<DFL::Mdib::Impl::PlugIn::Checker>>&& checker);

    /**
     * @brief Create an MdibAccess with multiple checkers
     */
    static NotNull<LocalMdibAccessUniquePtr> createLocalMdibAccess(
        DFL::Mdib::Impl::PlugIn::Checkers&& checkers);
};

inline NotNull<LocalMdibAccessUniquePtr> TestMdibFactory::createLocalMdibAccess(
    NotNull<std::unique_ptr<DFL::Mdib::Impl::PlugIn::Checker>>&& checker)
{
    DFL::Mdib::Impl::PlugIn::Checkers checkers;
    checkers.push_back(std::move(checker));
    return createLocalMdibAccess(std::move(checkers));
}

inline DFL::NotNull<DFL::Mdib::LocalMdibAccessUniquePtr> TestMdibFactory::
    createLocalMdibAccess(DFL::Mdib::Impl::PlugIn::Checkers&& checkers)
{
    return Impl::createLocal(
            DFL::Mdib::Impl::MdibTreeStore(),
            MdibVersion(DFL::Mdib::Uri("http://sequence-id")),
            DFL::Chrono::SystemClock::now(),
            MdDescriptionVersion{VersionCounter{0}},
            MdStateVersion{VersionCounter{0}},
            MdibConstraints{{}},
            std::move(checkers),
            DFL::Mdib::Impl::PlugIn::Modifiers{});
}

}
}
}
