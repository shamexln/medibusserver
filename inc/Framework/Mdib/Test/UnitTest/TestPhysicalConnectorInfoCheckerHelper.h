#pragma once

#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFL::Mdib::Test::Impl
{

template<class Entity_T>
void checkPhysicalConnectorInfoSingle(const BasicHandle<typename Entity_T::ParentType>& parentHandle);

template<class Entity_T>
void checkPhysicalConnectorInfo(const BasicHandle<typename Entity_T::ParentType>& parentHandle,
                                const BasicHandle<typename Entity_T::ParentType>& otherParentHandle);

template<class Entity_T>
void checkPhysicalConnectorInfoWithUnit(const BasicHandle<typename Entity_T::ParentType>& parentHandle);

template<class Entity_T>
void checkPhysicalConnectorInfoWithDifferentCategory(const BasicHandle<typename Entity_T::ParentType>& parentHandle);

template<class Entity_T>
void checkPhysicalConnectorInfoPreconditions(const BasicHandle<typename Entity_T::ParentType>& parent);

}
