#pragma once

#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Alert/AbstractAlertState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalPresence.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalPrimaryLocation.h>
#include <Framework/Mdib/Public/Model/Duration.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>
#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional.hpp>

#include <cstdint>
#include <memory>
#include <utility>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct SlotTag;
}

/**
 * @brief A 0-based index that allows a prioritization of the \ref AlertSignal "alert signal" w.r.t. signal tangibility.
 * @details The slot should be used if the medium for signal generation has only a limited capability of parallel signal generation.
 * The smaller the slot index, the higher is the priority in generation of the signal.
 *
 * Example: If a signal is audible and there are different audio signals for different alert signal,
 * and more than one alert signal has to be generated, the generating system has to decide which of
 * the alert signals it generates as overlaying audio signals, may be not desirable.
 * For example, if the first alert signal has a slot number of 0 and the second alert signal has a slot number 1
 * and both signals are active, than the \ref AlertSystem "alert system" generates only the alert signal with the slot number 0.
 *
 * @ingroup Mdib
 */
using Slot = DFL::StrongTypedef<uint32_t, Impl::SlotTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief   Dynamic/volatile information of an alert signal.
 * @ingroup Mdib
 */
class AlertSignalState: public AbstractAlertState
{
    DFL_MDIB_IMMUTABLE(AlertSignalState)

    public:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AlertSignalState::actualSignalGenerationDelay() "Actual signal generation delay" to none
         * - \ref AlertSignalState::presence() "Presence" to \ref AlertSignalPresence::Off "off"
         * - \ref AlertSignalState::location() "Location" to \ref AlertSignalPrimaryLocation::Local "local"
         * - \ref AlertSignalState::slot() "Slot" to none
         *
         * \note Also applies defaults from \ref AbstractAlertState.
         */
        AlertSignalState() = default;

        /**
         * @brief Full constructor.
         */
        AlertSignalState(AlertActivation activationState,
                         boost::optional<Duration> actualSignalGenerationDelay,
                         AlertSignalPresence presence,
                         AlertSignalPrimaryLocation location,
                         boost::optional<Slot> slot,
                         ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief   Signal Generation Delay of the signal.
         * @details Semantically overrides \ref AlertSignalDescriptor::defaultSignalGenerationDelay().
         */
        const boost::optional<Duration>& actualSignalGenerationDelay() const;

        /**
         * @brief   Presence that indicates if the signal is currently generated.
         */
        AlertSignalPresence presence() const;

        /**
         * @brief   Defines where the primary alert signal is generated.
         */
        AlertSignalPrimaryLocation location() const;

        /**
         * @brief   0-based index that allows a prioritization of the alert signal.
         */
        boost::optional<Slot> slot() const;

    private:
        boost::optional<Duration> m_actualSignalGenerationDelay{};
        AlertSignalPresence m_presence{AlertSignalPresence::Off};
        AlertSignalPrimaryLocation m_location{AlertSignalPrimaryLocation::Local};
        boost::optional<Slot> m_slot{};
};

inline AlertSignalState::AlertSignalState(AlertActivation activationState,
                                          boost::optional<Duration> actualSignalGenerationDelay,
                                          AlertSignalPresence presence,
                                          AlertSignalPrimaryLocation location,
                                          boost::optional<Slot> slot,
                                          ExtensionTypes extensions) :
        AbstractAlertState(activationState, std::move(extensions)),
        m_actualSignalGenerationDelay(std::move(actualSignalGenerationDelay)),
        m_presence(presence),
        m_location(location),
        m_slot(std::move(slot))
{
}

inline const boost::optional<Duration>& AlertSignalState::actualSignalGenerationDelay() const
{
    return m_actualSignalGenerationDelay;
}

inline AlertSignalPresence AlertSignalState::presence() const
{
    return m_presence;
}

inline AlertSignalPrimaryLocation AlertSignalState::location() const
{
    return m_location;
}

inline boost::optional<Slot> AlertSignalState::slot() const
{
    return m_slot;
}

/**
 * @brief Definition of shared pointer type \ref AlertSignalStateSharedPtr for state \ref AlertSignalState.
 * @ingroup Mdib
 */
using AlertSignalStateSharedPtr = SharedPtr<AlertSignalState>;


} /* namespace Mdib */
} /* namespace DFL */
