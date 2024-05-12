#pragma once

#include <Framework/Mdib/Private/MdibIteratorHelper.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Handle.h>

#include <Framework/Utils/Public/NotNull.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Type for iterators that run random access containers.
 */
template<class T_Entity>
using RandomEntityAccess = RandomAccess<NotNull<SharedPtr<T_Entity>>, BasicHandle<T_Entity>>;

/**
 * @brief Type for iterators that run sequential access containers.
 */
template<class T_Entity>
using SequentialEntityAccess = SequentialAccess<NotNull<SharedPtr<T_Entity>>>;

/**
 * @brief A template for iterators for Mdib entity containers.
 *
 * Used to give Mdib users access to entities without revealing internal container structures.
 *
 * For now this wraps a std::map iterator, but if needed there could be specializations of this this template
 * of other types that work similar transparent for the end user.
 *
 * @ingroup Mdib
 */
template<class T_Entity, class T_Container = RandomEntityAccess<T_Entity>>
class MdibIterator: public MdibIteratorTraits<NotNull<SharedPtr<T_Entity>>>
{
    public:
        /// @brief Function type that is used for filtering
        using FilterFunction = std::function<bool(const NotNull<SharedPtr<T_Entity>>&)>;

        /// @brief Access to underlying iterator container type, e.g., \c std::map or \c std::vector.
        using ContainerType = T_Container;

        /// @brief Constructor for iteration over all items
        MdibIterator(typename T_Container::const_iterator itbegin,
                     typename T_Container::const_iterator itend):
                m_it(itbegin),
                m_itEnd(itend),
                m_filterFunction()
        {}

        /// @brief Constructor for iteration over filtered items
        MdibIterator(typename T_Container::const_iterator itbegin,
                     typename T_Container::const_iterator itend,
                     FilterFunction filterFunction):
                m_it(itbegin),
                m_itEnd(itend),
                m_filterFunction(std::move(filterFunction))
        {
            goToNextSatisfyingEntity();
        }

        /// @brief Constructor for iteration over filtered items
        MdibIterator(const MdibIterator<T_Entity, T_Container>& itbegin, FilterFunction filterFunction):
                m_it(itbegin.m_it),
                m_itEnd(itbegin.m_itEnd),
                m_filterFunction(filterFunction)
        {
            if (itbegin.m_filterFunction)
            {
                // chain the filter functions if src iterator has a filter function already
                m_filterFunction = [=](const NotNull<SharedPtr<T_Entity>>& e) -> bool
                {
                    return itbegin.m_filterFunction(e) && filterFunction(e);
                };
            }
            goToNextSatisfyingEntity();
        }

        /// @brief Dereference operator
        const NotNull<SharedPtr<T_Entity>>& operator*() const;
        /// @brief member of pointer operator
        const NotNull<SharedPtr<T_Entity>>* operator->() const;
        /// @brief increment operator
        MdibIterator<T_Entity, T_Container> operator++(int);
        /// @brief increment operator
        MdibIterator<T_Entity, T_Container>& operator++();

        template<class T_Entity1, class T_Container1>
        friend bool operator==(const MdibIterator<T_Entity1, T_Container1> &lhs, const MdibIterator<T_Entity1, T_Container1> &rhs);
        template<class T_Entity1, class T_Container1>
        friend bool operator!=(const MdibIterator<T_Entity1, T_Container1> &lhs, const MdibIterator<T_Entity1, T_Container1> &rhs);
    private:
        void goToNextSatisfyingEntity();

        typename T_Container::const_iterator m_it;
        typename T_Container::const_iterator m_itEnd;
        FilterFunction m_filterFunction;

        static const NotNull<SharedPtr<T_Entity>>& getEntityFromIteratorValue(const NotNull<SharedPtr<T_Entity>>& iteratorValue);
        static const NotNull<SharedPtr<T_Entity>>& getEntityFromIteratorValue(const std::pair<BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>& iteratorValue);
        static const NotNull<SharedPtr<T_Entity>>& getEntityFromIteratorValue(const std::pair<const BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>& iteratorValue);
};

template<class T_Entity, class T_Container>
inline const NotNull<SharedPtr<T_Entity>>& MdibIterator<T_Entity, T_Container>::getEntityFromIteratorValue(const NotNull<SharedPtr<T_Entity>>& iteratorValue)
{
    return iteratorValue;
}

template<class T_Entity, class T_Container>
inline const NotNull<SharedPtr<T_Entity>>& MdibIterator<T_Entity, T_Container>::getEntityFromIteratorValue(const std::pair<BasicHandle<T_Entity>,
                                                                                                           NotNull<SharedPtr<T_Entity>>>& iteratorValue)
{
    return iteratorValue.second;
}

template<class T_Entity, class T_Container>
inline const NotNull<SharedPtr<T_Entity>>& MdibIterator<T_Entity, T_Container>::getEntityFromIteratorValue(const std::pair<const BasicHandle<T_Entity>,
                                                                                                           NotNull<SharedPtr<T_Entity>>>& iteratorValue)
{
    return iteratorValue.second;
}

template<class T_Entity, class T_Container>
inline const NotNull<SharedPtr<T_Entity>>& MdibIterator<T_Entity, T_Container>::operator*() const
{
    return getEntityFromIteratorValue(*m_it);
}

template<class T_Entity, class T_Container>
inline const NotNull<SharedPtr<T_Entity>>* MdibIterator<T_Entity, T_Container>::operator->() const
{
    return &(getEntityFromIteratorValue(*m_it));
}

template<class T_Entity, class T_Container>
inline MdibIterator<T_Entity, T_Container> MdibIterator<T_Entity, T_Container>::operator++(int)
{
    auto result = MdibIterator(*this);
    ++m_it;
    goToNextSatisfyingEntity();
    return result;
}

template<class T_Entity, class T_Container>
inline MdibIterator<T_Entity, T_Container>& MdibIterator<T_Entity, T_Container>::operator++()
{
    ++m_it;
    goToNextSatisfyingEntity();
    return (*this);
}

template<class T_Entity, class T_Container>
inline void MdibIterator<T_Entity, T_Container>::goToNextSatisfyingEntity()
{
    // if filter function is used then go (from current iterator position) to the next matching element
    if (m_filterFunction)
    {
        this->m_it = std::find_if(
            this->m_it,
            m_itEnd,
            [&](const typename T_Container::value_type& value)
            {
                return m_filterFunction(MdibIterator<T_Entity, T_Container>::getEntityFromIteratorValue(value));
            });
    }
}

/// @brief 'equal to' operator
template<class T_Entity1, class T_Container1>
inline bool operator==(const MdibIterator<T_Entity1, T_Container1> &lhs, const MdibIterator<T_Entity1, T_Container1> &rhs)
{
    return lhs.m_it == rhs.m_it;
}

/// @brief 'not equal to' operator
template<class T_Entity1, class T_Container1>
inline bool operator!=(const MdibIterator<T_Entity1, T_Container1> &lhs, const MdibIterator<T_Entity1, T_Container1> &rhs)
{
    return lhs.m_it != rhs.m_it;
}


}
}
}
