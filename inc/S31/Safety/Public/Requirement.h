#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>
#include <S31/Safety/Public/MdibXPath.h>
#include <S31/Safety/Public/MessageXPath.h>

#include <Framework/Mdib/Public/Model/Handle.h>

#include <boost/optional/optional.hpp>

#include <map>
#include <utility>

namespace S31::Safety
{

/**
 * @brief Map to represent \ref ContextId "safety context IDs" that correspond to specific \ref MdibXPath expressions.
 * @ingroup S31Safety
 */
using ContextDefinitions = std::map<ContextId, MdibXPath>;

/**
 * @brief Map to represent \ref ContextId "safety context IDs" that correspond to specific \ref MdibXPath expressions.
 * @ingroup S31Safety
 */
using DualChannelDefinitions = std::map<DualChannelId, MessageXPath>;

/**
 * @brief Maintains safety requirement definitions for an individual MDIB entity.
 * @details An device provides the requirements, while the client has to fulfill the requirements.
 * @ingroup S31Safety
 */
class Requirement
{
    public:
        /**
         * @brief Default constructor with empty safety and dual channel definitions.
         */
        Requirement();

        /**
         * @brief Constructor that populates safety and dual channel definitions.
         */
        Requirement(ContextDefinitions safetyContextDefinition, DualChannelDefinitions dualChannelDefinition);

        /**
         * @brief Constructor that populates safety definitions, but leaves dual channel definitions empty.
         */
        explicit Requirement(ContextDefinitions safetyContextDefinition);

        /**
         * @brief Constructor that populates dual channel definitions, but leaves safety definitions empty.
         */
        explicit Requirement(DualChannelDefinitions dualChannelDefinition);

        /**
         * @brief Returns the context definitions enclosed by the requirement.
         */
        const ContextDefinitions& contextDefinitions() const;

        /**
         * @brief Returns the dual channel definitions enclosed by the requirement.
         */
        const DualChannelDefinitions& dualChannelDefinitions() const;

    private:
        ContextDefinitions m_safetyContextDefinitions;
        DualChannelDefinitions m_dualChannelDefinition;
};

inline Requirement::Requirement() :
        m_safetyContextDefinitions(),
        m_dualChannelDefinition()
{
}

inline Requirement::Requirement(ContextDefinitions safetyContextDefinition, DualChannelDefinitions dualChannelDefinition) :
        m_safetyContextDefinitions(std::move(safetyContextDefinition)),
        m_dualChannelDefinition(std::move(dualChannelDefinition))
{
}

inline Requirement::Requirement(ContextDefinitions safetyContextDefinition) :
        m_safetyContextDefinitions(std::move(safetyContextDefinition)),
        m_dualChannelDefinition()
{
}

inline Requirement::Requirement(DualChannelDefinitions dualChannelDefinition) :
        m_safetyContextDefinitions(),
        m_dualChannelDefinition(std::move(dualChannelDefinition))
{
}

inline const ContextDefinitions& Requirement::contextDefinitions() const
{
    return m_safetyContextDefinitions;
}

inline const DualChannelDefinitions& Requirement::dualChannelDefinitions() const
{
    return m_dualChannelDefinition;
}

}
