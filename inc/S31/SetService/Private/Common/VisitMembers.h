#pragma once

#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/ProposedAlertState.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>

namespace S31::SetService
{
/**
 * @brief Visit all members.
 * @ingroup S31SetService
 */
template <class Visitor>
void visitMembers(Visitor& vis, const Argument& a)
{
    vis(a.argValue());
    vis(a.extensions());
}

/**
 * @brief Visit all members.
 * @ingroup S31SetService
 */
template <class Visitor>
void visitMembers(Visitor& vis, const ProposedAlertStates& a)
{
    vis(a.alertSystems());
    vis(a.alertSignals());
    vis(a.alertConditions());
    vis(a.limitAlertConditions());
}

template<class Visitor, class States>
class ProposedStateUpdatesVisitor
{
    public:
        ProposedStateUpdatesVisitor(Visitor& vis, const States& states) : m_vis(vis), m_states(states) {}

        template<class T_Entity>
        void visitEntity()
        {
            m_vis(m_states.template updates<T_Entity>());
        }

    private:
        Visitor& m_vis;
        const States& m_states;
};

template<class Visitor, class States>
class ProposedStateInsertionsVisitor
{
    public:
        ProposedStateInsertionsVisitor(Visitor& vis, const States& states) : m_vis(vis), m_states(states) {}

        template<class T_Entity>
        void visitEntity()
        {
            m_vis(m_states.template insertions<T_Entity>());
        }

    private:
        Visitor& m_vis;
        const States& m_states;
};

/**
 * @brief Visit all members.
 * @ingroup S31SetService
 */
template <class Visitor>
void visitMembers(Visitor& vis, const ProposedComponentStates& states)
{
    ProposedStateUpdatesVisitor<Visitor, ProposedComponentStates> entityVisitor{vis, states};
    DFL::Mdib::Entities<DFL_MDIB_ENTITY_COMPONENTS>::applyVisitor(entityVisitor);
}

/**
 * @brief Visit all members.
 * @ingroup S31SetService
 */
template <class Visitor>
void visitMembers(Visitor& vis, const ProposedContextStates& states)
{
    ProposedStateUpdatesVisitor<Visitor, ProposedContextStates> updatesVisitor{vis, states};
    DFL::Mdib::Entities<DFL_MDIB_ENTITY_CONTEXT_STATES>::applyVisitor(updatesVisitor);
    ProposedStateInsertionsVisitor<Visitor, ProposedContextStates> insertionsVisitor{vis, states};
    DFL::Mdib::Entities<DFL_MDIB_ENTITY_CONTEXT_STATES>::applyVisitor(insertionsVisitor);
}

/**
 * @brief Visit all members.
 * @ingroup S31SetService
 */
template <class Visitor>
void visitMembers(Visitor& vis, const ProposedMetricStates& states)
{
    ProposedStateUpdatesVisitor<Visitor, ProposedMetricStates> entityVisitor{vis, states};
    DFL::Mdib::Entities<DFL_MDIB_ENTITY_METRICS>::applyVisitor(entityVisitor);
}

}
