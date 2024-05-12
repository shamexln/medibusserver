#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/MdsParentPlaceholder.h>
#include <Framework/Mdib/Private/PrivateCodingSemantics.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/TypeTraits.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Find if a \ref DFL::Mdib::ProductionSpecification identifies private coding semantics
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP PrivateCodingSemantics findPrivateCodingSemanticsImpl(const DFL::Mdib::ProductionSpecifications& productionSpecifications);

/**
 * @brief Follow the chain of parents of an entity to find private coding semantics
 *
 * @details Private coding semantics for Draeger are identified by a \ref DFL::Mdib::ProductionSpecification at the same level, or above
 * in the containment tree of an entity.  This function searches up the containment tree for a %ProductionSpecification with the
 * %MDC_ATTR_PRIV_CODING_SEMANTICS %specType, stopping at the first one it finds.
 *
 * @return Indicator that private semantics are found, and whether or not it matches a Draeger system
 * @ingroup Mdib
 */
///@{
/*
 * [PCSWORK-2987] Revert the line below to the following statement and remove this comment:
 * template<typename T_Mdib, typename T_Entity, typename std::enable_if<!DFL::Mdib::is_device_component_state<typename T_Entity::StateType>::value, int>::type = 0>
 */
template<typename T_Mdib, typename T_Entity, typename std::enable_if<!(DFL::Mdib::is_device_component_state<typename T_Entity::StateType>::value || std::is_same<DFL::Mdib::SystemContext, T_Entity>::value), int>::type = 0>
PrivateCodingSemantics findPrivateCodingSemantics(const T_Mdib& mdib, const T_Entity& entity)
{
    if (auto parent = mdib.entity(entity.parent()))
    {
        return findPrivateCodingSemantics(mdib, *parent);
    }
    return PrivateCodingSemantics::NotFound;
}

/*
 * [PCSWORK-2987] Revert the line below to the following statement and remove this comment:
 * template<typename T_Mdib, typename T_Entity, typename std::enable_if<DFL::Mdib::is_device_component_state<typename T_Entity::StateType>::value, int>::type = 0>
 */
template<typename T_Mdib, typename T_Entity, typename std::enable_if<(DFL::Mdib::is_device_component_state<typename T_Entity::StateType>::value || std::is_same<DFL::Mdib::SystemContext, T_Entity>::value), int>::type = 0>
PrivateCodingSemantics findPrivateCodingSemantics(const T_Mdib& mdib, const T_Entity& entity)
{
    auto privateCoding = findPrivateCodingSemanticsImpl(entity.descriptor()->productionSpecifications());

    if (privateCoding == PrivateCodingSemantics::NotFound)
    {
        if (auto parent = mdib.entity(entity.parent()))
        {
            return findPrivateCodingSemantics(mdib, *parent);
        }
    }

    return privateCoding;
}
///@}

}
}
}
