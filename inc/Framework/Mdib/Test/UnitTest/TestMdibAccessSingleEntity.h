#pragma once

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/RemoteMdibAccess.h>
#include <Framework/Mdib/Test/UnitTest/Utils/MdibObserverSpy.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>

namespace DFL
{
namespace Mdib
{
namespace Test
{
namespace Impl
{

using WriteInLocalMdibAccess = std::function<DFL::Mdib::WriteResult (DFL::Mdib::LocalMdibAccess &, const DFL::Mdib::MdibChangeSet &)>;
using WriteInRemoteMdibAccess = std::function<DFL::Mdib::WriteResult (DFL::Mdib::RemoteMdibAccess &, DFL::Mdib::VersionCounter, const DFL::Mdib::MdibChangeSet &)>;
using ResolveChangedData = std::function<boost::optional<DFLTest::Mdib::UnitTest::MdibObserverSpy::Change> (const DFLTest::Mdib::UnitTest::MdibObserverSpy &)>;

template<class T_Entity, class T_UnusedEntity>
void testEntityInLocalMdibAccess(const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parentHandle,
                                 const WriteInLocalMdibAccess& writeStateInLocalMdibAccess,
                                 const ResolveChangedData& resolveChangedData);

template<class T_Entity, class T_UnusedEntity>
void testEntityInRemoteMdibAccess(const DFL::Mdib::BasicHandle<typename T_Entity::ParentType>& parentHandle,
                                  TestFactory::InitialMdibTree initMdibTree,
                                  const WriteInRemoteMdibAccess& writeStateInRemoteMdibAccess,
                                  const ResolveChangedData& resolveChangedData);

}
}
}
}
