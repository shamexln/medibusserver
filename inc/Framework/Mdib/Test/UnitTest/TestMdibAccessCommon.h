#pragma once

#include <Framework/Mdib/Public/Model/MdibVersion.h>
#include <Framework/Mdib/Public/WriteResult.h>
#include <Framework/Mdib/Test/UnitTest/Utils/MdibObserverSpy.h>
#include <functional>
#include <boost/optional.hpp>

namespace DFL
{
namespace Mdib
{
namespace Test
{
namespace Impl
{
using ObserverCallback = std::function<boost::optional<DFLTest::Mdib::UnitTest::MdibObserverSpy::Change>(void)>;

template<class T_Entity>
void checkExistenceInsertedLocal(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                 const MdibVersion& expectedMdibVersion,
                                 const WriteResult& writeResult,
                                 const DFLTest::Mdib::UnitTest::MdibObserverSpy& observer,
                                 ObserverCallback getChange,
                                 int callerLineNumber);

template<class T_Entity>
void checkExistenceUpdatedLocal(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                const MdibVersion& expectedMdibVersion,
                                const WriteResult& writeResult,
                                const DFLTest::Mdib::UnitTest::MdibObserverSpy& observer,
                                ObserverCallback getChange,
                                int callerLineNumber);

template<class T_Entity>
void checkExistenceRemovedLocal(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                const MdibVersion& expectedMdibVersion,
                                const WriteResult& writeResult,
                                const DFLTest::Mdib::UnitTest::MdibObserverSpy& observer,
                                ObserverCallback getChange,
                                int callerLineNumber);

template<class T_Entity>
void checkExistenceInsertedRemote(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                  const MdibVersion& expectedMdibVersion,
                                  const WriteResult& writeResult,
                                  const DFLTest::Mdib::UnitTest::MdibObserverSpy& observer,
                                  ObserverCallback getChange,
                                  int callerLineNumber);

template<class T_Entity>
void checkExistenceUpdatedRemote(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                 const MdibVersion& expectedMdibVersion,
                                 const WriteResult& writeResult,
                                 const DFLTest::Mdib::UnitTest::MdibObserverSpy& observer,
                                 ObserverCallback getChange,
                                 int callerLineNumber);

template<class T_Entity>
void checkExistenceRemovedRemote(const DFL::Mdib::BasicHandle<T_Entity>& handle,
                                 const MdibVersion& expectedMdibVersion,
                                 const WriteResult& writeResult,
                                 const DFLTest::Mdib::UnitTest::MdibObserverSpy& observer,
                                 ObserverCallback getChange,
                                 int callerLineNumber);

}
}
}
}
