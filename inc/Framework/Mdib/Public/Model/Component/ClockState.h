#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentState.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Chrono/Public/TimeZone.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL::Mdib
{

/**
 * @brief Indicates if the time is synchronized to an external source or set by an operator.
 * @ingroup Mdib
 */
enum class ClockSynchronization
{
    WithExternalSource, ///< The clock is synchronized with an external source (e.g., time server).
    Manual ///< The clock is manually set by an operator.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ClockSynchronization, (WithExternalSource)(Manual))

/**
 * @brief Identifies that the clock information is actively being used in care delivery algorithms/protocols.
 * @ingroup Mdib
 */
enum class ClockUsage
{
    Critical, ///< Clock information is actively being used in care delivery algorithms/protocols.
    NonCritical ///< Clock information is used for non-critical purposes only.
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ClockUsage, (Critical)(NonCritical))

/**
 * @brief Dynamic part of of a the \ref Clock object.
 * @note It does not contain the DateAndTime member from BICEPS schema.
 * @ingroup Mdib
 */
class ClockState: public AbstractDeviceComponentState
{
    DFL_MDIB_IMMUTABLE(ClockState)

    public:
        /**
         * @brief Defaults to \ref ComponentActivation::On "component activation on" with
         * \ref ClockSynchronization::Manual "manual clock synchronization" for
         * \ref ClockUsage::NonCritical "non critical use".
         */
        ClockState() = default;

        /**
         * @brief Constructor.
         */
        ClockState(ComponentActivation activationState,
                   const boost::optional<Chrono::Hours>& operatingHours,
                   const boost::optional<OperatingCycles>& operatingCycles,
                   const boost::optional<CalibrationInfo>& calibrationInfo,
                   const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                   const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                   const boost::optional<CodedValue>& activeSyncProtocol,
                   std::vector<Locale::Utf8> referenceSources,
                   ClockSynchronization remoteSync,
                   boost::optional<Decimal> accuracy,
                   boost::optional<Timestamp> lastSet,
                   boost::optional<Chrono::TimeZone> timeZone,
                   ClockUsage criticalUse,
                   ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Protocol that is actively being used for time sync.
         * @details Examples: MDC:MDC_TIME_SYNC_NTPV3 if the clock is synchronized using NTP v3.0 (RFC 1305)
         * or MDC:MDC_TIME_SYNC_NONE if the clock is not synchronized.
         */
        const boost::optional<CodedValue>& activeSyncProtocol() const;

        /**
         * @brief Identifies the clock's external reference source(s), e.g., NTP server addresses.
         */
        const std::vector<Locale::Utf8>& referenceSources() const;

        /**
         * @brief Indicates if the time is synchronized to an external source or set by an operator.
         */
        ClockSynchronization remoteSync() const;

        /**
         * @brief A decimal number indicating the maximum error in seconds of the absolute time
         * relative to a primary reference clock source.
         * @details In systems where time synchronization is not used and the clock is set manually
         * by "eyeball and wristwatch" (EBWW), this shall be initialized to three minutes when the
         * clock time is set. If NTP is used, this is equivalent to Root Dispersion + 1/2 Root Delay.
         */
        boost::optional<Decimal> accuracy() const;

        /**
         * @brief Time point when the absolute time was set or synchronized.
         * @details
         *
         * \note If a time synchronization protocol is used that "changes" the time and
         * date at a high frequency, it is proposed to update this value at a lower periodicity
         * (e.g., once every 10 minutes or once an hour), so as not to consume communications bandwidth
         * unnecessarily.
         * \note Synchronization might be achieved by slewing the time. This means that the virtual
         * frequency of the software clock is adjusted to make the clock go faster or slower until it is corrected.
         */
        const boost::optional<Timestamp>& lastSet() const;

        /**
         * @brief Identifies the time zone and daylight saving time of the clock.
         */
        const boost::optional<Chrono::TimeZone>& timeZone() const;

        /**
         * @brief Identifies that the clock information is actively being used in care delivery algorithms/protocols.
         */
        ClockUsage criticalUse() const;

    private:
        boost::optional<CodedValue> m_activeSyncProtocol{};
        std::vector<Locale::Utf8> m_referenceSources{};
        ClockSynchronization m_remoteSync{ClockSynchronization::Manual};
        boost::optional<Decimal> m_accuracy{};
        boost::optional<Timestamp> m_lastSet{};
        boost::optional<Chrono::TimeZone> m_timeZone{};
        ClockUsage m_criticalUse{ClockUsage::NonCritical};
};

inline ClockState::ClockState(ComponentActivation activationState,
                              const boost::optional<Chrono::Hours>& operatingHours,
                              const boost::optional<OperatingCycles>& operatingCycles,
                              const boost::optional<CalibrationInfo>& calibrationInfo,
                              const boost::optional<CalibrationInfo>& nextCalibrationInfo,
                              const boost::optional<PhysicalConnectorInfo>& physicalConnector,
                              const boost::optional<CodedValue>& activeSyncProtocol, // NOLINT(modernize-pass-by-value)
                              std::vector<Locale::Utf8> referenceSources,
                              ClockSynchronization remoteSync,
                              boost::optional<Decimal> accuracy,
                              boost::optional<Timestamp> lastSet,
                              boost::optional<Chrono::TimeZone> timeZone,
                              ClockUsage criticalUse,
                              ExtensionTypes extensions):
        AbstractDeviceComponentState(activationState, operatingHours, operatingCycles, calibrationInfo, nextCalibrationInfo, physicalConnector, std::move(extensions)),
        m_activeSyncProtocol(activeSyncProtocol),
        m_referenceSources(std::move(referenceSources)),
        m_remoteSync(remoteSync),
        m_accuracy(std::move(accuracy)),
        m_lastSet(std::move(lastSet)),
        m_timeZone(std::move(timeZone)),
        m_criticalUse(criticalUse)
{
}

inline ClockSynchronization ClockState::remoteSync() const
{
    return m_remoteSync;
}

inline boost::optional<Decimal> ClockState::accuracy() const
{
    return m_accuracy;
}

inline const boost::optional<Timestamp>& ClockState::lastSet() const
{
    return m_lastSet;
}

inline const boost::optional<Chrono::TimeZone>& ClockState::timeZone() const
{
    return m_timeZone;
}

inline ClockUsage ClockState::criticalUse() const
{
    return m_criticalUse;
}

inline const boost::optional<CodedValue>& ClockState::activeSyncProtocol() const
{
    return m_activeSyncProtocol;
}

inline const std::vector<Locale::Utf8>& ClockState::referenceSources() const
{
    return m_referenceSources;
}

/**
 * @brief Definition of shared pointer type \ref ClockStateSharedPtr for state \ref ClockState.
 * @ingroup Mdib
 */
using ClockStateSharedPtr = SharedPtr<ClockState>;

}
