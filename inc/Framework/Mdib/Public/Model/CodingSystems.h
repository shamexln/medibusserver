#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{
class CodingSystem;

/**
 * @brief Checks if a \ref CodingSystem instance is a IEEE 11073-10101 coding system.
 * @param codingSystem \ref CodingSystem
 * @return \c true if it is a IEEE 11073-10101 coding system
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP is11073system(const CodingSystem& codingSystem);

/**
 * @brief Compares if two \ref CodingSystem instances references the same coding system.
 * @param lhs first \ref CodingSystem
 * @param rhs second \ref CodingSystem
 * @return \c true in case both references the same coding system
 *         (e.g., optional localized names may differs)
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP referencesSameCodingSystem(const CodingSystem& lhs,
                                                const CodingSystem& rhs);

} /* namespace Mdib */
} /* namespace DFL */
