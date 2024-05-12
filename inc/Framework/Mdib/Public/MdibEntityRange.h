#pragma once

#include <Framework/Mdib/Private/MdibChildIterator.h>
#include <Framework/Mdib/Private/MdibIterator.h>
#include <Framework/Mdib/Private/MdibIteratorFromHandles.h>

#include <map>
#include <vector>

namespace DFL
{
namespace Mdib
{

class Mdib;

/**
 * @brief Range of MDIB entities given by the iterators begin() and end().
 *
 * With this a ranged based 'for' loop is possible.
 *
 * @see Mdib::range()
 * @ingroup Mdib
 */
template<class T_Entity, class T_Container = Impl::RandomEntityAccess<T_Entity>>
class MdibEntityRange
{
    public:
      /// Function type of filter function
      using FilterFunction = typename Impl::MdibIterator<T_Entity, T_Container>::FilterFunction;

      /// @brief Iterator type derived from underlying MDIB iterator type.
      using IteratorType = Impl::MdibIterator<T_Entity, T_Container>;

      /// @brief Container type derived from underlying MDIB iterator type.
      using ContainerType = typename IteratorType::ContainerType;

      /// @brief Constructor
      MdibEntityRange(IteratorType begin,
                      IteratorType end):
          m_begin(std::move(begin)),
          m_end(std::move(end))
      {
      }

      /// @brief begin of the range
      IteratorType begin() const;

      /// @brief end of the range
      IteratorType end() const;

      /// @brief returns true if the range is empty
      bool empty() const;

      /// @brief returns new range based on given filter
      MdibEntityRange<T_Entity, T_Container> filter(FilterFunction filterFunction) const;

    private:
      IteratorType m_begin;
      IteratorType m_end;
};

/**
 * @brief Create MDIB entity range from map.
 */
template<class T_Entity>
inline MdibEntityRange<T_Entity> toMdibEntityRange(const std::map<BasicHandle<T_Entity>, NotNull<SharedPtr<T_Entity>>>& map)
{
    return MdibEntityRange<T_Entity> (
        typename MdibEntityRange<T_Entity>::IteratorType(map.begin(), map.end()),
        typename MdibEntityRange<T_Entity>::IteratorType(map.end(), map.end())
    );
}

/**
 * @brief Create MDIB entity range from vector.
 */
template<class T_Entity>
inline MdibEntityRange<T_Entity, Impl::SequentialEntityAccess<T_Entity>> toMdibEntityRange(const std::vector<NotNull<SharedPtr<T_Entity>>>& vector)
{
    using Iterator = typename MdibEntityRange<T_Entity, Impl::SequentialEntityAccess<T_Entity>>::IteratorType;
    return MdibEntityRange<T_Entity, std::vector<NotNull<SharedPtr<T_Entity>>>> (
        Iterator(vector.begin(), vector.end()),
        Iterator(vector.end(), vector.end())
    );
}

/**
 * @brief %Range of MDIB entities given by a range of handles.
 *
 * @details This range is used, e.g., for alert signal iterators
 *
 * @ingroup Mdib
 */
template <class T_Entity, class T_Mdib>
class MdibEntityRangeFromHandles
{
    public:
      /// @brief Constructor
      MdibEntityRangeFromHandles(
              Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> begin,
              Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> end):
          m_begin(std::move(begin)),
          m_end(std::move(end))
      {
      }
      /// @brief begin of the range
      Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> begin() const;
      /// @brief end of the range
      Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> end() const;
      /// @brief returns true iif the range is empty
      bool empty() const;
    private:
      Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> m_begin;
      Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> m_end;
};

/**
 * @brief Range of MDIB entities revolved from a range of handles.
 * @ingroup Mdib
 */
template<class T_Entity, class T_EntityAccess = DFL::Mdib::Mdib>
class MdibEntityChildRange
{
    public:
        /// @brief Iterator type of the child range.
        using Iterator = Impl::MdibChildIterator<T_Entity, T_EntityAccess>;

        /// @brief Constructor with empty range
        MdibEntityChildRange() :
                m_empty(0),
                m_begin(Iterator(m_empty.end(), m_empty.end(), nullptr)),
                m_end(Iterator(m_empty.end(), m_empty.end(), nullptr))
        {
        }

        /// @brief Constructor with begin and end iterators.
        MdibEntityChildRange(Iterator begin,
                             Iterator end) :
                m_empty(),
                m_begin(std::move(begin)),
                m_end(std::move(end))
        {
        }

        /// @brief begin of the range
        Iterator begin() const;

        /// @brief end of the range
        Iterator end() const;

        /// @brief returns true if the range is empty
        bool empty() const;

    private:
        typename Iterator::ContainerType m_empty;
        Iterator m_begin;
        Iterator m_end;
};

template<class T_Entity, class T_Container>
typename MdibEntityRange<T_Entity, T_Container>::IteratorType MdibEntityRange<T_Entity, T_Container>::begin() const
{
    return m_begin;
}

template<class T_Entity, class T_Container>
typename MdibEntityRange<T_Entity, T_Container>::IteratorType MdibEntityRange<T_Entity, T_Container>::end() const
{
    return m_end;
}

template<class T_Entity, class T_Container>
bool MdibEntityRange<T_Entity, T_Container>::empty() const
{
    return m_begin == m_end;
}

template<class T_Entity, class T_Container>
inline MdibEntityRange<T_Entity, T_Container> MdibEntityRange<T_Entity, T_Container>::filter(FilterFunction filterFunction) const
{
  return
      MdibEntityRange<T_Entity>{
          Impl::MdibIterator<T_Entity, T_Container>{begin(), filterFunction},
          Impl::MdibIterator<T_Entity, T_Container>{end()}};
}

template<class T_Entity, class T_Mdib>
inline Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> MdibEntityRangeFromHandles<T_Entity, T_Mdib>::begin() const
{
    return m_begin;
}

template<class T_Entity, class T_Mdib>
inline Impl::MdibIteratorFromHandles<T_Entity, T_Mdib> MdibEntityRangeFromHandles<T_Entity, T_Mdib>::end() const
{
    return m_end;
}

template<class T_Entity, class T_Mdib>
inline bool MdibEntityRangeFromHandles<T_Entity, T_Mdib>::empty() const
{
    return m_begin == m_end;
}

template<class T_Entity, class T_EntityAccess>
inline typename MdibEntityChildRange<T_Entity, T_EntityAccess>::Iterator MdibEntityChildRange<T_Entity, T_EntityAccess>::begin() const
{
    return m_begin;
}

template<class T_Entity, class T_EntityAccess>
inline typename MdibEntityChildRange<T_Entity, T_EntityAccess>::Iterator MdibEntityChildRange<T_Entity, T_EntityAccess>::end() const
{
    return m_end;
}

template<class T_Entity, class T_EntityAccess>
inline bool MdibEntityChildRange<T_Entity, T_EntityAccess>::empty() const
{
    return m_begin == m_end;
}

}
}
