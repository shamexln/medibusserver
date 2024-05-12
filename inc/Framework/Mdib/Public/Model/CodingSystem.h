#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Mdib/Public/Model/Uri.h>

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Strong typedef of a coding system identifier.
 * @ingroup Mdib
 */
using CodingSystemId = DFL::StrongTypedef<Uri, struct CodingSystemIdTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Strong typedef of a coding system version.
 * @ingroup Mdib
 */
using CodingSystemVersion = DFL::StrongTypedef<Locale::Utf8, struct CodingSystemVersionTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Represents a coding system with codes to identify concepts.
 * @details An example coding system is the ISO/IEEE 11073-10101 nomenclature
 * to identify metrics such as SPO2.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodingSystem
{
    public:
        /**
         * @brief Constructs a coding system.
         * @details The provided coding system id shall be an URI with
         * an OID (urn:oid:...) or an UUID (urn:uuid:...).
         * @deprecated Please use \ref DFL::Mdib::CodingSystem(const CodingSystemId&) instead.
         *
         * @param codingSystemId The identification of the code system that defines the meaning of codes.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant by using DFL::Mdib::CodingSystemId for argument")
        explicit CodingSystem(const Locale::Utf8& codingSystemId);

        /**
         * @brief Constructor with coding system and version members.
         * @deprecated Please use \ref DFL::Mdib::CodingSystem(const CodingSystemId&, const CodingSystemVersion&) instead.
         *
         * @param codingSystemId The identification of the code system that defines the meaning of codes.
         * @param codingSystemVersion Optional coding system version.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant by using DFL::Mdib::CodingSystemId and DFL::Mdib::CodingSystemVersion for arguments")
        CodingSystem(const Locale::Utf8& codingSystemId,
                     const Locale::Utf8& codingSystemVersion);

        /**
         * @brief Constructor with all members.
         * @deprecated Please use \ref DFL::Mdib::CodingSystem(const CodingSystemId&, const CodingSystemVersion&, const LocalizedTexts&) instead.
         *
         * @param codingSystemId The identification of the code system that defines the meaning of codes.
         * @param codingSystemVersion Optional coding system version.
         * @param codingSystemNames Optional human-readable names for displaying purposes.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant by using DFL::Mdib::CodingSystemId and DFL::Mdib::CodingSystemVersion for first arguments")
        CodingSystem(const Locale::Utf8& codingSystemId,
                     const Locale::Utf8& codingSystemVersion,
                     LocalizedTexts codingSystemNames);

        /**
         * @brief Constructs a coding system.
         * @details The provided coding system id shall be an URI with
         * an OID (urn:oid:...) or an UUID (urn:uuid:...).
         *
         * @param codingSystemId The identification of the code system that defines the meaning of codes.
         */
        explicit CodingSystem(CodingSystemId codingSystemId);

        /**
         * @brief Constructor with coding system and version members.
         *
         * @param codingSystemId The identification of the code system that defines the meaning of codes.
         * @param codingSystemVersion Optional coding system version.
         */
        CodingSystem(CodingSystemId codingSystemId,
                     CodingSystemVersion codingSystemVersion);

        /**
         * @brief Constructor with all members.
         *
         * @param codingSystemId The identification of the code system that defines the meaning of codes.
         * @param codingSystemVersion Optional coding system version.
         * @param codingSystemNames Optional human-readable names for displaying purposes.
         */
        CodingSystem(CodingSystemId codingSystemId,
                     CodingSystemVersion codingSystemVersion,
                     LocalizedTexts codingSystemNames);

        /**
         * @brief Provides the coding system identifier as passed in the constructor.
         * @return The coding system identifier.
         */
        const CodingSystemId& id() const;

        /**
         * @name Coding system version
         * @brief Version of the system - if relevant.
         * @details
         * Note that a well-maintained coding system does not need the version
         * reported, because the meaning of codes is consistent across
         * versions. However this cannot consistently be assured. and when the
         * meaning is not guaranteed to be consistent, the version should be
         * set.
         * @{
         */
        const CodingSystemVersion& version() const;
        ///@}

        /**
         * @name Coding system names
         * @brief Human-readable name for displaying purposes.
         * @details The coding system name shall not be used in algorithm to
         * identify a coding system.
         * @{
         */
        const LocalizedTexts& names() const;
        ///@}

        friend bool operator==(const CodingSystem& lhs, const CodingSystem& rhs) noexcept;

    private:
        CodingSystemId m_id;
        CodingSystemVersion m_version;
        LocalizedTexts m_names;
};

/**
 * @brief Equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case all members equals.
 */
inline bool operator==(const CodingSystem& lhs, const CodingSystem& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.m_id == rhs.m_id &&
           lhs.m_version == rhs.m_version &&
           lhs.m_names == rhs.m_names;
}

/**
 * @brief Not equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const CodingSystem& lhs, const CodingSystem& rhs) noexcept
{
    return !(lhs == rhs);
}

inline const CodingSystemId& CodingSystem::id() const
{
    return m_id;
}

inline const CodingSystemVersion& CodingSystem::version() const
{
    return m_version;
}

inline const LocalizedTexts& CodingSystem::names() const
{
    return m_names;
}

}
}
