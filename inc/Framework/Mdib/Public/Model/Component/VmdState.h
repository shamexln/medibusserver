#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Volatile part of a \ref Vmd.
 * @ingroup Mdib
 */
class VmdState: public AbstractDeviceComponentState
{
    DFL_MDIB_IMMUTABLE(VmdState)

    public:
        /**
         * @brief Defaults to \ref ComponentActivation::On "component activation on" with no further information
         * (all optionals are empty).
         */
        VmdState() = default;

        /**
         * @brief Constructor.
         */
        VmdState(ComponentActivation activationState,
                 const boost::optional<Chrono::Hours>& operatingHours,
                 const boost::optional<OperatingCycles>& operatingCycles,
                 const boost::optional<CalibrationInfo>& calibrationInfo,
                 const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                 const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                 const boost::optional<InstanceIdentifier>& operatingJurisdiction,
                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The current region information that is configured for the \ref Vmd
         * @details This element shall not be inserted if there is no \ref VmdDescriptor::approvedJurisdictions list present.
         * @return Current region information or \c boost::none if no approved jurisdictions list is present.
         */
        const boost::optional<InstanceIdentifier>& operatingJurisdiction() const;

    private:
        boost::optional<InstanceIdentifier> m_operatingJurisdiction;

};

inline VmdState::VmdState(ComponentActivation activationState,
                          const boost::optional<Chrono::Hours>& operatingHours,
                          const boost::optional<OperatingCycles>& operatingCycles,
                          const boost::optional<CalibrationInfo>& calibrationInfo,
                          const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                          const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                          const boost::optional<InstanceIdentifier>& operatingJurisdiction, // NOLINT(modernize-pass-by-value)
                          ExtensionTypes extensions) :
        AbstractDeviceComponentState(activationState, operatingHours, operatingCycles, calibrationInfo, nextCalibrationInfo, physicalConnector, std::move(extensions)),
        m_operatingJurisdiction(operatingJurisdiction)
{
}

inline const boost::optional<InstanceIdentifier>& VmdState::operatingJurisdiction() const
{
    return m_operatingJurisdiction;
}

/**
 * @brief Definition of shared pointer type \ref VmdStateSharedPtr for state \ref VmdState.
 * @ingroup Mdib
 */
using VmdStateSharedPtr = SharedPtr<VmdState>;


} /* namespace Mdib */
} /* namespace DFL */
