/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <memory>
#include <boost/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <Framework/Mdib/Public/Model/Component/ClockState.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder with fluent interface for @ref ClockState
 * @ingroup Mdib
 */
class ClockStateBuilder
{
    public:
        /// @brief Typedef to the immutable @ref ClockState
        using BuiltType = ClockState;

        /// @brief Builder based on given immutable @ref ClockState
        explicit ClockStateBuilder(const ClockState& clockState=ClockState());

        /// @brief Builder based on given immutable @ref ClockState
        explicit ClockStateBuilder(const DFL::NotNull<SharedPtr<ClockState>>& clockState);

        /// @brief Overwrite all values with given immutable @ref ClockState
        ClockStateBuilder& operator=(const ClockState& clockState);

        /// @brief Explicit conversion to immutable @ref ClockState
        ClockState build() const;

        /// @brief Test whether the builder differs from the immutable @ref ClockState
        bool isChanged(const ClockState& base) const;

        /// @brief Setter for activationState
        /// @{
        ClockStateBuilder& activationState(ComponentActivation activationState);
        /// @}

        /// @brief Setter for operatingHours
        /// @{
        ClockStateBuilder& operatingHours(const boost::optional<Chrono::Hours>& operatingHours);
        ClockStateBuilder& operatingHours(boost::optional<Chrono::Hours>&& operatingHours);
        /// @}

        /// @brief Setter for operatingCycles
        /// @{
        ClockStateBuilder& operatingCycles(const boost::optional<OperatingCycles>& operatingCycles);
        ClockStateBuilder& operatingCycles(boost::optional<OperatingCycles>&& operatingCycles);
        /// @}

        /// @brief Setter for calibrationInfo
        /// @{
        ClockStateBuilder& calibrationInfo(const boost::optional<CalibrationInfo>& calibrationInfo);
        ClockStateBuilder& calibrationInfo(boost::optional<CalibrationInfo>&& calibrationInfo);
        /// @}

        /// @brief Setter for nextCalibrationInfo
        /// @{
        ClockStateBuilder& nextCalibrationInfo(const boost::optional<CalibrationInfo>& nextCalibrationInfo);
        ClockStateBuilder& nextCalibrationInfo(boost::optional<CalibrationInfo>&& nextCalibrationInfo);
        /// @}

        /// @brief Setter for physicalConnector
        /// @{
        ClockStateBuilder& physicalConnector(const boost::optional<PhysicalConnectorInfo>& physicalConnector);
        ClockStateBuilder& physicalConnector(boost::optional<PhysicalConnectorInfo>&& physicalConnector);
        /// @}

        /// @brief Setter for activeSyncProtocol
        /// @{
        ClockStateBuilder& activeSyncProtocol(const boost::optional<CodedValue>& activeSyncProtocol);
        ClockStateBuilder& activeSyncProtocol(boost::optional<CodedValue>&& activeSyncProtocol);
        /// @}

        /// @brief Setter for referenceSources
        /// @{
        ClockStateBuilder& referenceSources(const std::vector<Locale::Utf8>& referenceSources);
        ClockStateBuilder& referenceSources(std::vector<Locale::Utf8>&& referenceSources);
        /// @}

        /// @brief Setter for remoteSync
        /// @{
        ClockStateBuilder& remoteSync(ClockSynchronization remoteSync);
        /// @}

        /// @brief Setter for accuracy
        /// @{
        ClockStateBuilder& accuracy(const boost::optional<Decimal>& accuracy);
        ClockStateBuilder& accuracy(boost::optional<Decimal>&& accuracy);
        /// @}

        /// @brief Setter for lastSet
        /// @{
        ClockStateBuilder& lastSet(const boost::optional<Timestamp>& lastSet);
        ClockStateBuilder& lastSet(boost::optional<Timestamp>&& lastSet);
        /// @}

        /// @brief Setter for timeZone
        /// @{
        ClockStateBuilder& timeZone(const boost::optional<Chrono::TimeZone>& timeZone);
        ClockStateBuilder& timeZone(boost::optional<Chrono::TimeZone>&& timeZone);
        /// @}

