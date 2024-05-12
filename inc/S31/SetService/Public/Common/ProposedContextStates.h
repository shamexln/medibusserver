#pragma once

#include <S31/S31CoreExImp.h>

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

namespace S31::SetService
{

/**
 * @brief Alias for the new states of the type @ref DFL::Mdib::PatientContext.
 * @details Takes the @ref DFL::Mdib::PatientContextIndicatorHandle "Patient Context Indicator Handle" as key and
 *          @ref DFL::Mdib::PatientContextState "Patient Context States" as value.
 * @ingroup S31SetService
 */
using PatientContextInsertions = StateInsertionsMap<DFL::Mdib::PatientContextIndicator>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::PatientContext.
 * @details Take @ref DFL::Mdib::PatientContextHandle "Patient Context State Handles" as key and
 *          @ref DFL::Mdib::PatientContextState "Patient Context States" as value.
 * @ingroup S31SetService
 */
using PatientContextUpdates = StateUpdatesMap<DFL::Mdib::PatientContext>;

/**
 * @brief Alias for the new states of the type \ref DFL::Mdib::LocationContext.
 * @details Takes the @ref DFL::Mdib::LocationContextIndicatorHandle "Location Context Indicator Handle" as key and
 *          @ref DFL::Mdib::LocationContextState "Location Context States" as value.
 * @ingroup S31SetService
 */
using LocationContextInsertions = StateInsertionsMap<DFL::Mdib::LocationContextIndicator>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::LocationContext.
 * @details Take @ref DFL::Mdib::LocationContextHandle "Location Context State Handles" as key and
 *          @ref DFL::Mdib::LocationContextState "Location Context States" as value.
 * @ingroup S31SetService
 */
using LocationContextUpdates = StateUpdatesMap<DFL::Mdib::LocationContext>;

/**
 * @brief Alias for the new states of the type \ref DFL::Mdib::EnsembleContext.
 * @details Takes the @ref DFL::Mdib::EnsembleContextIndicatorHandle "Ensemble Context Indicator Handle" as key and
 *          @ref DFL::Mdib::EnsembleContextState "Ensemble Context States" as value.
 * @ingroup S31SetService
 */
using EnsembleContextInsertions = StateInsertionsMap<DFL::Mdib::EnsembleContextIndicator>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::EnsembleContext.
 * @details Take @ref DFL::Mdib::EnsembleContextHandle "Ensemble Context State Handles" as key and
 *          @ref DFL::Mdib::EnsembleContextState "Ensemble Context States" as value.
 * @ingroup S31SetService
 */
using EnsembleContextUpdates = StateUpdatesMap<DFL::Mdib::EnsembleContext>;

/**
 * @brief This class provides a container for set context operations.
 * @details @ref DFL::Mdib::SetContextStateOperation "Set context state operations" allow setting @ref DFL::Mdib::PatientContextState "Patient",
 *          @ref DFL::Mdib::LocationContextState "Location" and @ref DFL::Mdib::EnsembleContextState "Ensemble" context states at the same time.
 *          This container can hold both updates to existing context states or new context states that shall be inserted under a given context indicator.
 * @ingroup S31SetService
 */
class S31_CORE_EXPIMP ProposedContextStates
{
    public:
        using size_type = std::size_t;
        using ProposedContextUpdates = ProposedUpdates<DFL_MDIB_ENTITY_CONTEXT_STATES>;
        using ProposedContextInsertions = ProposedInsertions<DFL_MDIB_ENTITY_CONTEXT_INDICATORS>;

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
            m_insertions.states<T_Map>(std::forward<T_Map>(map));
        }

        /**
         * @return State updates for type T_Entity.
         */
        template<class T_Entity>
        const StateUpdatesMap<T_Entity>& updates() const
        {
            return m_updates.states<T_Entity>();
        }

        /**
         * @return State insertions for type T_Entity.
         */
        template<class T_Entity>
        const StateInsertionsMap<typename T_Entity::ParentType>& insertions() const
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

        size_type size() const
        {
            return m_updates.size() + m_insertions.size();
        }
    private:
        ProposedContextUpdates m_updates;
        ProposedContextInsertions m_insertions;

};

}
