#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibEntityRange.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalVariant.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace DFL
{
namespace Mdib
{
class Mdib;
namespace Impl
{
class MdibTreeStore;
}
/**
 * @brief Query template class. Get data like parent entities or signals of alert conditions.
 *
 * @ingroup Mdib
 */
class MdibQuery
{
    public:
        /// Constructor
        MdibQuery(const Mdib &parentMdib, const Impl::MdibTreeStore& treeStore):
            m_parentMdib(parentMdib),
            m_treeStore(treeStore)
        {}

        /**
         * @name Get Parent
         * @brief Get the direct parent of an entity.
         * @returns the parent or an empty element if it was not found. Note that the return type is just SharedPtr<T_Entity::ParentType>
         *
         * ### Example
         * @snippet Mdib/Test/UnitTest/TestMdib.cpp getparent
         *
         */
        ///@{
        /// get the parent by entity reference
        template<class T_Entity>
        SharedPtr<typename T_Entity::ParentType> parent(const T_Entity &entity) const;
        /// get the parent by shared pointer of entity
        template<class T_Entity>
        SharedPtr<typename T_Entity::ParentType> parent(const SharedPtr<T_Entity> &entity) const;
        /// get the parent by not null pointer of an shared pointer of the entity
        template<class T_Entity>
        SharedPtr<typename T_Entity::ParentType> parent(const NotNull<SharedPtr<T_Entity>> &entity) const;
        ///@}

        /**
         * @brief Get an iterator range for the signals of an alert condition.
         * @details
         * The return type cannot be derived from the alert condition type due
         * to one common use case. When having a VMD with an alert system very
         * often the alert conditions from the VMD have signal in the MDS. Thus,
         * it is required to support having NDS alert signal as well as VMD
         * alert signal for a VMD alert condition.
         * @param handle The (typed) handle of the alert condition.
         */
        template<class T_AlertCondition>
        MdibEntityRangeFromHandles<AlertSignalVariant, Mdib> alertSignals(BasicHandle<T_AlertCondition> handle) const;

    private:
        const Mdib& m_parentMdib;
        const Impl::MdibTreeStore& m_treeStore;
};

template<class T_Entity>
inline SharedPtr<typename T_Entity::ParentType> MdibQuery::parent(const SharedPtr<T_Entity> &entity) const
{
    if (!entity)
    {
        return SharedPtr<typename T_Entity::ParentType>();
    }
    return parent(*entity);
}

template<class T_Entity>
inline SharedPtr<typename T_Entity::ParentType> MdibQuery::parent(const NotNull<SharedPtr<T_Entity>> &entity) const
{
    return parent(*entity);
}

}
}
