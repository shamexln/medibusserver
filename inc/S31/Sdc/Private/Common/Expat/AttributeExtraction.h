#pragma once

#include <S31/Sdc/Private/Common/ErrorDefinitions.h>
#include <S31/BicepsXml/S31Only/Duration.h>
#include <S31/Base/S31Only/Exception.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Format/Public/Stream.h>
#include <Framework/Mdib/Public/Model/DecimalConvert.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Mdib/Public/Model/TimestampConvert.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Utils/Public/NotNull.h>

#include <cstring>
#include <cstdlib>

namespace S31::Sdc::Impl::Expat
{

/**
 * @ingroup S31SdcCommon
 */
static const char* requiredNonEmptyAttribute(const char* attributeName, const char** attributes);

/**
 * @ingroup S31SdcCommon
 */
static const char* optionalAttribute(const char* attributeName, const char** attributes);

/**
 * @ingroup S31SdcCommon
 */
static const char* optionalAttributeWithDefault(const char* attributeName, const char** attributes, const char* defaultValue);

/**
 * @ingroup S31SdcCommon
 */
static const char* requiredAttribute(const char* attributeName, const char** attributes);

/**
 * @ingroup S31SdcCommon
 */
unsigned long long toUnsignedLongLong(DFL::NotNull<const char*> string);

/**
 * @ingroup S31SdcCommon
 */
long long toLongLong(DFL::NotNull<const char*> string);

inline const char* requiredNonEmptyAttribute(const char* attributeName, const char** attributes)
{
    for (int i = 0; attributes[i]; i += 2)
    {
        if (strcmp(attributes[i], attributeName) == 0)
        {
            if (attributes[i + 1][0] != '\0')
            {
                return attributes[i + 1];
            }
            S31_THROW_EXCEPTION(
                    ExternalDataMappingFailed, "required (non-empty) attribute '" << attributeName << "' is empty");
        }
    }
    S31_THROW_EXCEPTION(
            ExternalDataMappingFailed, "required (non-empty) attribute '" << attributeName << "' not found");
}

inline const char* optionalAttribute(const char* attributeName, const char** attributes)
{
    for (int i = 0; attributes[i]; i += 2)
    {
        if (strcmp(attributes[i], attributeName) == 0)
        {
            return attributes[i + 1];
        }
    }
    return nullptr;
}

inline boost::optional<DFL::Mdib::Decimal> optionalDecimalAttribute(const char* attributeName, const char** attributes)
{
    if (const auto* string = optionalAttribute(attributeName, attributes))
    {
        return DFL::Mdib::Convert::toDecimal(string);
    }
    return boost::none;
}


inline const char* optionalAttributeWithDefault(const char* attributeName, const char** attributes, const char* defaultValue)
{
    if (const auto* found = optionalAttribute(attributeName, attributes))
    {
        return found;
    }
    return defaultValue;
}

inline const char* requiredAttribute(const char* attributeName, const char** attributes)
{
    if (const auto* found = optionalAttribute(attributeName, attributes))
    {
        return found;
    }
    S31_THROW_EXCEPTION(ExternalDataMappingFailed, "required attribute '" << attributeName << "' not found");
}

/**
 * @ingroup S31SdcCommon
 */
static boost::optional<DFL::Mdib::Timestamp> toOptionalTimestamp(const char* timestamp);
inline boost::optional<DFL::Mdib::Timestamp> toOptionalTimestamp(const char* timestamp)
{
    if (timestamp)
    {
        auto msSince1970 = toUnsignedLongLong(DFL::asNotNull(timestamp));
        return DFL::Mdib::Convert::fromBicepsTimestamp(DFL::Mdib::BicepsTimestamp{msSince1970});
    }
    return boost::none;
}

/**
 * @ingroup S31SdcCommon
 */
static boost::optional<DFL::Mdib::Duration> toOptionalDuration(const char* durationString);
inline boost::optional<DFL::Mdib::Duration> toOptionalDuration(const char* durationString)
{
    if (!durationString)
    {
        return boost::none;
    }

    auto duration = Convert::toOptionalIsoDuration(durationString);
    if (!duration)
    {
        S31_THROW_EXCEPTION(ExternalDataMappingFailed, "cannot convert string '" << durationString << "' to duration");
    }

    auto microSeconds = Convert::toOptionalMicroseconds(*duration);
    if (!microSeconds)
    {
        // Conversion to microseconds returns boost::none if limits preventing
        // overflow during conversion are exceeded.
        S31_THROW_EXCEPTION(
                ExternalDataMappingFailed,
                "cannot convert string '" << durationString << "' to duration (out of range)");
    }

    return microSeconds;
}

/**
 * @ingroup S31SdcCommon
 */
static unsigned long long toUlong64(const char* longString);

/**
 * @ingroup S31SdcCommon
 */
static uint32_t toUint32(const char* intString);
inline uint32_t toUint32(const char* intString)
{
    unsigned long long const intValue = toUlong64(intString);

    if (intValue > (std::numeric_limits<uint32_t>::max)())
    {
        S31_THROW_EXCEPTION(
                ExternalDataMappingFailed, "cannot convert string '" << intString << "' into uint32 (out of range)");
    }
    return static_cast<uint32_t>(intValue);
}

inline unsigned long long toUlong64(const char* longString)
{
    if (longString)
    {
        return toUnsignedLongLong(DFL::asNotNull(longString));
    }
    S31_THROW_EXCEPTION(ExternalDataMappingFailed, "nullptr is not a valid ulong64");
}

/**
 * @ingroup S31SdcCommon
 */
static boost::optional<int32_t> toOptionalInt32(const char* intString);
inline boost::optional<int32_t> toOptionalInt32(const char* intString)
{
    if (intString)
    {
        long long longValue = toLongLong(DFL::asNotNull(intString));
        if (longValue > (std::numeric_limits<int32_t>::max)() ||
                longValue < (std::numeric_limits<int32_t>::min)())
        {
            S31_THROW_EXCEPTION(
                    ExternalDataMappingFailed, "cannot convert string '" << intString << "' into int32 (out of range)");
        }
        return static_cast<int32_t>(longValue);
    }
    return boost::none;
}

/**
 * @ingroup S31SdcCommon
 */
static boost::optional<DFL::Mdib::VersionCounter> toOptionalVersionCounter(const char* versionString);
inline boost::optional<DFL::Mdib::VersionCounter> toOptionalVersionCounter(const char* versionString)
{
    if (versionString)
    {
        unsigned long long const version = toUnsignedLongLong(DFL::asNotNull(versionString));
        return DFL::Mdib::VersionCounter(version);
    }
    return boost::none;
}

/**
 * @ingroup S31SdcCommon
 */
static DFL::Mdib::VersionCounter toVersionCounter(const char* versionString);
inline DFL::Mdib::VersionCounter toVersionCounter(const char* versionString)
{
    auto optVersion = toOptionalVersionCounter(versionString);
    return optVersion ? *optVersion : DFL::Mdib::VersionCounter(0);
}

}
