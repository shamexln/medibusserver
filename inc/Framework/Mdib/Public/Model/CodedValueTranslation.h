#pragma once

#include <Framework/Config/Public/Attributes.h>
#include <Framework/Mdib/Public/Model/CodeId.h>
#include <Framework/Mdib/Public/Model/CodingSystem.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief %CodedValueTranslation is used to model translations of a coded value of BICEPS.
 *
 * @ingroup Mdib
 */
class CodedValueTranslation: public Impl::HasExtensions
{
    public:
        /**
         * @brief Constructs a code within a specific coding system.
         * @deprecated Please use \ref DFL::Mdib::CodedValueTranslation(const CodingSystem&, const CodeId&) instead.
         * @param codingSystem Coding system for the code, only the id and version are used.
         * @param code Code from coding system.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant by using DFL::Mdib::CodeId for second argument")
        CodedValueTranslation(const CodingSystem& codingSystem, const Locale::Utf8& code);

        /**
         * @brief Constructs a code within a specific coding system id and version.
         * @deprecated Please use \ref DFL::Mdib::CodedValueTranslation(const CodingSystemId&, const CodingSystemVersion&, const CodeId&) instead.
         * @param codingSystemId Coding system identifier for the code.
         * @param codingSystemVersion Coding system version for the code.
         * @param code Code from coding system.
         */
        DFL_ATTRIBUTE_DEPRECATED("Replace by type safe variant by using DFL::Mdib::CodeId for last argument")
        CodedValueTranslation(const CodingSystemId& codingSystemId, const CodingSystemVersion& codingSystemVersion, const Locale::Utf8& code);

        /**
         * @brief Constructs a code within a specific coding system.
         * @param codingSystem Coding system for the code, only the id and version are used.
         * @param code Code from coding system.
         * @param extensions \ref DFL::Mdib::ExtensionType "Extensions" of any kind
         */
        CodedValueTranslation(const CodingSystem& codingSystem, CodeId code, ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Constructs a code within a specific coding system id and version.
         * @param codingSystemId Coding system identifier for the code.
         * @param codingSystemVersion Coding system version for the code.
         * @param code Code from coding system.
         * @param extensions \ref DFL::Mdib::ExtensionType "Extensions" of any kind
         */
        CodedValueTranslation(const CodingSystemId& codingSystemId, const CodingSystemVersion& codingSystemVersion, CodeId code, ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Provides a coding system from the coded value translation.
         * @return A coding system from given coded value translation information (i.e., coding system id and coding system version only)
         */
        const CodingSystem& codingSystem() const;

        /**
         * @brief Provide the code identifier.
         * @return The code identifier.
         */
        const CodeId& code() const;

        friend bool operator==(const CodedValueTranslation &lhs, const CodedValueTranslation &rhs) noexcept;

        friend bool operator!=(const CodedValueTranslation &lhs, const CodedValueTranslation &rhs) noexcept;

    private:
        CodingSystem m_codingSystem;
        CodeId m_code;
};

inline CodedValueTranslation::CodedValueTranslation(const CodingSystem& codingSystem, const Locale::Utf8& code) :
    m_codingSystem(CodingSystem(codingSystem.id(), codingSystem.version())),
    m_code(CodeId(code))
{
}

inline CodedValueTranslation::CodedValueTranslation(const CodingSystemId& codingSystemId,
                                                    const CodingSystemVersion& codingSystemVersion,
                                                    const Locale::Utf8& code) :
        m_codingSystem(CodingSystem(codingSystemId, codingSystemVersion)),
        m_code(CodeId(code))
{
}

inline CodedValueTranslation::CodedValueTranslation(const CodingSystem& codingSystem,
                                                    CodeId code,
                                                    ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_codingSystem(CodingSystem(codingSystem.id(), codingSystem.version())),
        m_code(std::move(code))
{
}

inline CodedValueTranslation::CodedValueTranslation(const CodingSystemId& codingSystemId,
                                                    const CodingSystemVersion& codingSystemVersion,
                                                    CodeId code,
                                                    ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_codingSystem(CodingSystem(codingSystemId, codingSystemVersion)),
        m_code(std::move(code))
{
}

inline const CodingSystem& CodedValueTranslation::codingSystem() const
{
    return m_codingSystem;
}

inline const CodeId& CodedValueTranslation::code() const
{
    return m_code;
}

/**
 * @brief Comparison operator for \ref CodedValueTranslation.
 */
inline bool operator==(const CodedValueTranslation &lhs, const CodedValueTranslation &rhs) noexcept
{
    return lhs.m_code == rhs.m_code && lhs.m_codingSystem == rhs.m_codingSystem && lhs.extensions() == rhs.extensions();
}

/**
 * @brief Comparison operator for \ref CodedValueTranslation.
 */
inline bool operator!=(const CodedValueTranslation &lhs, const CodedValueTranslation &rhs) noexcept
{
    return !(lhs == rhs);
}

/**
 * @brief Sequence of \ref CodedValueTranslation objects (as used in \ref CodedValue).
 * @ingroup Mdib
 */
using CodedValueTranslations = std::vector<CodedValueTranslation>;

} /* namespace Mdib */
} /* namespace DFL */
