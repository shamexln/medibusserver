#pragma once
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/CodingSystem.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <boost/optional.hpp>

namespace DFL::Mdib
{
/**
 * @brief Builder with fluent interface for @ref CodedValue
 * @ingroup Mdib
 */
class CodedValueBuilder
{
    public:
    /// @brief Builder based on given immutable @ref CodedValue
    explicit CodedValueBuilder(const CodedValue& codedValue);

    /// @brief Builder based on given immutable @ref CodedValue
    explicit CodedValueBuilder(const DFL::NotNull<SharedPtr<CodedValue>>& codedValue);

    /// @brief Overwrite all values with given immutable @ref CodedValue
    CodedValueBuilder& operator=(const CodedValue& codedValue);

    /// @brief Explicit conversion to immutable @ref CodedValue
    CodedValue build() const;

    /// @brief Test whether the builder differs from the immutable @ref CodedValue
    bool isChanged(const CodedValue& base) const;

    /// @brief Setter for CodingSystem
    /// @{
    CodedValueBuilder& codingSystem(const CodingSystem& codingSystem);
    CodedValueBuilder& codingSystem(CodingSystem&& codingSystem);
    
    /// @brief Setter for CodeId
    /// @{
    CodedValueBuilder& code(const CodeId& code);
    CodedValueBuilder& code(CodeId&& code);
    /// @}

    /// @brief Setter for ConceptDescription
    /// @{
    CodedValueBuilder& conceptDescription(const LocalizedTexts& conceptDescription);
    CodedValueBuilder& conceptDescription(LocalizedTexts&& conceptDescription);
    /// @}

    /// @brief Setter for SymbolicCodeName
    /// @{
    CodedValueBuilder& symbolicCodeName(const Locale::Utf8& symbolicCodeName);
    CodedValueBuilder& symbolicCodeName(Locale::Utf8&& symbolicCodeName);
    /// @}

    /// @brief Setter for CodedValueTranslations
    /// @{
    CodedValueBuilder& translations(const CodedValueTranslations& translations);
    CodedValueBuilder& translations(CodedValueTranslations&& translations);
    /// @}

    /// @brief Setter for extensions
    /// @{
    CodedValueBuilder& extensions(const ExtensionTypes& extensions);
    CodedValueBuilder& extensions(ExtensionTypes&& extensions);
    /// @}

    /// @brief Convenience function to add a single translation to the list of translations
    /// @{
    CodedValueBuilder& addTranslation(const CodedValueTranslation translation);
    CodedValueBuilder& clearTranslations();
    /// @}
    //------------------------
    /// @brief Getter for CodingSystem
    /// @{
    CodingSystem& codingSystem();
    const CodingSystem& codingSystem() const;
    
    /// @brief Getter for CodeId
    /// @{
    CodeId& code();
    const CodeId& code() const;
    /// @}

    /// @brief Getter for ConceptDescription
    /// @{
    LocalizedTexts& conceptDescription();
    const LocalizedTexts& conceptDescription() const;
    /// @}

    /// @brief Getter for SymbolicCodeName
    /// @{
    Locale::Utf8& symbolicCodeName();
    const Locale::Utf8& symbolicCodeName() const;
    /// @}

    /// @brief Getter for CodedValueTranslations
    /// @{
    CodedValueTranslations& translations();
    const CodedValueTranslations& translations() const;
    /// @}

    /// @brief Getter for extensions
    /// @{
    ExtensionTypes& extensions();
    const ExtensionTypes& extensions() const;
    /// @}


