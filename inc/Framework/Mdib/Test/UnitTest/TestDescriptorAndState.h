#pragma once

#include <Framework/Mdib/Public/Model/EntityFactory.h>
#include <gtest/gtest.h>

namespace DFL
{
namespace Mdib
{
namespace UnitTest
{

template <class Type>
void testDescriptor()
{
    const BasicHandle<Type> handle("handle");
    const BasicHandle<typename Type::ParentType> parent("parent");
    const auto& entity = EntityFactory::create(handle, parent);

    ASSERT_EQ(handle, entity->handle());
    ASSERT_EQ(VersionCounter(0), entity->descriptorVersion());
}

template <class Type>
void testState()
{
    const BasicHandle<Type> handle("handle");
    const BasicHandle<typename Type::ParentType> parent("parent");
    const auto& entity = EntityFactory::create(handle, parent);

    ASSERT_EQ(VersionCounter(0), entity->stateVersion());
    ASSERT_EQ(handle, entity->handle());
    ASSERT_EQ(VersionCounter(0), entity->descriptorVersion());
}

}
}
}
