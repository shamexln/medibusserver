#pragma once

#include <Framework/Mdib/Private/MdibIteratorHelper.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Utils/Entities.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Utils/Public/NotNull.h>
#include <map>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief An iterator that holds an ordered range of handles to child entities modeled as variants.
 * @details This iterator can be used with any object that can access entities with the following
 * method signature:
 *
 * \code{.cpp}
 * template<class T_Entity>
 * SharedPtr<T_Entity> entity(const BasicHandle<T_Entity>& handle) const;
 * \endcode
 *
 * Contract: returns pointer to the entity with given handle if existing or \c nullptr otherwise.
 * @ingroup Mdib
 */
template <class T_ParentEntity, class T_EntityAccess>
class MdibChildIterator: public MdibIteratorTraits<typename T_ParentEntity::ChildType>
{
    public:
        /// @brief The container type that facilitates sequential access for this iterator.
        using ContainerType = SequentialAccess<Handle>;

        /// @brief Const iterator from held container type.
        using Iterator = typename ContainerType::const_iterator;

        /// @brief Constructor.
        MdibChildIterator(const Iterator& handleBegin,
                          const Iterator& handleEnd,
                          const T_EntityAccess* mdib) :
                m_handleIt(handleBegin),
                m_handleEnd(handleEnd),
                m_entityAccess(mdib),
                m_currentEntity(boost::none)
        {
            setCurrentItem();
        }

        /// @brief Dereference operator
        const typename T_ParentEntity::ChildType& operator*() const;
        /// @brief Member of pointer operator
        const typename T_ParentEntity::ChildType* operator->() const;
        /// @brief Increment operator
        MdibChildIterator operator++(int);
        /// @brief Increment operator
        MdibChildIterator& operator++();

        template<class T_ParentEntity1, class T_EntityAccess1>
        friend bool operator==(const MdibChildIterator<T_ParentEntity1, T_EntityAccess1>& lhs, const MdibChildIterator<T_ParentEntity1, T_EntityAccess1>& rhs);
        template<class T_ParentEntity1, class T_EntityAccess1>
        friend bool operator!=(const MdibChildIterator<T_ParentEntity1, T_EntityAccess1>& lhs, const MdibChildIterator<T_ParentEntity1, T_EntityAccess1>& rhs);

    private:
        // entity visitor to find typed entity from untyped handle
        class SetCurrentItemVisitor
        {
            public:
                template<class T_Entity>
                VisitorProcessing visitEntity(const T_EntityAccess& mdib,
                                              const Handle& untypedHandle,
                                              boost::optional<typename T_ParentEntity::ChildType>& typedHandle) const;
        };

        Iterator m_handleIt;
        Iterator m_handleEnd;
        const T_EntityAccess* m_entityAccess;

        boost::optional<typename T_ParentEntity::ChildType> m_currentEntity;

        void setCurrentItem();
        typename T_ParentEntity::ChildType createInvalidEntity() const;
};

template<class T_ParentEntity, class T_EntityAccess>
template<class T_Entity>
inline VisitorProcessing MdibChildIterator<T_ParentEntity, T_EntityAccess>::SetCurrentItemVisitor::visitEntity(const T_EntityAccess& mdib,
                                                                                                               const Handle& untypedHandle,
                                                                                                               boost::optional<typename T_ParentEntity::ChildType>& typedHandle) const
{
    auto entity = mdib.entity(BasicHandle<T_Entity>(untypedHandle));
    if (entity)
    {
        typedHandle = std::move(asNotNull(entity));
        return VisitorProcessing::Cancel;
    }
    return VisitorProcessing::Proceed;
}

template<class T_ParentEntity, class T_EntityAccess>
inline const typename T_ParentEntity::ChildType& MdibChildIterator<T_ParentEntity, T_EntityAccess>::operator*() const
{
    return *m_currentEntity;
}

template<class T_ParentEntity, class T_EntityAccess>
inline const typename T_ParentEntity::ChildType* MdibChildIterator<T_ParentEntity, T_EntityAccess>::operator->() const
{
    return &*m_currentEntity;
}

template<class T_ParentEntity, class T_EntityAccess>
inline MdibChildIterator<T_ParentEntity, T_EntityAccess> MdibChildIterator<T_ParentEntity, T_EntityAccess>::operator++(int)
{
    auto result = MdibChildIterator(*this);
    if (m_handleIt != m_handleEnd)
    {
        ++m_handleIt;
        setCurrentItem();
    }
    return result;
}

template<class T_ParentEntity, class T_EntityAccess>
inline MdibChildIterator<T_ParentEntity, T_EntityAccess>& MdibChildIterator<T_ParentEntity, T_EntityAccess>::operator++()
{
    ++m_handleIt;
    setCurrentItem();
    return *this;
}

template<class T_ParentEntity, class T_EntityAccess>
inline void MdibChildIterator<T_ParentEntity, T_EntityAccess>::setCurrentItem()
{
    m_currentEntity = boost::none;
    if (m_handleIt == m_handleEnd || !m_entityAccess)
    {
        return;
    }

    while (m_handleIt != m_handleEnd)
    {
        T_ParentEntity::ChildEntities::applyVisitorWithEarlyExit(SetCurrentItemVisitor{}, *m_entityAccess, *m_handleIt, m_currentEntity);
        if (m_currentEntity)
        {
            break;
        }
        ++m_handleIt;
    }
    if (!m_currentEntity)
    {
        // Every handle is supposed to be found as a typed variation in the entity access.
        // If that unexpectedly fails, then the iterator is set to end.
        m_handleIt = m_handleEnd;
    }
}

/// @brief 'equal to' operator
template<class T_ParentEntity1, class T_EntityAccess1>
inline bool operator==(const MdibChildIterator<T_ParentEntity1, T_EntityAccess1> &lhs, const MdibChildIterator<T_ParentEntity1, T_EntityAccess1> &rhs)
{
    return lhs.m_handleIt == rhs.m_handleIt;
}

/// @brief 'not equal to' operator
template<class T_ParentEntity1, class T_EntityAccess1>
inline bool operator!=(const MdibChildIterator<T_ParentEntity1, T_EntityAccess1> &lhs, const MdibChildIterator<T_ParentEntity1, T_EntityAccess1> &rhs)
{
    return lhs.m_handleIt != rhs.m_handleIt;
}

}
}
}
