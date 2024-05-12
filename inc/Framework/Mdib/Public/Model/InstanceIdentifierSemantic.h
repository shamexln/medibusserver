#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Checks validity of \ref DFL::Mdib::InstanceIdentifier root member.
 * @details
 * Check is based on Modular requirement PTSR_30599:
 * > An SDC PARTICIPANT SHALL limit values of pm:InstanceIdentifier/\@Root
 * > to those matching the form scheme ":" hier-part
 * > as defined in section 3 of RFC 3986.
 * > The only exception from this is the "biceps.uri.unk"
 * > and "sdc.ctxt.loc.detail" value.
 *
 * In other word no query and fragment part in URLs.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool validInstanceIdentifierRoot(const InstanceIdentifier& ii);

/**
 * @brief Whether two \ref DFL::Mdib::InstanceIdentifier are the same.
 * @details
 * Return type of a ReferencesSameInstance call.
 * @ingroup Mdib
 */
enum class ReferencesSameInstance
{
    /**
     * @brief Reference same instance due to semantic match.
     */
    True,

    /**
     * @brief No semantic match possible with given identifiers.
     */
    False,

    /**
     * @brief No statement regarding matching semantics possible.
     * @details
     * This happens in case of missing context information.
     */
    Unknown
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ReferencesSameInstance, (True)(False)(Unknown))

/**
 * @brief Checks for same instance identification.
 * @details
 * The check only takes care of matching root and extension by ignoring
 * "meta data" such as identifier type or localized names.
 * It does not match identifiers from different roots for example.
 *
 * In case it is not possible to make a decision (because information
 * about a root or null-flavors is missing) the result is
 * \ref ReferencesSameInstance::Unknown.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP ReferencesSameInstance referencesSameInstance(
    const InstanceIdentifier& lhs,
    const InstanceIdentifier& rhs);

/**
 * @brief Checks for same instance identification.
 * @details
 * The check succeeds in case there is one instance identifier match.
 *
 * The check only takes care of matching root and extension by ignoring
 * "meta data" such as identifier type or localized names.
 * It does not match identifiers from different roots for example.
 *
 * In case it is not possible to make a decision (because information
 * about a root or null-flavors is missing) the result is
 * \ref ReferencesSameInstance::Unknown.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP ReferencesSameInstance referencesSameInstance(
    const InstanceIdentifiers& lhs,
    const InstanceIdentifier& rhs);

/**
 * @brief Checks for same instance identification.
 * @details
 * The check succeeds in case there is one instance identifier match.
 *
 * The check only takes care of matching root and extension by ignoring
 * "meta data" such as identifier type or localized names.
 * It does not match identifiers from different roots for example.
 *
 * In case it is not possible to make a decision (because information
 * about a root or null-flavors is missing) the result is
 * \ref ReferencesSameInstance::Unknown.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP ReferencesSameInstance referencesSameInstance(
    const InstanceIdentifier& lhs,
    const InstanceIdentifiers& rhs);

/**
 * @brief Checks for same instance identification.
 * @details
 * The check succeeds in case there is one instance identifier match.
 *
 * The check only takes care of matching root and extension by ignoring
 * "meta data" such as identifier type or localized names.
 * It does not match identifiers from different roots for example.
 *
 * In case it is not possible to make a decision (because information
 * about a root or null-flavors is missing) the result is
 * \ref ReferencesSameInstance::Unknown.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP ReferencesSameInstance referencesSameInstance(
    const InstanceIdentifiers& lhs,
    const InstanceIdentifiers& rhs);

}
}
