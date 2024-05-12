#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the volatile part of a \ref Channel.
 * @ingroup Mdib
 */
class ChannelState : public AbstractDeviceComponentState
{
    DFL_MDIB_IMMUTABLE(ChannelState)

    public:
        /**
         * @brief Defaults to \ref ComponentActivation::On "component activation on" with no further information
         * (all optionals are empty).
         */
        ChannelState() = default;

        /**
         * @brief Constructor.
         */
        ChannelState(ComponentActivation activationState,
                     const boost::optional<Chrono::Hours>& operatingHours,
                     const boost::optional<OperatingCycles>& operatingCycles,
                     const boost::optional<CalibrationInfo>& calibrationInfo,
                     const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                     const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                     ExtensionTypes extensions = ExtensionTypes{ });
};

inline ChannelState::ChannelState(ComponentActivation activationState,
                                  const boost::optional<Chrono::Hours>& operatingHours,
                                  const boost::optional<OperatingCycles>& operatingCycles,
                                  const boost::optional<CalibrationInfo>& calibrationInfo,
                                  const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                                  const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                  ExtensionTypes extensions):
        AbstractDeviceComponentState(activationState, operatingHours, operatingCycles, calibrationInfo, nextCalibrationInfo, physicalConnector, std::move(extensions))
{
}

/**
 * @brief Definition of shared pointer type \ref ChannelStateSharedPtr for state \ref ChannelState.
 * @ingroup Mdib
 */
using ChannelStateSharedPtr = SharedPtr<ChannelState>;


}
}
