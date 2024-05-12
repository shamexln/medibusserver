#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/SetService/Public/Common/ProposedStates.h>

#include <Framework/Mdib/Public/Model/Component/Battery.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/Clock.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>

#include <map>

namespace S31::SetService
{

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::Mds.
 * @details Takes \ref DFL::Mdib::MdsHandle "Mds Handles" as key and \ref DFL::Mdib::MdsState "Mds States" as value.
 * @ingroup S31SetService
 */
using MdsUpdates = StateUpdatesMap<DFL::Mdib::Mds>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::Vmd.
 * @details Takes \ref DFL::Mdib::VmdHandle "Vmd Handles" as key and \ref DFL::Mdib::VmdState "Vmd States" as value.
 * @ingroup S31SetService
 */
using VmdUpdates = StateUpdatesMap<DFL::Mdib::Vmd>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::MdsSco.
 * @details Takes \ref DFL::Mdib::MdsScoHandle "Mds Sco Handles" as key and \ref DFL::Mdib::ScoState "Mds Sco States" as value.
 * @ingroup S31SetService
 */
using MdsScoUpdates = StateUpdatesMap<DFL::Mdib::MdsSco>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::VmdSco.
 * @details Takes \ref DFL::Mdib::VmdScoHandle "Vmd Sco Handles" as key and \ref DFL::Mdib::ScoState "Vmd Sco States" as value.
 * @ingroup S31SetService
 */
using VmdScoUpdates = StateUpdatesMap<DFL::Mdib::VmdSco>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::SystemContext.
 * @details Takes \ref DFL::Mdib::SystemContextHandle "System Context Handles" as key and \ref DFL::Mdib::SystemContextState "System Context States" as value.
 * @ingroup S31SetService
 */
using SystemContextUpdates = StateUpdatesMap<DFL::Mdib::SystemContext>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::Battery.
 * @details Takes \ref DFL::Mdib::BatteryHandle "Battery Handles" as key and \ref DFL::Mdib::BatteryState "Battery States" as value.
 * @ingroup S31SetService
 */
using BatteryUpdates = StateUpdatesMap<DFL::Mdib::Battery>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::Clock.
 * @details Takes \ref DFL::Mdib::ClockHandle "Clock Handles" as key and \ref DFL::Mdib::ClockState "Clock States" as value.
 * @ingroup S31SetService
 */
using ClockUpdates = StateUpdatesMap<DFL::Mdib::Clock>;

/**
 * @brief Alias for the updated states of the type \ref DFL::Mdib::Channel.
 * @details Takes \ref DFL::Mdib::ChannelHandle "Channel Handles" as key and \ref DFL::Mdib::ChannelState "Channel States" as value.
 * @ingroup S31SetService
 */
using ChannelUpdates = StateUpdatesMap<DFL::Mdib::Channel>;

/**
 * @brief This class provides a container for set component state operations.
 * @details @ref DFL::Mdib::SetComponentStateOperation "Set component state operations" allow setting @ref DFL::Mdib::MdsState "Mds",
 *          @ref DFL::Mdib::VmdState "Vmd", @ref DFL::Mdib::ScoState "Mds Sco", @ref DFL::Mdib::ScoState "Vmd Sco",
 *          @ref DFL::Mdib::SystemContextState "System Context", @ref DFL::Mdib::BatteryState "Battery", @ref DFL::Mdib::ClockState "Clock"
 *           and @ref DFL::Mdib::ChannelState "Channel" states at the same time.
 * @ingroup S31SetService
 */
class S31_CORE_EXPIMP ProposedComponentStates
{
    public:
        using ProposedComponentUpdates = ProposedUpdates<DFL_MDIB_ENTITY_COMPONENTS>;

        /**
         * @brief Set the map for updates of type T_Entity to map.
         * @param map holds proposed component state updates for type T_Entity.
         */
        template<class T_Map>
        void updates(T_Map&& map)
        {
            m_updates.states<T_Map>(std::forward<T_Map>(map));
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
         * @brief Check if the container is empty.
         * @return True if the container contains no state updates.
         */
        bool empty() const
        {
            return m_updates.empty();
        }

    private:
        ProposedComponentUpdates m_updates;
};

}
