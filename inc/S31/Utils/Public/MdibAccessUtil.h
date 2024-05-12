#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Utils/Public/NotNull.h>

namespace S31::Utils
{

/**
 * @brief Template functions to simplify access to children in MDIB.
 *
 * @ingroup S31Utils
 */

/**
 * Helper to retrieve all children from a parent
 * @return A range with all children
 */
template <typename T_Child>
inline DFL::Mdib::MdibEntityRange<T_Child> children(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::Mdib::BasicHandle<typename T_Child::ParentType>& parent)
{
    if (parent.isValid())
    {
        auto range(mdib->range<T_Child>(mdib->filters().children<T_Child>(parent)));
        return range;
    }
    return mdib->range<T_Child>();
}

/**
 * Helper to retrieve the first child handle below a parent
 * @return The child handle or invalid handle, if underlying range is empty
 */
template <typename T_Child>
inline DFL::Mdib::BasicHandle<T_Child> firstChildHandle(const DFL::NotNull<DFL::Mdib::MdibSharedPtr>& mdib, const DFL::Mdib::BasicHandle<typename T_Child::ParentType>& parent)
{
    auto range(children<T_Child>(mdib, parent));
    if (!range.empty())
    {
        return (*range.begin())->handle();
    }
    return DFL::Mdib::BasicHandle<T_Child>();
}

/**
 * Helper to retrieve the first child handle below a parent
 * @return The child handle or invalid handle, if underlying range is empty
 */
template <typename T_Entity>
inline DFL::Mdib::SharedPtr<T_Entity> getUniqueEntity(const DFL::Mdib::Mdib& mdib)
{
    auto range = mdib.range<T_Entity>();
    if (range.empty())
    {
        // no entity of that type
        return nullptr;
    }
    auto it = range.begin();
    auto entity = *it;
    if (++it != range.end())
    {
        // not unique
        return nullptr;
    }
    return entity.get();
}


/**
 * Helper to retrieve the first MDS handle from an MDIB
 * @return The MDS handle or invalid handle, if no MDS is found
 */
inline DFL::Mdib::BasicHandle<DFL::Mdib::Mds> firstMdsHandle(const DFL::Mdib::Mdib& mdib)
{
    auto range(mdib.range<DFL::Mdib::Mds>());
    if (!range.empty())
    {
        return (*range.begin())->handle();
    }
    return {};
}

/**
 * Helper to retrieve an unique entity with a specific type.
 * @param mdib The mdib.
 * @param type The type.
 * @return The entity or nullptr, if no unique entity is found.
 */
 template<typename T_Entity>
 inline std::shared_ptr<T_Entity> getUniqueEntity(const DFL::Mdib::Mdib& mdib, const DFL::Mdib::CodedValue& type)
 {
     auto entities(mdib.range<T_Entity>([&](const DFL::NotNull<std::shared_ptr<T_Entity>>& entity) -> bool
     {
         return (entity->descriptor()->type() &&
                 DFL::Mdib::isSemanticallyEqual(type, entity->descriptor()->type().get(), mdib, *entity));
     }));

     if (!entities.empty() && ++entities.begin() == entities.end())
     {
         return (*entities.begin()).get();
     }

     return std::shared_ptr<T_Entity>();
}

/**
 * Helper to retrieve the handle of an unique entity with a specific type.
 * @param mdib The mdib.
 * @param type The type.
 * @return The handle or an invalid handle, if no unique entity is found.
 */
template<typename T_Entity>
inline DFL::Mdib::BasicHandle<T_Entity> getUniqueEntityHandle(const DFL::Mdib::Mdib& mdib, const DFL::Mdib::CodedValue& type)
{
    if (auto entity = getUniqueEntity<T_Entity>(mdib, type))
    {
        return entity->handle();
    }

    return DFL::Mdib::BasicHandle<T_Entity>();
}

/**
 * Helper to retrieve an unique operation with a specific type and operation target.
 * @param mdib The mdib.
 * @param type The type.
 * @param operationTarget The operation target handle.
 * @return The entity or nullptr, if no unique entity is found.
 */
 template<typename T_Entity>
 inline std::shared_ptr<T_Entity> getUniqueOperation(const DFL::Mdib::Mdib& mdib, const DFL::Mdib::CodedValue& type, const DFL::Mdib::Handle& operationTarget)
 {
     auto entities(mdib.range<T_Entity>([&](const DFL::NotNull<std::shared_ptr<T_Entity>>& entity) -> bool
     {
         return (entity->descriptor()->type() &&
                 entity->descriptor()->operationTarget() == operationTarget &&
                 DFL::Mdib::isSemanticallyEqual(type, entity->descriptor()->type().get(), mdib, *entity));
     }));

     if (!entities.empty() && ++entities.begin() == entities.end())
     {
         return (*entities.begin()).get();
     }

     return std::shared_ptr<T_Entity>();
}

 /**
  * Helper to retrieve the handle of unique operation with a specific type and operation target.
  * @param mdib The mdib.
  * @param type The type.
  * @param operationTarget The operation target handle.
  * @return The handle or an invalid handle, if no unique operation is found.
  */
template<typename T_Entity>
inline DFL::Mdib::BasicHandle<T_Entity> getUniqueOperationHandle(const DFL::Mdib::Mdib& mdib, const DFL::Mdib::CodedValue& type, const DFL::Mdib::Handle& operationTarget)
{
    if (auto entity = getUniqueOperation<T_Entity>(mdib, type, operationTarget))
    {
        return entity->handle();
    }

    return DFL::Mdib::BasicHandle<T_Entity>();
}

}