    private:
        CodingSystem m_codingSystem;
        CodeId m_code;
        LocalizedTexts m_conceptDescription;
        Locale::Utf8 m_symbolicCodeName;
        CodedValueTranslations m_translations;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const CodedValueBuilder& lhs, const CodedValueBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const CodedValueBuilder& lhs, const CodedValue& rhs);
bool operator==(const CodedValue& lhs, const CodedValueBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
bool operator!=(const CodedValueBuilder& lhs, const CodedValueBuilder& rhs);
bool operator!=(const CodedValue& lhs, const CodedValueBuilder& rhs);
bool operator!=(const CodedValueBuilder& lhs, const CodedValue& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref CodedValue
 * @ingroup Mdib
 */
/// @{
CodedValueBuilder getBuilder(const CodedValue& codedValue);
CodedValueBuilder getBuilder(const DFL::NotNull<SharedPtr<CodedValue>>& codedValue);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const CodedValue& lhs, const CodedValue& rhs);

inline CodedValueBuilder::CodedValueBuilder(const CodedValue& codedValue)
        : m_codingSystem(codedValue.codingSystem())
        , m_code(codedValue.code())
        , m_conceptDescription(codedValue.conceptDescription())
        , m_symbolicCodeName(codedValue.symbolicCodeName())
        , m_translations(codedValue.translations())
        , m_extensions(codedValue.extensions())
{
}

inline CodedValueBuilder::CodedValueBuilder(const DFL::NotNull<SharedPtr<CodedValue>>& codedValue)
        : m_codingSystem(codedValue->codingSystem())
        , m_code(codedValue->code())
        , m_conceptDescription(codedValue->conceptDescription())
        , m_symbolicCodeName(codedValue->symbolicCodeName())
        , m_translations(codedValue->translations())
        , m_extensions(codedValue->extensions())
{
}

inline CodedValueBuilder& CodedValueBuilder::operator=(const CodedValue& codedValue)
{
    m_codingSystem = codedValue.codingSystem();
    m_code = codedValue.code();
    m_conceptDescription = codedValue.conceptDescription();
    m_symbolicCodeName = codedValue.symbolicCodeName();
    m_translations = codedValue.translations();
    m_extensions = codedValue.extensions();
    return *this;
}

inline CodedValue CodedValueBuilder::build() const
{
     return CodedValue{m_codingSystem, m_code, m_conceptDescription, m_symbolicCodeName, m_translations, m_extensions};
}

inline CodedValueBuilder& CodedValueBuilder::codingSystem(const CodingSystem& codingSystem)
{
    m_codingSystem = codingSystem;
    return *this;
}

inline CodedValueBuilder& CodedValueBuilder::codingSystem(CodingSystem&& codingSystem)
{
    m_codingSystem = codingSystem;
    return *this;
}

inline CodingSystem& CodedValueBuilder::codingSystem()
{
    return m_codingSystem;
}

inline const CodingSystem& CodedValueBuilder::codingSystem() const
{
    return m_codingSystem;
}

inline CodedValueBuilder& CodedValueBuilder::code(const CodeId& code)
{
    m_code = code;
    return *this;
}

inline CodedValueBuilder& CodedValueBuilder::code(CodeId&& code)
{
    m_code = code;
    return *this;
}

inline CodeId& CodedValueBuilder::code()
{
    return m_code;
}

inline const CodeId& CodedValueBuilder::code() const
{
    return m_code;
}

inline CodedValueBuilder& CodedValueBuilder::conceptDescription(const LocalizedTexts& conceptDescription)
{
    m_conceptDescription = conceptDescription;
    return *this;
}

inline CodedValueBuilder& CodedValueBuilder::conceptDescription(LocalizedTexts&& conceptDescription)
{
    m_conceptDescription = conceptDescription;
    return *this;
}

inline LocalizedTexts& CodedValueBuilder::conceptDescription()
{
    return m_conceptDescription;
}

inline const LocalizedTexts& CodedValueBuilder::conceptDescription() const
{
    return m_conceptDescription;
}

inline CodedValueBuilder& CodedValueBuilder::symbolicCodeName(const Locale::Utf8& symbolicCodeName)
{
    m_symbolicCodeName = symbolicCodeName;
    return *this;
}

inline CodedValueBuilder& CodedValueBuilder::symbolicCodeName(Locale::Utf8&& symbolicCodeName)
{
    m_symbolicCodeName = symbolicCodeName;
    return *this;
}

inline Locale::Utf8& CodedValueBuilder::symbolicCodeName()
{
    return m_symbolicCodeName;
}

inline const Locale::Utf8& CodedValueBuilder::symbolicCodeName() const
{
    return m_symbolicCodeName;
}

inline CodedValueBuilder& CodedValueBuilder::translations(const CodedValueTranslations& translations)
{
    m_translations = translations;
    return *this;
}

inline CodedValueBuilder& CodedValueBuilder::translations(CodedValueTranslations&& translations)
{
    m_translations = translations;
    return *this;
}

inline CodedValueTranslations& CodedValueBuilder::translations()
{
    return m_translations;
}

inline const CodedValueTranslations& CodedValueBuilder::translations() const
{
    return m_translations;
}

inline CodedValueBuilder& CodedValueBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline CodedValueBuilder& CodedValueBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& CodedValueBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& CodedValueBuilder::extensions() const
{
    return m_extensions;
}

inline  CodedValueBuilder& CodedValueBuilder::addTranslation(const CodedValueTranslation translation)
{
    m_translations.push_back(translation);
    return *this;
}

inline  CodedValueBuilder& CodedValueBuilder::clearTranslations()
{
    m_translations.clear();
    return *this;
}

inline bool operator==(const CodedValue& lhs, const CodedValueBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const CodedValueBuilder& lhs, const CodedValueBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const CodedValue& lhs, const CodedValueBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const CodedValueBuilder& lhs, const CodedValue& rhs)
{
    return !(lhs == rhs);
}

inline CodedValueBuilder getBuilder(const CodedValue& codedValue)
{
    return CodedValueBuilder(codedValue);
}

inline CodedValueBuilder getBuilder(const DFL::NotNull<SharedPtr<CodedValue>>& codedValue)
{
    return CodedValueBuilder(codedValue);
}

} // namespace DFL::Mdib