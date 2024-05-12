#pragma once

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Generic range implementation with support of getting begin and end as well as testing on emptiness.
 * @ingroup Mdib
 */
template<class T_Container>
class GenericRange
{
    public:
        /// @brief Container type that is used to access iterators.
        using ContainerType = T_Container;

        /// @brief Iterator type derived from underlying container type.
        using IteratorType = typename ContainerType::const_iterator;

        /// @brief Constructor.
        GenericRange(const IteratorType& begin, const IteratorType& end);

        /// @brief Begin of the range.
        IteratorType begin() const;

        /// @brief End of the range.
        IteratorType end() const;

        /// @brief Returns \c true if the range is empty, otherwise \c false.
        bool empty() const;

    private:
        IteratorType m_begin;
        IteratorType m_end;
};

template<class T_Container>
inline GenericRange<T_Container>::GenericRange(const IteratorType& begin, const IteratorType& end) :
        m_begin(begin),
        m_end(end)
{
}

template<class T_Container>
inline typename GenericRange<T_Container>::IteratorType GenericRange<T_Container>::begin() const
{
    return m_begin;
}

template<class T_Container>
inline typename GenericRange<T_Container>::IteratorType GenericRange<T_Container>::end() const
{
    return m_end;
}

template<class T_Container>
inline bool GenericRange<T_Container>::empty() const
{
    return m_begin == m_end;
}

}
}
}
