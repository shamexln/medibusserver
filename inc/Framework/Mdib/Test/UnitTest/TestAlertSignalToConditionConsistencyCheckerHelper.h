#pragma once

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>

#include <Framework/Utils/Public/NotNull.h>

namespace DFL::Mdib::Test::Impl
{

namespace SecondTree
{
static const VmdHandle vmdHandle("vmd-tree-2");
static const VmdAlertSystemHandle vmdAlertSystemHandle("vmd-tree-2-alert-system");
static const VmdAlertConditionHandle vmdAlertConditionHandle("vmd-tree-2-alert-condition");
}


DFL::NotNull<LocalMdibAccessUniquePtr> createBaseMdibWithConsistencyChecks();

template<class T_Entity>
void removeEntity(LocalMdibAccess& mdibAccess,
                  MdibChangeSet& changeSet,
                  const BasicHandle<T_Entity>& handle);

template<class T_Entity>
void insertSignalEntity(MdibChangeSet& changeSet,
                        const BasicHandle<T_Entity>& signalHandle,
                        const BasicHandle<typename T_Entity::ParentType>& systemHandle,
                        const Handle& conditionToReference);

template<class T_Entity>
void updateSignalEntity(LocalMdibAccess& mdibAccess,
                        MdibChangeSet& changeSet,
                        const BasicHandle<T_Entity>& signalHandle,
                        const Handle& conditionToReference);

template<class T_Entity>
void insertConditionEntity(MdibChangeSet& changeSet,
                           const BasicHandle<T_Entity>& conditionHandle,
                           const BasicHandle<typename T_Entity::ParentType>& systemHandle);

void add2ndVmdAlertSystemToMdib(LocalMdibAccess& mdibAccess, const MdsHandle& mds);

}
