#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/QName.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Container for a list of \ref DFL::QName "XML QNames".
 * @ingroup S31SdcCommon
 */
using QNameList = std::vector<DFL::QName>;

/**
 * @brief Compares two @ref QNameList "lists of qualified names" in terms of semantic equality.
 * @details Two QNameLists are considered semantically equal iff each @ref DFL::QName "QName" in lhs is
 *          @ref containsSemantically() "semantically contained" in rhs and vice versa.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP bool isSemanticallyEqual(const QNameList& lhs, const QNameList& rhs);

/**
 * @brief Checks whether lhs is a semantical subset of rhs.
 * @details lhs is considered a semantical subset of rhs, iff each @ref DFL::QName "QName" in lhs is
 *          @ref containsSemantically() "semantically contained" in rhs.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP bool isSemanticallySubsetOf(const QNameList& lhs, const QNameList& rhs);

/**
 * @brief Checks whether lhs contains rhs semantically.
 * @details lhs is considered to contain rhs semantically, iff there exists a @ref DFL::QName "QName" in lhs
 *          that @ref DFL::isSemanticallyEqual() "is semantically equal" to rhs.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP bool containsSemantically(const QNameList& lhs, const DFL::QName& rhs);

}
