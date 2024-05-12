#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>
#include <Framework/Mdib/Public/Model/Duration.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes the static capabilities of an \ref Mds regarding date/time handling and synchronization.
 * @ingroup Mdib
 */
class ClockDescriptor : public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(ClockDescriptor)

    public:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without further information.
         */
        ClockDescriptor() = default;

        /**
         * @brief Constructor.
         */
        ClockDescriptor(SafetyClassification safetyClassification,
                        boost::optional<CodedValue>&& type,
                        ProductionSpecifications productionSpecifications,
                        boost::optional<Duration> resolution,
                        CodedValues timeProtocol,
                        ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructor.
         */
        ClockDescriptor(SafetyClassification safetyClassification,
                        const boost::optional<CodedValue>& type,
                        ProductionSpecifications productionSpecifications,
                        boost::optional<Duration> resolution,
                        CodedValues timeProtocol,
                        ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The time between actual ticks of the clock in microseconds.
         * @return Time between ticks of the clock or \c boost::none if resolution is unknown.
         */
        const boost::optional<Duration>& resolution() const;

        /**
         * @brief Optional list of protocols that can be used to set the medical device's clock.
         * @details An empty list implies that the clock cannot be set and is therefore uncalibrated
         * and unsynchronized (e.g., equal to MDC:MDC_TIME_SYNC_NONE).
         *
         * \note Example: {MDC:MDC_TIME_SYNC_EBWW, MDC:MDC_TIME_SYNC_SNTPV4, MDC:MDC_TIME_SYNC_NTPV3} if
         * the clock supports synchronization using manually setting on the POC MEDICAL DEVICE,
         * SNTP v4.0 (RFC 2030) and NTP v3.0 (RFC 1305).
         */
        const CodedValues& timeProtocol() const;

    private:
        boost::optional<Duration> m_resolution;
        CodedValues m_timeProtocol;
};

inline ClockDescriptor::ClockDescriptor(SafetyClassification safetyClassification,
                                        boost::optional<CodedValue>&& type,
                                        ProductionSpecifications productionSpecifications,
                                        boost::optional<Duration> resolution,
                                        CodedValues timeProtocol,
                                        ExtensionTypes extensions):
        AbstractDeviceComponentDescriptor(safetyClassification, std::move(type), std::move(productionSpecifications), std::move(extensions)),
        m_resolution(std::move(resolution)),
        m_timeProtocol(std::move(timeProtocol))
{
}

inline ClockDescriptor::ClockDescriptor(SafetyClassification safetyClassification,
                                        const boost::optional<CodedValue>& type,
                                        ProductionSpecifications productionSpecifications,
                                        boost::optional<Duration> resolution,
                                        CodedValues timeProtocol,
                                        ExtensionTypes extensions):
        AbstractDeviceComponentDescriptor(safetyClassification, type, std::move(productionSpecifications), std::move(extensions)),
        m_resolution(std::move(resolution)),
        m_timeProtocol(std::move(timeProtocol))
{
}

inline const boost::optional<Duration>& ClockDescriptor::resolution() const
{
    return m_resolution;
}

inline const CodedValues& ClockDescriptor::timeProtocol() const
{
    return m_timeProtocol;
}

/**
 * @brief Definition of shared pointer type \ref ClockDescriptorSharedPtr for descriptor \ref ClockDescriptor.
 * @ingroup Mdib
 */
using ClockDescriptorSharedPtr = SharedPtr<ClockDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
