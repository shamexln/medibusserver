#pragma once

#include <Framework/Mdib/Private/MdibIteratorHelper.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>
#include <Framework/Mdib/Public/MdibSmartPtrTypes.h>

#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Strategy for iteration through the NextMdibView
 * @details AllEntities queries the existing mdib as well as updates/inserts, Modified only iteration only updates/inserts
 */
enum class IterationMode
{
    AllEntities,
    ModifiedOnly
};

template<class T_Entity>
class NextLocalMdibViewIterator;

template<class T_Entity>
bool operator==(const NextLocalMdibViewIterator<T_Entity>& lhs, const NextLocalMdibViewIterator<T_Entity>& rhs);

/**
 * @brief Iterator type to iterate over an MDIB and a change set for given
 * MDIB change type.
 *
 * @details The instances are typically created by the \ref NextLocalMdibViewRange
 * type that provides the begin and end iterator.
 *
 * @ingroup Mdib
 */
template<class T_Entity>
class NextLocalMdibViewIterator: public Impl::MdibIteratorTraits<NotNull<SharedPtr<T_Entity>>>
{
    public:
        /// @brief Function type that is used for filtering
        using FilterFunction = std::function<bool(const NotNull<SharedPtr<T_Entity>>&)>;

        /**
         * @brief Constructor used for the beginning.
         */
        NextLocalMdibViewIterator(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode);

        /**
         * @brief Constructor for iterating with a filter
         */
        NextLocalMdibViewIterator(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode, FilterFunction filterFunction);

        /**
         * @brief Factory for end() iterator.
         *
         * @details
         * The only internal end() iterator that is always valid is from the
         * MDIB. Depending on the MDIB change type insert and update ranges are
         * not allowed to be accessed.
         */
        static NextLocalMdibViewIterator end(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode);

        /// @brief post+increment operator
        NextLocalMdibViewIterator<T_Entity> operator++(int) &;
        /// @brief pre-increment operator
        NextLocalMdibViewIterator<T_Entity>& operator++();

        /// @brief Dereference operator
        const NotNull<SharedPtr<T_Entity>>& operator*() const;
        /// @brief member of pointer operator
        const NotNull<SharedPtr<T_Entity>>* operator->() const;

        friend bool operator== <>(const NextLocalMdibViewIterator<T_Entity> &lhs, const NextLocalMdibViewIterator<T_Entity> &rhs);

    private:
        void initializeIterators();

        // Loops through the entries until a valid entry (according to filter) is found
        void checkCurrentWithFilter();

        void goToNextEntry();
        void setCurrent();

        NotNull<const Mdib*> m_mdib;
        NotNull<const MdibChangeSet*> m_changes;
        MdibChangeType m_changeType;
        IterationMode m_iterationMode;
        typename MdibEntityRange<T_Entity>::IteratorType m_mdibBegin;
        typename MdibEntityRange<T_Entity>::IteratorType m_mdibEnd;
        typename MdibEntityRange<T_Entity>::IteratorType m_insertedBegin;
        typename MdibEntityRange<T_Entity>::IteratorType m_insertedEnd;
        typename MdibEntityRange<T_Entity>::IteratorType m_updatedBegin;
        typename MdibEntityRange<T_Entity>::IteratorType m_updatedEnd;
        FilterFunction m_filterFunction;

