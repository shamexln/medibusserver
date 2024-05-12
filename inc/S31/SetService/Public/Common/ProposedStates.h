#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <map>

namespace S31::SetService
{
/**
 * @brief Alias for map used for set state operations where existing states are updated.
 * @ingroup S31SetService
 */
template<class T_Entity>
using StateUpdatesMap = std::map<DFL::Mdib::BasicHandle<T_Entity>, typename T_Entity::StateType>;

/**
 * @brief Alias for map used for set state operations where existing states are inserted.
 * @details This is only relevant for set context state operations.
 * @ingroup S31SetService
 */
/// This does not provide the type safety that you would expect since Handles can be implicitly converted.
/// @todo JIRA S31-2600
template<class T_ContextIndicator>
using StateInsertionsMap = std::multimap<DFL::Mdib::BasicHandle<T_ContextIndicator>, typename T_ContextIndicator::StateType>;

/**
 * @brief Container to hold states of certain type.
 * @ingroup S31SetService
 */
template<class T_Map>
class ProposedStatesContainer
{
    protected:
        T_Map m_statesMap;
};

/**
 * @brief Helper class to recursively include containers for all types.
 * @ingroup S31SetService
 */
///@{
template<template<class TM> class T_Map, class T_Entity, class... T_Entities> class ProposedStatesExpansion;

template<template<class TM> class T_Map, class T_Entity>
class ProposedStatesExpansion<T_Map, T_Entity> : /** @cond **/ protected ProposedStatesContainer<T_Map<T_Entity>>
{
};

template<template<class TM> class T_Map, class T_Entity, class... T_Entities>
class ProposedStatesExpansion : public ProposedStatesExpansion<T_Map, T_Entity>, public ProposedStatesExpansion<T_Map, T_Entities...> /** @endcond **/
{
};
///@}

/**
 * @brief This class holds containers for all types specified in the template parameter pack T_Entities...
 *        The kind of container used depends on the Map type specified via T_Map.
 * @ingroup S31SetService
*/
template<template<class TM> class T_Map, class... T_Entities>
class ProposedStates: public ProposedStatesExpansion<T_Map, T_Entities...>
{
    public:
        using size_type = std::size_t;

        /**
         * @brief Set the states map of container for type T_Entity to map.
         * @details map is of forwarding reference type, i.e. it can take const/volatile lvalues/rvalues
         */
        template<class T_MapType>
        void states(T_MapType&& map)
        {
            ProposedStatesContainer<typename std::decay<T_MapType>::type>::m_statesMap = std::forward<T_MapType>(map);
        }

        /**
         * @brief Get the states map for type T_Entity.
         */
        template<class T_Entity>
        const T_Map<T_Entity>& states() const
        {
            return ProposedStatesContainer<T_Map<T_Entity>>::m_statesMap;
        }

        /**
         * @brief Check if all containers are empty.
         * @return True if all containers are empty.
         */
        bool empty() const
        {
            return emptyContainer<T_Entities...>();
        }

        size_type size() const
        {
            return sizeContainer<T_Entities...>();
        }

    private:
        template<class... Args>
        bool emptyContainer(typename std::enable_if<sizeof...(Args) == 0>::type* = nullptr) const
        {
            return true;
        }

        template<class T_Entity, class ...Args>
        bool emptyContainer() const
        {
            return states<T_Entity>().empty() && emptyContainer<Args...>();
        }

        template<class... Args>
        size_type sizeContainer(typename std::enable_if<sizeof...(Args) == 0>::type* = nullptr) const
        {
            return 0;
        }

        template<class T_Entity, class ...Args>
        size_type sizeContainer() const
        {
            return states<T_Entity>().size() + emptyContainer<Args...>();
        }

};

/**
 * @brief Alias for ProposedStates for StateUpdates.
 * @ingroup S31SetService
 */
template<class... T_Entities>
using ProposedUpdates = ProposedStates<StateUpdatesMap, T_Entities...>;

/**
 * @brief Alias for ProposedStates for StateInsertions.
 * @ingroup S31SetService
 */
template<class... T_Entities>
using ProposedInsertions = ProposedStates<StateInsertionsMap, T_Entities...>;

}
