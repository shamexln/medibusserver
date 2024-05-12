#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/PrivateCodingSemantics.h>
#include <Framework/Mdib/Public/Model/Handle.h>

namespace DFL
{
namespace Mdib
{
class Mdib;

/**
 * @brief Stores context information about a \ref DFL::Mdib::CodedValue for semantic comparison.
 *
 * @details
 * Only public IEEE 11073 codes can be compared without context information.
 * For private IEEE 11073 codes the vendor of the private code must be known
 * for semantic comparison of codes.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP CodedValueContext
{
    public:
        /**
         * @brief Constructs a context for Draeger private codes.
         */
        static CodedValueContext draegerPrivateCode();

        /**
         * @brief Constructs a context for IEEE public codes only.
         */
        static CodedValueContext publicIeeeCode();

        /**
         * @brief Constructs a context for unknown private IEEE codes.
         */
        static CodedValueContext unknownPrivateCodes();

        /**
         * @brief Extracts the context from an entity in an MDIB.
         */
        template<class Entity_T>
        CodedValueContext(const Mdib& mdib, const Entity_T& entity);

        /**
         * @brief Access to native value.
         */
        Impl::PrivateCodingSemantics semantics() const;

    private:
        explicit CodedValueContext(Impl::PrivateCodingSemantics);
        Impl::PrivateCodingSemantics m_context;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool operator==(const CodedValueContext& lhs, const CodedValueContext& rhs) noexcept;

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP bool operator!=(const CodedValueContext& lhs, const CodedValueContext& rhs) noexcept;


}
}
