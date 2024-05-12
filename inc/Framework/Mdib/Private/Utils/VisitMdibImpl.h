#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/TypeTraits.h>
#include <type_traits>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
template<class Visitor>
class MdibEntityStateVisitor
{
    public:
        MdibEntityStateVisitor(Visitor& vis, const Mdib& mdib) : m_vis(vis), m_mdib(mdib) {}

        template<class T_Entity,
                typename std::enable_if<is_context_indicator<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            // Context indicator have no state
        }

        template<class T_Entity,
                typename std::enable_if<!is_context_indicator<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            for (const auto& entity : m_mdib.range<T_Entity>())
            {
                visitMembers(m_vis, *(entity->state()));
            }
        }

    private:
        Visitor& m_vis;
        const Mdib& m_mdib;
};

template<class Visitor>
class ChangeSetEntityStateVisitor
{
    public:
        ChangeSetEntityStateVisitor(Visitor& vis, const MdibChangeSet& changes) : m_vis(vis), m_changes(changes) {}

        template<class T_Entity,
                typename std::enable_if<is_context_indicator<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            // Context indicator have no state
        }

        template<class T_Entity,
                typename std::enable_if<!is_context_indicator<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            for (const auto& entity : m_changes.insertedEntities<T_Entity>())
            {
                visitMembers(m_vis, *(entity->state()));
            }
            for (const auto& entity : m_changes.updatedEntities<T_Entity>())
            {
                visitMembers(m_vis, *(entity->state()));
            }
        }

    private:
        Visitor& m_vis;
        const MdibChangeSet& m_changes;
};

template<class Visitor>
class MdibEntityDescriptorVisitor
{
    public:
        MdibEntityDescriptorVisitor(Visitor& vis, const Mdib& mdib) : m_vis(vis), m_mdib(mdib) {}

        template<class T_Entity,
                typename std::enable_if<is_multi_state<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            // multi state (context state) do not have a descriptor
        }

        template<class T_Entity,
                typename std::enable_if<!is_multi_state<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            for (const auto& entity : m_mdib.range<T_Entity>())
            {
                visitMembers(m_vis, *(entity->descriptor()));
            }
        }

    private:
        Visitor& m_vis;
        const Mdib& m_mdib;
};

template<class Visitor>
class ChangeSetEntityDescriptorVisitor
{
    public:
        ChangeSetEntityDescriptorVisitor(Visitor& vis, const MdibChangeSet& changes) : m_vis(vis), m_changes(changes) {}

        template<class T_Entity,
                typename std::enable_if<is_multi_state<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            // multi state (context state) do not have a descriptor
        }

        template<class T_Entity,
                typename std::enable_if<!is_multi_state<T_Entity>{}, bool>::type = true>
        void visitEntity()
        {
            for (const auto& entity : m_changes.insertedEntities<T_Entity>())
            {
                visitMembers(m_vis, *(entity->descriptor()));
            }
            for (const auto& entity : m_changes.updatedEntities<T_Entity>())
            {
                visitMembers(m_vis, *(entity->descriptor()));
            }
        }

    private:
        Visitor& m_vis;
        const MdibChangeSet& m_changes;
};

}
}
}
