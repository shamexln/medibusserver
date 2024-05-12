#pragma once

#include <S31/SetService/Public/Common/ProposedStates.h>

#include <Framework/Mdib/Public/Model/Context/EnsembleContext.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>

#include <map>

namespace S31::Sdc::Impl
{

template<class T_Entity>
using MultiStateHandlePair = std::pair<DFL::Mdib::BasicHandle<typename T_Entity::ParentType>, DFL::Mdib::BasicHandle<T_Entity>>;

template<class T_Entity>
using EnhancedStateUpdatesMap = std::map<MultiStateHandlePair<T_Entity>, typename T_Entity::StateType>;

template<class... T_Entities>
using EnhancedProposedUpdates = SetService::ProposedStates<EnhancedStateUpdatesMap, T_Entities...>;

/**
 * @brief This class provides a complete container for set context operations.
 * @details It has the indicator handle as well as the state handle for a context state.
 * @ingroup S31SdcCommon
 */
class EnhancedProposedContextStates
{
    public:
        using EnhancedProposedContextUpdates = EnhancedProposedUpdates<DFL_MDIB_ENTITY_CONTEXT_STATES>;
        using ProposedContextInsertions = SetService::ProposedInsertions<DFL_MDIB_ENTITY_CONTEXT_INDICATORS>;

        /**
         * @brief Set the map for updates of type T_Entity to map.
         * @param map contains proposed context state updates for type T_Entity.
         */
        template<class T_Map>
        void updates(T_Map&& map)
        {
            m_updates.states<T_Map>(std::forward<T_Map>(map));
        }

        /**
         * @brief Set the map for insertions of type T_Entity to map.
         * @param map contains proposed context state insertions for type T_Entity.
         */
        template<class T_Map>
        void insertions(T_Map&& map)
        {
            m_insertions.states(std::forward<T_Map>(map));
        }

        /**
         * @return State updates for type T_Entity.
         */
        template<class T_Entity>
        const EnhancedStateUpdatesMap<T_Entity>& updates() const
        {
            return m_updates.states<T_Entity>();
        }

        /**
         * @return State insertions for type T_Entity.
         */
        template<class T_Entity>
        const SetService::StateInsertionsMap<typename T_Entity::ParentType>& insertions() const
        {
            return m_insertions.states<typename T_Entity::ParentType>();
        }

        /**
         * @brief Check if the container is empty.
         * @return True if the container contains neither updates nor insertions.
         */
        bool empty() const
        {
            return m_updates.empty() && m_insertions.empty();
        }

    private:
        EnhancedProposedContextUpdates m_updates;
        ProposedContextInsertions m_insertions;

};

}
