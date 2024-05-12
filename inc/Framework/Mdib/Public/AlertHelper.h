#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>

#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Helper functionality for handling alert related things in Mdib.
 *
 * see also: MdibQuery::alertSignals()
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP AlertHelper
{
    public:

        /**
         * @brief Modus for calling AlertHelper::setAlertSystemConditionPresenceLists()
         * @ingroup Mdib
         */
        enum class PresenceListsUpdateModus
        {
            OldMdibIsConsistent, //!< The old Mdib is considered consistent, so only delta changes are done
            ResetAllLists,       //!< Presence lists are build new from scratch
        };

        /**
         * @brief Set the presence lists in the affected AlertSystems.
         *
         * The provided change set may contain alert conditions with changed presence (@ref AlertConditionState::presence()).
         * The alert systems containing these alert conditions hold lists of present alert conditions
         * (@ref AlertSystemState::presentPhysiologicalAlarmConditions(), @ref AlertSystemState::presentTechnicalAlarmConditions()).
         * This function sets these lists so that they reflect the new Mdib.
         *
         * This function should be used beforehand of Mdib write operations to local Mdib:
         * @ref LocalMdibAccess::writeDescription(), @ref LocalMdibAccess::writeAlertStates()
         *
         * @param[in] mdib The old Mdib
         * @param[in, out] changeSet Changeset to be merged into Mdib.
         * @param[in] modus Should the old MDIB considered consistent, i.e. are it's alert system presence lists right or should all be build from scratch
         */
        ///@{
        static void setAlertSystemConditionPresenceLists(
                const Mdib& mdib,
                MdibChangeSet& changeSet,
                PresenceListsUpdateModus modus);
        static void setAlertSystemConditionPresenceLists(
                const DFL::NotNull<MdibSharedPtr>& mdib,
                MdibChangeSet& changeSet,
                PresenceListsUpdateModus modus);
        ///@}

};

inline void AlertHelper::setAlertSystemConditionPresenceLists(
        const DFL::NotNull<MdibSharedPtr>& mdib,
        MdibChangeSet& changeSet,
        PresenceListsUpdateModus modus)
{
    setAlertSystemConditionPresenceLists(*mdib, changeSet, modus);
}

}
}
