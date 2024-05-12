#pragma once

#include <Framework/Mdib/Private/MdibIteratorHelper.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibSmartPtr.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalVariant.h>
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
 * @brief An Iterator that holds a range of handles in a multimap and goes over the entities in
 * the also given Mdib.
 *
 * If the iterator meets a handle for which it cannot find an entity the iterator stops an this
 * handle (goes to end() immediately)
 *
 * @ingroup Mdib
 */
template <class T_Entity, class T_Mdib>
class MdibIteratorFromHandles: public MdibIteratorTraits<NotNull<SharedPtr<T_Entity>>>
{
    public:
        /// Handle types of the entity (that is the alert signal)
        using HandleType = BasicHandle<T_Entity>;
        /// underlying map type for the signal index
        using Map = std::multimap<Handle, HandleType>;
        /// Iterator over the index
        using MapIterator = typename Map::const_iterator;

        /// the constructor
        MdibIteratorFromHandles(
                const MapIterator &handleBegin,
                const MapIterator &handleEnd,
                const T_Mdib &mdib):
            m_handleIt(handleBegin),
            m_handleEnd(handleEnd),
            m_mdib(mdib),
            m_currentEntity(createInvalidEntity())
        {
            setCurrentItem();
        }

        /// @brief Dereference operator
        const NotNull<SharedPtr<T_Entity>>& operator*() const;
        /// @brief member of pointer operator
        const NotNull<SharedPtr<T_Entity>>* operator->() const;
        /// @brief increment operator
        MdibIteratorFromHandles operator++(int);
        /// @brief increment operator
        MdibIteratorFromHandles& operator++();

        template<class T_Entity1, class T_Mdib1>
        friend bool operator==(const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &lhs, const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &rhs);
        template<class T_Entity1, class T_Mdib1>
        friend bool operator!=(const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &lhs, const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &rhs);

    private:
        void setCurrentItem();
        NotNull<SharedPtr<T_Entity>> createInvalidEntity() const;

        MapIterator m_handleIt;
        MapIterator m_handleEnd;
        const T_Mdib &m_mdib;

        NotNull<SharedPtr<T_Entity>> m_currentEntity;
};

template<class T_Entity, class T_Mdib>
inline const NotNull<SharedPtr<T_Entity>>& MdibIteratorFromHandles<T_Entity, T_Mdib>::operator*() const
{
    return m_currentEntity;
}

template<class T_Entity, class T_Mdib>
inline const NotNull<SharedPtr<T_Entity>>* MdibIteratorFromHandles<T_Entity, T_Mdib>::operator->() const
{
    return &m_currentEntity;
}

template<class T_Entity, class T_Mdib>
inline MdibIteratorFromHandles<T_Entity, T_Mdib> MdibIteratorFromHandles<T_Entity, T_Mdib>::operator++(int)
{
    auto result = MdibIteratorFromHandles(*this);
    ++m_handleIt;
    setCurrentItem();
    return result;
}

template<class T_Entity, class T_Mdib>
inline MdibIteratorFromHandles<T_Entity, T_Mdib>& MdibIteratorFromHandles<T_Entity, T_Mdib>::operator++()
{
    ++m_handleIt;
    setCurrentItem();
    return (*this);
}

template<class T_Entity, class T_Mdib>
inline void MdibIteratorFromHandles<T_Entity, T_Mdib>::setCurrentItem()
{
    if (m_handleIt == m_handleEnd)
    {
        // no more items
        m_currentEntity = createInvalidEntity();
        return;
    }
    const auto handle = m_handleIt->second;
    auto entity = m_mdib.entity(handle);
    if (!entity)
    {
        m_currentEntity = createInvalidEntity();
        m_handleIt = m_handleEnd;
        return;
    }
    m_currentEntity = asNotNull(entity);
}

/// @brief 'equal to' operator
template<class T_Entity1, class T_Mdib1>
inline bool operator==(const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &lhs, const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &rhs)
{
    return lhs.m_handleIt == rhs.m_handleIt;
}

/// @brief 'not equal to' operator
template<class T_Entity1, class T_Mdib1>
inline bool operator!=(const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &lhs, const MdibIteratorFromHandles<T_Entity1, T_Mdib1> &rhs)
{
    return lhs.m_handleIt != rhs.m_handleIt;
}

template <class T_Entity, class T_Mdib>
inline NotNull<SharedPtr<T_Entity>> MdibIteratorFromHandles<T_Entity, T_Mdib>::createInvalidEntity() const
{
    if constexpr(std::is_same_v<AlertSignalVariant, T_Entity>)
    {
        return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(
            BasicHandle<T_Entity>(),
            DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>()),
            VersionCounter(0),
            DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()),
            VersionCounter(0),
            Handle()));
    }
    else
    {
        return asNotNull(DFL_MDIB_MAKE_SHARED<T_Entity>(
            BasicHandle<T_Entity>(),
            DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::DescriptorType>()),
            VersionCounter(0),
            DFL::asNotNull(DFL_MDIB_MAKE_SHARED<typename T_Entity::StateType>()),
            VersionCounter(0),
            BasicHandle<typename T_Entity::ParentType>()));
    }
}

}
}
}
