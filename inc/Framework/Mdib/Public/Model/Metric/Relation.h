#pragma once

#include <Framework/Mdib/Public/Model/Metric/Kind.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <utility>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Allows the modeling of relationships between a metric and other containment tree entries.
 * @details Related containment tree entries are defined in \ref entries, whereby the flavor of a relationship can be set up in \ref kind.
 * The cardinality of Relation is zero or more in order to express relations of different flavors for the same metric
 *
 * \note Example: some settings of high frequency cutting devices cause changes in measurements (e.g., current form can influences the
 * maximum emitted power). If such a setting is controllable by external means, presumably the SERVICE CONSUMER wants to be able to gain
 * knowledge of affected measurements, which might be then accessed through the Relation element.
 * @ingroup Mdib
 */
class Relation: public Impl::HasExtensions
{
    public:
        /**
         * @brief Constructor
         */
        Relation(Kind kind,
                 Handles entries,
                 const boost::optional<CodedValue>& code,
                 const boost::optional<InstanceIdentifier>& identification,
                 ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Kind specifies the relationship between the m and referenced containment tree entries.
         * @details Referenced containment tree entries are defined in \ref entries
         */
        Kind kind() const;

        /**
         * @brief Kind specifies the relationship between the m and referenced containment tree entries.
         * @details Referenced containment tree entries are defined in \ref entries
         */
        const Handles& entries() const;

        /**
         * @brief allows to semantically describe the relationship between the metric and the list of related containment
         * tree entries defined in \ref entries.
         */
        const boost::optional<CodedValue>& code() const;

        /**
         * @brief Allow relations to be grouped by instance identifiers.
         * @details E.g. a service provider can group sets of recommendations or presettings
         * in order to allow easy identification.
         */
        const boost::optional<InstanceIdentifier>& identification() const;

    private:
        Kind m_kind;
        Handles m_entries;
        boost::optional<CodedValue> m_code;
        boost::optional<InstanceIdentifier> m_identification;
};

/**
 * @brief Sequence of \ref Relation.
 * @ingroup Mdib
 */
using Relations = std::vector<Relation>;

inline Relation::Relation(Kind kind,
                   Handles entries,
                   const boost::optional<CodedValue>& code, // NOLINT(modernize-pass-by-value)
                   const boost::optional<InstanceIdentifier>& identification, // NOLINT(modernize-pass-by-value)
                   ExtensionTypes extensions):
        Impl::HasExtensions(std::move(extensions)),
        m_kind(kind),
        m_entries(std::move(entries)),
        m_code(code),
        m_identification(identification)
{
}

inline Kind Relation::kind() const
{
    return m_kind;
}

inline const Handles& Relation::entries() const
{
    return m_entries;
}

inline const boost::optional<CodedValue>& Relation::code() const
{
    return m_code;
}

inline const boost::optional<InstanceIdentifier>& Relation::identification() const
{
    return m_identification;
}

/**
 * @brief Equal operator compares all members.
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case all members equals.
 */
inline bool operator ==(const Relation& lhs, const Relation& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }

    return lhs.kind() == rhs.kind()
        && lhs.entries() == rhs.entries()
        && lhs.code() == rhs.code()
        && lhs.identification() == rhs.identification()
        && lhs.extensions() == rhs.extensions();
}

/**
 * @brief Not equal operator compares all members.
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const Relation& lhs, const Relation& rhs) noexcept
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