        /**
         * @brief Instance the iterator is pointing to.
         * @details
         * The dereference and pointer member require to have an lvalue to
         * return. Thus it is not possible to have only a shared_ptr that might
         * be empty. For invalid iterators (end) no entity exists. To represent
         * that value a boost optional is used.
         */
        boost::optional<NotNull<SharedPtr<T_Entity>>> m_currentEntity;
};

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity>::NextLocalMdibViewIterator(const Mdib& mdib,
                                                     const MdibChangeSet& changes,
                                                     MdibChangeType changeType,
                                                     IterationMode mode):
        m_mdib(asNotNull(&mdib)),
        m_changes(asNotNull(&changes)),
        m_changeType(changeType),
        m_iterationMode(mode),
        m_mdibBegin(mdib.range<T_Entity>().begin()),
        m_mdibEnd(mdib.range<T_Entity>().end()),
        m_insertedBegin(changes.template insertedEntities<T_Entity>().begin()),
        m_insertedEnd(changes.template insertedEntities<T_Entity>().end()),
        m_updatedBegin(changes.template updatedEntities<T_Entity>().begin()),
        m_updatedEnd((changes.template updatedEntities<T_Entity>().end())),
        m_filterFunction(),
        m_currentEntity()
{
    initializeIterators();
}

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity>::NextLocalMdibViewIterator(const Mdib& mdib,
                                                     const MdibChangeSet& changes,
                                                     MdibChangeType changeType,
                                                     IterationMode mode,
                                                     FilterFunction filterFunction):
         m_mdib(asNotNull(&mdib)),
         m_changes(asNotNull(&changes)),
         m_changeType(changeType),
         m_iterationMode(mode),
         m_mdibBegin(mdib.range<T_Entity>().begin()),
         m_mdibEnd(mdib.range<T_Entity>().end()),
         m_insertedBegin(changes.template insertedEntities<T_Entity>().begin()),
         m_insertedEnd(changes.template insertedEntities<T_Entity>().end()),
         m_updatedBegin(changes.template updatedEntities<T_Entity>().begin()),
         m_updatedEnd((changes.template updatedEntities<T_Entity>().end())),
         m_filterFunction(std::move(filterFunction)),
         m_currentEntity()
{
    initializeIterators();
    checkCurrentWithFilter();
}

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity> NextLocalMdibViewIterator<T_Entity>::end(
        const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode)
{
    auto end = NextLocalMdibViewIterator<T_Entity>(mdib, changes, changeType, mode);

    // End of MDIB and inserted entites is defined as end of iteration.
    end.m_mdibBegin = mdib.range<T_Entity>().end();
    end.m_insertedBegin = changes.insertedEntities<T_Entity>().end();
    end.m_updatedBegin = changes.updatedEntities<T_Entity>().end();
    return end;
}

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity>& NextLocalMdibViewIterator<T_Entity>::operator++()
{
    // pre-increment
    goToNextEntry();
    checkCurrentWithFilter();
    return *this;
}

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity> NextLocalMdibViewIterator<T_Entity>::operator++(int) &
{
    // post-increment
    auto tmp = *this;
    goToNextEntry();
    checkCurrentWithFilter();
    return tmp;
}

template<class T_Entity>
bool operator==(const NextLocalMdibViewIterator<T_Entity>& lhs, const NextLocalMdibViewIterator<T_Entity>& rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }

    return lhs.m_mdibBegin == rhs.m_mdibBegin
        && lhs.m_mdibEnd == rhs.m_mdibEnd
        && lhs.m_insertedBegin == rhs.m_insertedBegin
        && lhs.m_insertedEnd == rhs.m_insertedEnd
        && lhs.m_updatedBegin == rhs.m_updatedBegin
        && lhs.m_updatedEnd == rhs.m_updatedEnd
        && lhs.m_changeType == rhs.m_changeType
        && lhs.m_iterationMode == rhs.m_iterationMode;
}

template<class T_Entity>
const NotNull<SharedPtr<T_Entity>>& NextLocalMdibViewIterator<T_Entity>::operator*() const
{
    if (!m_currentEntity)
    {
        throw std::runtime_error("Empty iterator is not allowed to be dereferenced");
    }
    return *m_currentEntity;
}

template<class T_Entity>
const NotNull<SharedPtr<T_Entity>>* NextLocalMdibViewIterator<T_Entity>::operator->() const
{
    if (!m_currentEntity)
    {
        throw std::runtime_error("Empty iterator is not allowed to be dereferenced");
    }
    return &(*m_currentEntity);
}

template<class T_Entity>
bool operator!=(const NextLocalMdibViewIterator<T_Entity>& lhs, const NextLocalMdibViewIterator<T_Entity>& rhs)
{
    return !(lhs == rhs);
}

}
}
