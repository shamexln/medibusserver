#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/PrivateCodingSemantics.h>
#include <Framework/Mdib/Public/Model/CodeId.h>
#include <Framework/Mdib/Public/Model/CodingSystem.h>

namespace DFL
{
namespace Mdib
{
class Mdib;
class CodedValue;
class CodedValueContext;

/**
 * @brief Context for comparing the semantics of \ref DFL::Mdib::CodedValue
 *
 * @details
 * Two %CodedValues are nominally equal in case that
 * - the coding system, code and coding system version matches or
 * - a translation in one %CodedValue is equal to the other %CodedValue, or one of its translations.
 *
 * However, in general, assumptions cannot be made about private codes in ISO/IEEE 11073, or
 * unknown coding systems.  Only public ISO/IEEE 11073 will compare equal, unless it can be inferred
 * (via search for \ref DFL::Mdib::ProductionSpecification) that ISO/IEEE 11073 private codes have
 * Draeger private code semantics.
 *
 * @note
 * Coding system name and description (both LocalizedText) are not used for comparison.
 *
 * @ingroup MDIB
 */
class DFL_MDIB_EXPIMP CodedValueSemantics
{
    public:
        /**
         * @brief Default constructor
         * @details Private ISO/IEEE 11073 codes or unknown coding systems will return not equal.
         */
        CodedValueSemantics() = default;

        /**
         * @brief Construct in the context of an \ref DFL::Mdib::Mdib and %Entity.
         * @details Determines from the %Mdib if the %Entity is within the scope of
         * Draeger 11073 private code semantics, allowing for comparison of ISO/IEEE 11073 private codes.
         */
        template<class Entity>
        CodedValueSemantics(const Mdib& contextMdib, const Entity& contextEntity);

        /**
         * @brief Test if two coded values are semantically equal in the current context.
         */
        bool isEqual(const CodedValue& lhs, const CodedValue& rhs) const;

    private:
        Impl::PrivateCodingSemantics m_private11073Coding = Impl::PrivateCodingSemantics::NotFound;

};

/**
 * @brief Test if two coded values are semantically equal in the default \ref CodedValueSemantics context.
 * @ingroup MDIB
 */
DFL_MDIB_EXPIMP bool isSemanticallyEqual(const CodedValue& lhs, const CodedValue& rhs);

/**
 * @brief Test if two coded values are semantically equal in the context of an \ref DFL::Mdib::Mdib and %Entity.
 * @ingroup MDIB
 */
template<class Entity>
bool isSemanticallyEqual(const CodedValue& lhs,
                         const CodedValue& rhs,
                         const Mdib& contextMdib,
                         const Entity& contextEntity)
{
    CodedValueSemantics const context(contextMdib, contextEntity);
    return context.isEqual(lhs, rhs);
}

/**
 * @brief Checks semantically equality for \ref DFL::Mdib::CodedValue "CodeValues"
 * base on their \ref DFL::Mdib::CodedValueContext "CodedValueContext".
 *
 * @details Also evaluates the translations of the CodedValues for semantic equality.
 * It is sufficient if there is any match.
 *
 * @param lhsCode    First CodedValue.
 * @param lhsContext First context for first CodedValue.
 * @param rhsCode    Second CodedValue to compare with.
 * @param rhsContext Second context belonging to second CodedValue.
 * @return \c true in case the semantic is equal.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool isSemanticallyEqual(
        const CodedValue& lhsCode,
        const CodedValueContext& lhsContext,
        const CodedValue& rhsCode,
        const CodedValueContext& rhsContext);

/**
 * @brief Test if the \ref DFL::Mdib::CodingSystem and \ref DFL::Mdib::CodeId indicate an ISO/IEEE 11073 public code.
 * @ingroup MDIB
 */
DFL_MDIB_EXPIMP bool isPublicIeee11073Code(const CodingSystem& system, const CodeId& code);

/**
 * @brief Test if the \ref DFL::Mdib::CodedValue or one of its translations indicate an ISO/IEEE 11073 public code.
 * @ingroup MDIB
 */
DFL_MDIB_EXPIMP bool isPublicIeee11073Code(const CodedValue& cv);

/**
 * @brief Extract ISO/IEEE 11073 code iff one is available.
 * @ingroup MDIB
 */
DFL_MDIB_EXPIMP boost::optional<CodeId> ieee11073CodeId(const CodedValue& cv);

}
}
