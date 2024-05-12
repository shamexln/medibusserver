#pragma once

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Identifier for Draeger 11073 private coding semantics
 * @ingroup Mdib
 */
const char Draeger11073PrivateCodingSystem[] = "urn:oid:1.3.6.1.4.1.3592.2.1.2.1";

/**
 * @brief Type to report whether private coding semantics are found, and match a Draeger system
 * @ingroup Mdib
 */
enum class PrivateCodingSemantics
{
    /**
     * @brief No information about the semantic of IEEE private codes are available.
     * @details
     * The information has to be looked up in a "larger" context (e.g., MDS production
     * specification instead of VMD production specification). Maybe the
     * vendor documentation instead of MDS production specification provides the semantics.
     */
    NotFound,

    /**
     * @brief Private code semantics are specified but are not know (understandable by Draeger)
     */
    Other,

    /**
     * @brief The private code is a Draeger specific code with Draeger semantics.
     * @details
     * All Draeger devices have the same semantics for the private codes.
     * They are shared across products in a central place (e.g., Doors).
     */
    Draeger
};

}
}
}
