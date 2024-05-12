#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace DFL
{
/**
 * @brief Represents valid Object Identifier (OID).
 *
 * An object identifier (OID) is an extensively used identification mechanism
 * for naming any type of object, concept or "thing" with a globally unambiguous
 * name which requires a persistent name. It is based on a hierarchical name
 * structure based on the "OID tree". This naming structure uses a sequence of
 * names, of which the first name identifies a top-level "node" in the OID tree,
 * and the next provides further identification of arcs leading to sub-nodes
 * beneath the top-level, and so on to any depth. A critical feature of this
 * identification mechanism is that it makes OIDs available to a great many
 * organizations and specifications for their own use. See
 * [RFC3061](https://tools.ietf.org/html/rfc3061) for reference. The string
 * provided is parsed on construction and the constructor throws if the string
 * is not a valid OID. Currently only a string containing the [dot
 * notation](http://www.oid-info.com/faq.htm#14) is accepted.
 * [ASN.1](http://www.oid-info.com/faq.htm#17) and [OID
 * IRI](http://www.oid-info.com/faq.htm#iri) notation are currently not
 * accepted.
 *
 * @snippet Utils/Test/UnitTest/TestOid.cpp ValidOids
 * @snippet Utils/Test/UnitTest/TestOid.cpp InvalidOids
 *
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Oid
{
public:
    struct DotNotationTag;
    /**
     * @brief String type for clarifying that an OID in dot notation is
     * expected.
     */
    using DotNotation = StrongTypedef<std::string,
                                      DotNotationTag,
                                      DFL::Skill::TotallyOrdered,
                                      DFL::Skill::Streamable>;
    /**
     * @brief Creates an empty OID.
     *
     * @snippet Utils/Test/UnitTest/TestOid.cpp DefaultCtor
     */
    Oid() = default;
    /**
     * @brief Checks whether given string is a valid OID.
     *
     * An empty string does not throw and such an OID is equal to a default
     * constructed one.
     *
     * @snippet Utils/Test/UnitTest/TestOid.cpp ValidOids
     * @snippet Utils/Test/UnitTest/TestOid.cpp InvalidOids
     *
     * @throws std::runtime_error
     */
    explicit Oid(DotNotation oidsString);
    /**
     * @brief True if underlying strings are the same otherwise false.
     */
    bool equals(const Oid& other) const noexcept;
    /**
     * @brief Returns the OID in form of the dot notation string.
     */
    const DotNotation& dotNotation() const;
    /**
     * @brief Returns true if underlying string is empty.
     *
     * Only possible on default or empty string constructed instances.
     *
     * @snippet Utils/Test/UnitTest/TestOid.cpp Empty
     */
    bool empty() const noexcept;

private:
    void parse();

    DotNotation m_oid{};
};
/**
 * @brief Two oids are compared lexicographically.
 *
 * This is exactly the same as comparing two strings containing the required dot
 * notation.
 *
 * @snippet Utils/Test/UnitTest/TestOid.cpp Relational
 *
 * @ingroup Utils
 * @{
 */
DFL_UTILS_EXPIMP bool operator==(const Oid& lhs, const Oid& rhs);
DFL_UTILS_EXPIMP bool operator!=(const Oid& lhs, const Oid& rhs);
DFL_UTILS_EXPIMP bool operator<(const Oid& lhs, const Oid& rhs);
DFL_UTILS_EXPIMP bool operator<=(const Oid& lhs, const Oid& rhs);
DFL_UTILS_EXPIMP bool operator>(const Oid& lhs, const Oid& rhs);
DFL_UTILS_EXPIMP bool operator>=(const Oid& lhs, const Oid& rhs);
/** @} */
}
