#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationInfo.h>
#include <Framework/Mdib/Public/Model/Component/PhysicalConnectorInfo.h>
#include <Framework/Mdib/Public/Model/ComponentActivation.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>

#include <boost/optional/optional.hpp>

#include <cstdint>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct OperatingCyclesTag;
}

/**
 * @brief Counter for operation cycles.
 * @ingroup Mdib
 */
using OperatingCycles = DFL::StrongTypedef<int32_t, Impl::OperatingCyclesTag, DFL::Skill::Incrementable, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief State of a component that is part of an \ref Mds.
 * @ingroup Mdib
 */
class AbstractDeviceComponentState: public Impl::HasExtensions
{
    DFL_MDIB_IMMUTABLE(AbstractDeviceComponentState)

    public:
        /**
         * @brief See \ref ComponentActivation.
         */
        ComponentActivation activationState() const;

        /**
         * @brief Optional amount of operating hours (e.g., an OR light).
         * @details There are no further semantics defined.
         * @return Integer number of operating hours or \c boost::none if undefined.
         */
        boost::optional<Chrono::Hours> operatingHours() const;

        /**
         * @brief Optional amount of operating cycles.
         * @details Example: the number of measurements taken within the component. There are no further semantics defined.
         * @return Integer number of operating cycles or \c boost::none if undefined.
         */
        boost::optional<OperatingCycles> operatingCycles() const;

        /**
         * @brief Provides information about the last calibration that was performed.
         * @return Calibration information (timestamp and documentation) or \c boost::none if undefined.
         */
        const boost::optional<CalibrationInfo>& calibrationInfo() const;

        /**
         * @brief Provides information about the next calibration that will be performed.
         * @return Calibration information (timestamp and documentation) or \c boost::none if undefined.
         */
        const boost::optional<CalibrationInfo>& nextCalibrationInfo() const;

        /**
         * @brief The physical connector number for this component.
         * @details See \ref PhysicalConnectorInfo.
         * @return Physical connector number or \c boost::none if undefined.
         */
        const boost::optional<PhysicalConnectorInfo>& physicalConnector() const;

    protected:
        /**
         * @brief Defaults to \ref ComponentActivation::On "component activation on" with no further information
         * (all optionals are empty).
         */
        AbstractDeviceComponentState() = default;

        /**
         * @brief Constructor.
         */
        AbstractDeviceComponentState(ComponentActivation activationState,
                                     boost::optional<Chrono::Hours> operatingHours,
                                     boost::optional<OperatingCycles> operatingCycles,
                                     boost::optional<CalibrationInfo> calibrationInfo,
                                     boost::optional<CalibrationInfo> nextCalibrationInfo,
                                     boost::optional<PhysicalConnectorInfo> physicalConnector,
                                     ExtensionTypes&& extensions);

        ~AbstractDeviceComponentState() = default;
    private:
        ComponentActivation m_activationState{ComponentActivation::On};
        boost::optional<Chrono::Hours> m_operatingHours{};
        boost::optional<OperatingCycles> m_operatingCycles{};
        boost::optional<CalibrationInfo> m_calibrationInfo{};
        boost::optional<CalibrationInfo> m_nextCalibrationInfo{};
        boost::optional<PhysicalConnectorInfo> m_physicalConnector{};
};

inline AbstractDeviceComponentState::AbstractDeviceComponentState(ComponentActivation activationState,
                                                                  boost::optional<Chrono::Hours> operatingHours,
                                                                  boost::optional<OperatingCycles> operatingCycles,
                                                                  boost::optional<CalibrationInfo> calibrationInfo,
                                                                  boost::optional<CalibrationInfo> nextCalibrationInfo,
                                                                  boost::optional<PhysicalConnectorInfo> physicalConnector,
                                                                  ExtensionTypes&& extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_activationState(activationState),
        m_operatingHours(std::move(operatingHours)),
        m_operatingCycles(std::move(operatingCycles)),
        m_calibrationInfo(std::move(calibrationInfo)),
        m_nextCalibrationInfo(std::move(nextCalibrationInfo)),
        m_physicalConnector(std::move(physicalConnector))
{
}

inline ComponentActivation AbstractDeviceComponentState::activationState() const
{
    return m_activationState;
}

inline boost::optional<Chrono::Hours> AbstractDeviceComponentState::operatingHours() const
{
    return m_operatingHours;
}

inline boost::optional<OperatingCycles> AbstractDeviceComponentState::operatingCycles() const
{
    return m_operatingCycles;
}

inline const boost::optional<CalibrationInfo>& AbstractDeviceComponentState::calibrationInfo() const
{
    return m_calibrationInfo;
}

inline const boost::optional<CalibrationInfo>& AbstractDeviceComponentState::nextCalibrationInfo() const
{
    return m_nextCalibrationInfo;
}

inline const boost::optional<PhysicalConnectorInfo>& AbstractDeviceComponentState::physicalConnector() const
{
    return m_physicalConnector;
}

} /* namespace Mdib */
} /* namespace DFL */
