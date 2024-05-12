#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>
#include <Framework/Mdib/Public/Model/Component/ChargeStatus.h>
#include <Framework/Mdib/Public/Model/Measurement.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>

#include <boost/optional/optional.hpp>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct ChargeCyclesTag;
}

/**
 * @brief Number of charge/discharge cycles.
 * @ingroup Mdib
 */
using ChargeCycles = DFL::StrongTypedef<uint32_t, Impl::ChargeCyclesTag, DFL::Skill::Incrementable, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief Volatile part of battery information.
 * @details The current power source is designated by \ref ComponentActivation "ComponentActivation":
 *
 * - If \ref BatteryState::activationState equals \ref ComponentActivation::On, the device is running on battery
 * - If \ref BatteryState::activationState equals \ref ComponentActivation::Off, the device is in mains operation and currently not able to be run on battery
 * - If \ref BatteryState::activationState equals \ref ComponentActivation::StandBy, the device is in mains operation and can be switched to run on battery
 * - If \ref BatteryState::activationState equals \ref ComponentActivation::Failure, the battery has a malfunction. Detailed error information should be communicated by using an alert system.
 *
 * \note Enumerations \ref ComponentActivation::Shutdown and \ref ComponentActivation::NotReady are undefined for %BatteryState.
 * @ingroup Mdib
 */
class BatteryState : public AbstractDeviceComponentState
{
    public:
        /**
         * @brief Defaults to \ref ComponentActivation::On "component activation on" with no further information
         * (all optionals are empty).
         */
        BatteryState() = default;

        /**
         * @brief Constructor.
         */
        BatteryState(ComponentActivation activationState,
                     const boost::optional<Chrono::Hours>& operatingHours,
                     const boost::optional<OperatingCycles>& operatingCycles,
                     const boost::optional<CalibrationInfo>& calibrationInfo,
                     const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                     const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                     const boost::optional<ChargeStatus>& chargeStatus,
                     boost::optional<ChargeCycles> chargeCycles,
                     const boost::optional<Measurement>& capacityRemaining,
                     const boost::optional<Measurement>& voltage,
                     const boost::optional<Measurement>& current,
                     const boost::optional<Measurement>& temperature,
                     const boost::optional<Measurement>& remainingBatteryTime,
                     ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Current charge status of a battery.
         * @return Current charge of battery or \c boost::none if not specified.
         */
        boost::optional<ChargeStatus> chargeStatus() const;

        /**
         * @brief Number of charge/discharge cycles of a battery
         * @return Number of charge/discharge cycles or \c boost::none if not specified.
         */
        boost::optional<ChargeCycles> chargeCycles() const;

        /**
         * @brief Remaining capacity of a battery at current load
         * @return Remaining capacity or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& capacityRemaining() const;

        /**
         * @brief Voltage between the terminals of a cell or battery when being discharged.
         * @details See also IEC 60050-482 International Electrotechnical Vocabulary, 482-03-28.
         * @return Voltage of battery when being discharged or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& voltage() const;

        /**
         * @brief Electric current delivered by a battery during its discharge. Negative if battery is charging.
         * @details See also IEC 60050-482 International Electrotechnical Vocabulary, 482-03-24.
         * @return Electric current delivered or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& current() const;

        /**
         * @brief Current battery temperature.
         * @return Current battery temperature or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& temperature() const;

        /**
         * @brief Current remaining time until battery is discharged.
         * @return Current remaining time until discharged or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& remainingBatteryTime() const;

    private:
        boost::optional<ChargeStatus> m_chargeStatus;
        boost::optional<ChargeCycles> m_chargeCycles;
        boost::optional<Measurement> m_capacityRemaining;
        boost::optional<Measurement> m_voltage;
        boost::optional<Measurement> m_current;
        boost::optional<Measurement> m_temperature;
        boost::optional<Measurement> m_remainingBatteryTime;
};


inline BatteryState::BatteryState(ComponentActivation activationState,
                                  const boost::optional<Chrono::Hours>& operatingHours,
                                  const boost::optional<OperatingCycles>& operatingCycles,
                                  const boost::optional<CalibrationInfo>& calibrationInfo,
                                  const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                                  const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                                  const boost::optional<ChargeStatus>& chargeStatus,
                                  boost::optional<ChargeCycles> chargeCycles,
                                  const boost::optional<Measurement>& capacityRemaining, // NOLINT(modernize-pass-by-value)
                                  const boost::optional<Measurement>& voltage, // NOLINT(modernize-pass-by-value)
                                  const boost::optional<Measurement>& current, // NOLINT(modernize-pass-by-value)
                                  const boost::optional<Measurement>& temperature, // NOLINT(modernize-pass-by-value)
                                  const boost::optional<Measurement>& remainingBatteryTime, // NOLINT(modernize-pass-by-value)
                                  ExtensionTypes extensions):
        AbstractDeviceComponentState(activationState, operatingHours, operatingCycles, calibrationInfo, nextCalibrationInfo, physicalConnector, std::move(extensions)),
        m_chargeStatus(chargeStatus),
        m_chargeCycles(std::move(chargeCycles)),
        m_capacityRemaining(capacityRemaining),
        m_voltage(voltage),
        m_current(current),
        m_temperature(temperature),
        m_remainingBatteryTime(remainingBatteryTime)
{
}

inline boost::optional<ChargeStatus> BatteryState::chargeStatus() const
{
    return m_chargeStatus;
}

inline boost::optional<ChargeCycles> BatteryState::chargeCycles() const
{
    return m_chargeCycles;
}

inline const boost::optional<Measurement>& BatteryState::capacityRemaining() const
{
    return m_capacityRemaining;
}

inline const boost::optional<Measurement>& BatteryState::voltage() const
{
    return m_voltage;
}

inline const boost::optional<Measurement>& BatteryState::current() const
{
    return m_current;
}

inline const boost::optional<Measurement>& BatteryState::temperature() const
{
    return m_temperature;
}

inline const boost::optional<Measurement>& BatteryState::remainingBatteryTime() const
{
    return m_remainingBatteryTime;
}

/**
 * @brief Definition of shared pointer type \ref BatteryStateSharedPtr for state \ref BatteryState.
 * @ingroup Mdib
 */
using BatteryStateSharedPtr = SharedPtr<BatteryState>;

}
}