        /// @brief Setter for criticalUse
        /// @{
        ClockStateBuilder& criticalUse(ClockUsage criticalUse);
        /// @}

        /// @brief Setter for extensions
        /// @{
        ClockStateBuilder& extensions(const ExtensionTypes& extensions);
        ClockStateBuilder& extensions(ExtensionTypes&& extensions);
        /// @}

        /// @brief Getter for activationState
        /// @{
        ComponentActivation& activationState();
        ComponentActivation activationState() const;
        /// @}

        /// @brief Getter for operatingHours
        /// @{
        boost::optional<Chrono::Hours>& operatingHours();
        const boost::optional<Chrono::Hours>& operatingHours() const;
        /// @}

        /// @brief Getter for operatingCycles
        /// @{
        boost::optional<OperatingCycles>& operatingCycles();
        const boost::optional<OperatingCycles>& operatingCycles() const;
        /// @}

        /// @brief Getter for calibrationInfo
        /// @{
        boost::optional<CalibrationInfo>& calibrationInfo();
        const boost::optional<CalibrationInfo>& calibrationInfo() const;
        /// @}

        /// @brief Getter for nextCalibrationInfo
        /// @{
        boost::optional<CalibrationInfo>& nextCalibrationInfo();
        const boost::optional<CalibrationInfo>& nextCalibrationInfo() const;
        /// @}

        /// @brief Getter for physicalConnector
        /// @{
        boost::optional<PhysicalConnectorInfo>& physicalConnector();
        const boost::optional<PhysicalConnectorInfo>& physicalConnector() const;
        /// @}

        /// @brief Getter for activeSyncProtocol
        /// @{
        boost::optional<CodedValue>& activeSyncProtocol();
        const boost::optional<CodedValue>& activeSyncProtocol() const;
        /// @}

        /// @brief Getter for referenceSources
        /// @{
        std::vector<Locale::Utf8>& referenceSources();
        const std::vector<Locale::Utf8>& referenceSources() const;
        /// @}

        /// @brief Getter for remoteSync
        /// @{
        ClockSynchronization& remoteSync();
        ClockSynchronization remoteSync() const;
        /// @}

        /// @brief Getter for accuracy
        /// @{
        boost::optional<Decimal>& accuracy();
        const boost::optional<Decimal>& accuracy() const;
        /// @}

        /// @brief Getter for lastSet
        /// @{
        boost::optional<Timestamp>& lastSet();
        const boost::optional<Timestamp>& lastSet() const;
        /// @}

        /// @brief Getter for timeZone
        /// @{
        boost::optional<Chrono::TimeZone>& timeZone();
        const boost::optional<Chrono::TimeZone>& timeZone() const;
        /// @}

        /// @brief Getter for criticalUse
        /// @{
        ClockUsage& criticalUse();
        ClockUsage criticalUse() const;
        /// @}

        /// @brief Getter for extensions
        /// @{
        ExtensionTypes& extensions();
        const ExtensionTypes& extensions() const;
        /// @}

    private:
        ComponentActivation m_activationState;
        boost::optional<Chrono::Hours> m_operatingHours;
        boost::optional<OperatingCycles> m_operatingCycles;
        boost::optional<CalibrationInfo> m_calibrationInfo;
        boost::optional<CalibrationInfo> m_nextCalibrationInfo;
        boost::optional<PhysicalConnectorInfo> m_physicalConnector;
        boost::optional<CodedValue> m_activeSyncProtocol;
        std::vector<Locale::Utf8> m_referenceSources;
        ClockSynchronization m_remoteSync;
        boost::optional<Decimal> m_accuracy;
        boost::optional<Timestamp> m_lastSet;
        boost::optional<Chrono::TimeZone> m_timeZone;
        ClockUsage m_criticalUse;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const ClockState& lhs, const ClockState& rhs);
