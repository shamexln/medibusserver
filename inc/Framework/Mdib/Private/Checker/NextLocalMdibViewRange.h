#pragma once

#include <Framework/Mdib/Private/Checker/NextLocalMdibViewIterator.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibChangeType.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Range type for a specific MDIB entity type for an MDIB with an applied
 * MDIB change set according to the change type.
 *
 * @details
 * Use this in case of getting all entities after applying an MDIB change set.
 * Typical use case is a check before applying a change set.
 *
 * @ingroup Mdib
 */
template<class T_Entity>
class NextLocalMdibViewRange
{
    public:
        using FilterFunction = typename NextLocalMdibViewIterator<T_Entity>::FilterFunction;

        NextLocalMdibViewRange(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode);
        NextLocalMdibViewRange(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode, FilterFunction filterFunction);

        NextLocalMdibViewIterator<T_Entity> begin() const;
        NextLocalMdibViewIterator<T_Entity> end() const;
        bool empty() const;
        NextLocalMdibViewRange<T_Entity> filter(FilterFunction filterFunction) const;

    private:
        const Mdib& m_mdib;
        const MdibChangeSet& m_changes;
        const MdibChangeType m_changeType;
        const IterationMode m_mode;
        const NextLocalMdibViewIterator<T_Entity> m_begin;
        const NextLocalMdibViewIterator<T_Entity> m_end;
};

template<class T_Entity>
NextLocalMdibViewRange<T_Entity>::NextLocalMdibViewRange(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode):
        m_mdib(mdib),
        m_changes(changes),
        m_changeType(changeType),
        m_mode(mode),
        m_begin(NextLocalMdibViewIterator<T_Entity>(m_mdib, m_changes, m_changeType, m_mode)),
        m_end(NextLocalMdibViewIterator<T_Entity>::end(m_mdib, m_changes, m_changeType, m_mode))
{
}

template<class T_Entity>
NextLocalMdibViewRange<T_Entity>::NextLocalMdibViewRange(const Mdib& mdib, const MdibChangeSet& changes, MdibChangeType changeType, IterationMode mode, FilterFunction filterFunction):
        m_mdib(mdib),
        m_changes(changes),
        m_changeType(changeType),
        m_mode(mode),
        m_begin(NextLocalMdibViewIterator<T_Entity>(m_mdib, m_changes, m_changeType, m_mode, filterFunction)),
        m_end(NextLocalMdibViewIterator<T_Entity>::end(m_mdib, m_changes, m_changeType, m_mode))
{
}

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity> NextLocalMdibViewRange<T_Entity>::begin() const
{
    return m_begin;
}

template<class T_Entity>
NextLocalMdibViewIterator<T_Entity> NextLocalMdibViewRange<T_Entity>::end() const
{
    return m_end;
}

template<class T_Entity>
bool NextLocalMdibViewRange<T_Entity>::empty() const
{
    return begin() == end();
}

template<class T_Entity>
NextLocalMdibViewRange<T_Entity> NextLocalMdibViewRange<T_Entity>::filter(FilterFunction filterFunction) const
{
    return NextLocalMdibViewRange<T_Entity>(m_mdib, m_changes, m_changeType, m_mode, filterFunction);
}

}
}
