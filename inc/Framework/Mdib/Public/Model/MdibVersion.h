#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Uri.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <boost/optional/optional.hpp>

#include <memory>

namespace DFL::Mdib
{
/**
 * @brief \ref DFL::StrongTypedef representing Instance id
 *
 * @ingroup Mdib
 */
using InstanceId = DFL::StrongTypedef<unsigned long long , struct InstanceIdTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief MDIB version that consists of a version number, a unique sequence id and an instance id.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP MdibVersion
{
    public:
        /**
         * @brief Creates an initial %MdibVersion with \ref VersionCounter set to 0.
         * @param sequenceId URI for sequence identification.
         */
        explicit MdibVersion(Uri sequenceId);

        /**
         * @brief Creates an %MdibVersion with for a specific \ref VersionCounter and a specific instanceID.
         */
        MdibVersion(VersionCounter version, Uri sequenceId, boost::optional<InstanceId> instanceId);


        /**
         * @brief Version counter of this %MdibVersion.
         */
        VersionCounter version() const;

        /**
         * @brief Sequence identification URI.
         */
        const Uri& sequenceId() const;

        /**
         * @brief InstanceId of this %MdibVersion.
         */
        boost::optional<InstanceId> instanceId() const;

        /**
         * @brief Checks if this version is a previous/older version of the passed one.
         */
        bool isOlderVersionOf(const MdibVersion& rhs) const;

        /**
         * @brief Checks if versions have different URI sequence identification.
         */
        bool isOtherSequenceOf(const MdibVersion& rhs) const;

        /**
         * @brief Checks if all members are equal.
         * @details
         * Two MdibVersion objects are equal if
         * - \ref VersionCounter "Version counters" are equal
         * - sequenceIds are equal compared by [RFC 3986 Section "6.2.1.  Simple String
         * Comparison"](https://tools.ietf.org/html/rfc3986#section-6.2.1)
         */
        friend bool operator==(const MdibVersion& lhs, const MdibVersion& rhs) noexcept;

    private:
        VersionCounter m_versionCounter;
        Uri m_sequenceId;
        boost::optional<InstanceId> m_instanceId;

};

/**
 * @name Comparison operators
 * @details
 * Two MdibVersion objects are equal if
 * - \ref VersionCounter "Version counters" are equal
 * - sequenceIds are equal compared by [RFC 3986 Section "6.2.1.  Simple String
 * Comparison"](https://tools.ietf.org/html/rfc3986#section-6.2.1)
 */
///@{
inline bool operator==(const MdibVersion& lhs, const MdibVersion& rhs) noexcept
{
    return lhs.m_versionCounter == rhs.m_versionCounter &&
           lhs.m_sequenceId == rhs.m_sequenceId &&
           lhs.m_instanceId == rhs.m_instanceId;
}

inline bool operator!=(const MdibVersion& lhs, const MdibVersion& rhs) noexcept
{
    return !(lhs == rhs);
}
///@}

/**
 * @brief Creates a new \ref MdibVersion based on an existing one.
 * @ingroup Mdib
 */
MdibVersion operator+(const MdibVersion& lhs, unsigned int rhs);

inline VersionCounter MdibVersion::version() const
{
    return m_versionCounter;
}

inline const Uri& MdibVersion::sequenceId() const
{
    return m_sequenceId;
}

inline boost::optional<InstanceId> MdibVersion::instanceId() const
{
    return m_instanceId;
}

inline MdibVersion operator+(const MdibVersion& lhs, unsigned int rhs)
{
    return {VersionCounter(lhs.version().get() + rhs), lhs.sequenceId(), lhs.instanceId()};
}

} /* namespace DFL */