DFL_MDIB_EXPIMP bool operator==(const ClockStateBuilder& lhs, const ClockStateBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const ClockStateBuilder& lhs, const ClockState& rhs);
bool operator==(const ClockState& lhs, const ClockStateBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator!=(const ClockState& lhs, const ClockState& rhs);
bool operator!=(const ClockStateBuilder& lhs, const ClockStateBuilder& rhs);
bool operator!=(const ClockState& lhs, const ClockStateBuilder& rhs);
bool operator!=(const ClockStateBuilder& lhs, const ClockState& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref ClockState
 * @ingroup Mdib
 */
/// @{
ClockStateBuilder getBuilder(const ClockState& clockState);
ClockStateBuilder getBuilder(const DFL::NotNull<SharedPtr<ClockState>>& clockState);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const ClockState& lhs, const ClockState& rhs);

inline ClockStateBuilder::ClockStateBuilder(const ClockState& clockState) :
    m_activationState(clockState.activationState()),
    m_operatingHours(clockState.operatingHours()),
    m_operatingCycles(clockState.operatingCycles()),
    m_calibrationInfo(clockState.calibrationInfo()),
    m_nextCalibrationInfo(clockState.nextCalibrationInfo()),
    m_physicalConnector(clockState.physicalConnector()),
    m_activeSyncProtocol(clockState.activeSyncProtocol()),
    m_referenceSources(clockState.referenceSources()),
    m_remoteSync(clockState.remoteSync()),
    m_accuracy(clockState.accuracy()),
    m_lastSet(clockState.lastSet()),
    m_timeZone(clockState.timeZone()),
    m_criticalUse(clockState.criticalUse()),
    m_extensions(clockState.extensions())
{
}

inline ClockStateBuilder::ClockStateBuilder(const DFL::NotNull<SharedPtr<ClockState>>& clockState) :
    m_activationState(clockState->activationState()),
    m_operatingHours(clockState->operatingHours()),
    m_operatingCycles(clockState->operatingCycles()),
    m_calibrationInfo(clockState->calibrationInfo()),
    m_nextCalibrationInfo(clockState->nextCalibrationInfo()),
    m_physicalConnector(clockState->physicalConnector()),
    m_activeSyncProtocol(clockState->activeSyncProtocol()),
    m_referenceSources(clockState->referenceSources()),
    m_remoteSync(clockState->remoteSync()),
    m_accuracy(clockState->accuracy()),
    m_lastSet(clockState->lastSet()),
    m_timeZone(clockState->timeZone()),
    m_criticalUse(clockState->criticalUse()),
    m_extensions(clockState->extensions())
{
}

inline ClockStateBuilder& ClockStateBuilder::operator=(const ClockState& clockState)
{
    m_activationState = clockState.activationState();
    m_operatingHours = clockState.operatingHours();
    m_operatingCycles = clockState.operatingCycles();
    m_calibrationInfo = clockState.calibrationInfo();
    m_nextCalibrationInfo = clockState.nextCalibrationInfo();
    m_physicalConnector = clockState.physicalConnector();
    m_activeSyncProtocol = clockState.activeSyncProtocol();
    m_referenceSources = clockState.referenceSources();
    m_remoteSync = clockState.remoteSync();
    m_accuracy = clockState.accuracy();
    m_lastSet = clockState.lastSet();
    m_timeZone = clockState.timeZone();
    m_criticalUse = clockState.criticalUse();
    m_extensions = clockState.extensions();
    return *this;
}

inline ClockState ClockStateBuilder::build() const
{
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return ClockState(m_activationState, m_operatingHours, m_operatingCycles, m_calibrationInfo, m_nextCalibrationInfo, m_physicalConnector, m_activeSyncProtocol, m_referenceSources, m_remoteSync, m_accuracy, m_lastSet, m_timeZone, m_criticalUse, m_extensions);
}

inline bool ClockStateBuilder::isChanged(const ClockState& base) const
{
    return *this != base;
}

inline ClockStateBuilder& ClockStateBuilder::activationState(ComponentActivation activationState)
{
    m_activationState = activationState;
    return *this;
}

inline ComponentActivation& ClockStateBuilder::activationState()
{
    return m_activationState;
}

inline ComponentActivation ClockStateBuilder::activationState() const
{
    return m_activationState;
}

inline ClockStateBuilder& ClockStateBuilder::operatingHours(const boost::optional<Chrono::Hours>& operatingHours)
{
    m_operatingHours = operatingHours;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::operatingHours(boost::optional<Chrono::Hours>&& operatingHours)
{
    m_operatingHours = std::move(operatingHours);
    return *this;
}

inline boost::optional<Chrono::Hours>& ClockStateBuilder::operatingHours()
{
    return m_operatingHours;
}

inline const boost::optional<Chrono::Hours>& ClockStateBuilder::operatingHours() const
{
    return m_operatingHours;
}

inline ClockStateBuilder& ClockStateBuilder::operatingCycles(const boost::optional<OperatingCycles>& operatingCycles)
{
    m_operatingCycles = operatingCycles;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::operatingCycles(boost::optional<OperatingCycles>&& operatingCycles)
{
    m_operatingCycles = std::move(operatingCycles);
    return *this;
}

inline boost::optional<OperatingCycles>& ClockStateBuilder::operatingCycles()
{
    return m_operatingCycles;
}

inline const boost::optional<OperatingCycles>& ClockStateBuilder::operatingCycles() const
{
    return m_operatingCycles;
}

inline ClockStateBuilder& ClockStateBuilder::calibrationInfo(const boost::optional<CalibrationInfo>& calibrationInfo)
{
    m_calibrationInfo = calibrationInfo;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::calibrationInfo(boost::optional<CalibrationInfo>&& calibrationInfo)
{
    m_calibrationInfo = std::move(calibrationInfo);
    return *this;
}

inline boost::optional<CalibrationInfo>& ClockStateBuilder::calibrationInfo()
{
    return m_calibrationInfo;
}

inline const boost::optional<CalibrationInfo>& ClockStateBuilder::calibrationInfo() const
{
    return m_calibrationInfo;
}

inline ClockStateBuilder& ClockStateBuilder::nextCalibrationInfo(const boost::optional<CalibrationInfo>& nextCalibrationInfo)
{
    m_nextCalibrationInfo = nextCalibrationInfo;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::nextCalibrationInfo(boost::optional<CalibrationInfo>&& nextCalibrationInfo)
{
    m_nextCalibrationInfo = std::move(nextCalibrationInfo);
    return *this;
}

inline boost::optional<CalibrationInfo>& ClockStateBuilder::nextCalibrationInfo()
{
    return m_nextCalibrationInfo;
}

inline const boost::optional<CalibrationInfo>& ClockStateBuilder::nextCalibrationInfo() const
{
    return m_nextCalibrationInfo;
}

inline ClockStateBuilder& ClockStateBuilder::physicalConnector(const boost::optional<PhysicalConnectorInfo>& physicalConnector)
{
    m_physicalConnector = physicalConnector;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::physicalConnector(boost::optional<PhysicalConnectorInfo>&& physicalConnector)
{
    m_physicalConnector = std::move(physicalConnector);
    return *this;
}

inline boost::optional<PhysicalConnectorInfo>& ClockStateBuilder::physicalConnector()
{
    return m_physicalConnector;
}

inline const boost::optional<PhysicalConnectorInfo>& ClockStateBuilder::physicalConnector() const
{
    return m_physicalConnector;
}

inline ClockStateBuilder& ClockStateBuilder::activeSyncProtocol(const boost::optional<CodedValue>& activeSyncProtocol)
{
    m_activeSyncProtocol = activeSyncProtocol;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::activeSyncProtocol(boost::optional<CodedValue>&& activeSyncProtocol)
{
    m_activeSyncProtocol = std::move(activeSyncProtocol);
    return *this;
}

inline boost::optional<CodedValue>& ClockStateBuilder::activeSyncProtocol()
{
    return m_activeSyncProtocol;
}

inline const boost::optional<CodedValue>& ClockStateBuilder::activeSyncProtocol() const
{
    return m_activeSyncProtocol;
}

inline ClockStateBuilder& ClockStateBuilder::referenceSources(const std::vector<Locale::Utf8>& referenceSources)
{
    m_referenceSources = referenceSources;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::referenceSources(std::vector<Locale::Utf8>&& referenceSources)
{
    m_referenceSources = std::move(referenceSources);
    return *this;
}

inline std::vector<Locale::Utf8>& ClockStateBuilder::referenceSources()
{
    return m_referenceSources;
}

inline const std::vector<Locale::Utf8>& ClockStateBuilder::referenceSources() const
{
    return m_referenceSources;
}

inline ClockStateBuilder& ClockStateBuilder::remoteSync(ClockSynchronization remoteSync)
{
    m_remoteSync = remoteSync;
    return *this;
}

inline ClockSynchronization& ClockStateBuilder::remoteSync()
{
    return m_remoteSync;
}

inline ClockSynchronization ClockStateBuilder::remoteSync() const
{
    return m_remoteSync;
}

inline ClockStateBuilder& ClockStateBuilder::accuracy(const boost::optional<Decimal>& accuracy)
{
    m_accuracy = accuracy;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::accuracy(boost::optional<Decimal>&& accuracy)
{
    m_accuracy = std::move(accuracy);
    return *this;
}

inline boost::optional<Decimal>& ClockStateBuilder::accuracy()
{
    return m_accuracy;
}

inline const boost::optional<Decimal>& ClockStateBuilder::accuracy() const
{
    return m_accuracy;
}

inline ClockStateBuilder& ClockStateBuilder::lastSet(const boost::optional<Timestamp>& lastSet)
{
    m_lastSet = lastSet;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::lastSet(boost::optional<Timestamp>&& lastSet)
{
    m_lastSet = std::move(lastSet);
    return *this;
}

inline boost::optional<Timestamp>& ClockStateBuilder::lastSet()
{
    return m_lastSet;
}

inline const boost::optional<Timestamp>& ClockStateBuilder::lastSet() const
{
    return m_lastSet;
}

inline ClockStateBuilder& ClockStateBuilder::timeZone(const boost::optional<Chrono::TimeZone>& timeZone)
{
    m_timeZone = timeZone;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::timeZone(boost::optional<Chrono::TimeZone>&& timeZone)
{
    m_timeZone = std::move(timeZone);
    return *this;
}

inline boost::optional<Chrono::TimeZone>& ClockStateBuilder::timeZone()
{
    return m_timeZone;
}

inline const boost::optional<Chrono::TimeZone>& ClockStateBuilder::timeZone() const
{
    return m_timeZone;
}

inline ClockStateBuilder& ClockStateBuilder::criticalUse(ClockUsage criticalUse)
{
    m_criticalUse = criticalUse;
    return *this;
}

inline ClockUsage& ClockStateBuilder::criticalUse()
{
    return m_criticalUse;
}

inline ClockUsage ClockStateBuilder::criticalUse() const
{
    return m_criticalUse;
}

inline ClockStateBuilder& ClockStateBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline ClockStateBuilder& ClockStateBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& ClockStateBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& ClockStateBuilder::extensions() const
{
    return m_extensions;
}

inline bool operator==(const ClockState& lhs, const ClockStateBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const ClockStateBuilder& lhs, const ClockStateBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const ClockState& lhs, const ClockStateBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const ClockStateBuilder& lhs, const ClockState& rhs)
{
    return !(lhs == rhs);
}

inline ClockStateBuilder getBuilder(const ClockState& clockState)
{
    return ClockStateBuilder(clockState);
}

inline ClockStateBuilder getBuilder(const DFL::NotNull<SharedPtr<ClockState>>& clockState)
{
    return ClockStateBuilder(clockState);
}

}
}
