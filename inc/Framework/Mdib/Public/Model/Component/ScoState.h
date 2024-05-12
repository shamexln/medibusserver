#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/OperatingMode.h>
#include <Framework/Mdib/Public/Model/Operation/OperationGroup.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the volatile part of the \ref Sco.
 * @ingroup Mdib
 */
class ScoState : public AbstractDeviceComponentState
{
    DFL_MDIB_IMMUTABLE(ScoState)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref ScoState::invocationRequested() "Invocation requested" to empty sequence
         * - \ref ScoState::invocationRequired() "Invocation required" to empty sequence
         * - \ref ScoState::operationGroups() "Operation groups" to empty sequence
         */
        ScoState();

        /**
         * @brief Full constructor.
         */
        ScoState(ComponentActivation activationState,
                 const boost::optional<Chrono::Hours>& operatingHours,
                 const boost::optional<OperatingCycles>& operatingCycles,
                 const boost::optional<CalibrationInfo>& calibrationInfo,
                 const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                 const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                 Handles invocationRequested,
                 Handles invocationRequired,
                 const OperationGroups& operationGroups,
                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Prioritized list of operations that are requested
         * to be invoked by a Service Consumer.
         */
        const Handles& invocationRequested() const;

        /**
         * @brief Prioritized list of operations that are required
         * to be invoked by a Service Consumer.
         */
        const Handles& invocationRequired() const;

        /**
         * @brief Defines groups of operations in order to allow clinical
         * grouping and prioritization of operations.
         */
        const OperationGroups& operationGroups() const;

    private:
        Handles m_invocationRequested;
        Handles m_invocationRequired;
        OperationGroups m_operationGroups;
};

inline ScoState::ScoState():
         m_invocationRequested(Handles()),
         m_invocationRequired(Handles()),
         m_operationGroups(OperationGroups())
{
}

inline ScoState::ScoState(ComponentActivation activationState,
                          const boost::optional<Chrono::Hours>& operatingHours,
                          const boost::optional<OperatingCycles>& operatingCycles,
                          const boost::optional<CalibrationInfo>& calibrationInfo,
                          const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                          const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                          Handles invocationRequested,
                          Handles invocationRequired,
                          const OperationGroups& operationGroups, // NOLINT(modernize-pass-by-value)
                          ExtensionTypes extensions) :
        AbstractDeviceComponentState(activationState, operatingHours, operatingCycles, calibrationInfo, nextCalibrationInfo, physicalConnector, std::move(extensions)),
        m_invocationRequested(std::move(invocationRequested)),
        m_invocationRequired(std::move(invocationRequired)),
        m_operationGroups(operationGroups)
{
}

inline const Handles& ScoState::invocationRequested() const
{
    return m_invocationRequested;
}

inline const Handles& ScoState::invocationRequired() const
{
    return m_invocationRequired;
}

inline const OperationGroups& ScoState::operationGroups() const
{
    return m_operationGroups;
}

/**
 * @brief Definition of shared pointer type \ref ScoStateSharedPtr for state \ref ScoState.
 */
using ScoStateSharedPtr = SharedPtr<ScoState>;

} /* namespace Mdib */
} /* namespace DFL */
