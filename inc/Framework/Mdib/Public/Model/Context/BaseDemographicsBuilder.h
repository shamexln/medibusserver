#pragma once

#include <memory>
#include <boost/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <Framework/Mdib/Public/Model/Context/BaseDemographics.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Builder with fluent interface for @ref BaseDemographics
 * @ingroup Mdib
 */
class BaseDemographicsBuilder
{
    public:
        /// @brief Typedef to the immutable @ref BaseDemographics
        using BuiltType = BaseDemographics;

        /// @brief Builder based on given immutable @ref BaseDemographics
        explicit BaseDemographicsBuilder(const BaseDemographics& baseDemographics=BaseDemographics());

        /// @brief Builder based on given immutable @ref BaseDemographics
        explicit BaseDemographicsBuilder(const DFL::NotNull<SharedPtr<BaseDemographics>>& baseDemographics);

        /// @brief Overwrite all values with given immutable @ref BaseDemographics
        BaseDemographicsBuilder& operator=(const BaseDemographics& baseDemographics);

        /// @brief Explicit conversion to immutable @ref BaseDemographics
        BaseDemographics build() const;

        /// @brief Test whether the builder differs from the immutable @ref BaseDemographics
        bool isChanged(const BaseDemographics& base) const;

        /// @brief Setter for givenName
        /// @{
        BaseDemographicsBuilder& givenName(Locale::Utf8 givenName);
        /// @}

        /// @brief Setter for middleName
        /// @{
        BaseDemographicsBuilder& middleName(Locale::Utf8 middleName);
        /// @}

        /// @brief Setter for familyName
        /// @{
        BaseDemographicsBuilder& familyName(Locale::Utf8 familyName);
        /// @}

        /// @brief Setter for birthName
        /// @{
        BaseDemographicsBuilder& birthName(Locale::Utf8 birthName);
        /// @}

        /// @brief Setter for title
        /// @{
        BaseDemographicsBuilder& title(Locale::Utf8 title);
        /// @}

        /// @brief Setter for extensions
        /// @{
        BaseDemographicsBuilder& extensions(const ExtensionTypes& extensions);
        BaseDemographicsBuilder& extensions(ExtensionTypes&& extensions);
        /// @}

        /// @brief Getter for givenName
        /// @{
        Locale::Utf8& givenName();
        Locale::Utf8 givenName() const;
        /// @}

        /// @brief Getter for middleName
        /// @{
        Locale::Utf8& middleName();
        Locale::Utf8 middleName() const;
        /// @}

        /// @brief Getter for familyName
        /// @{
        Locale::Utf8& familyName();
        Locale::Utf8 familyName() const;
        /// @}

        /// @brief Getter for birthName
        /// @{
        Locale::Utf8& birthName();
        Locale::Utf8 birthName() const;
        /// @}

        /// @brief Getter for title
        /// @{
        Locale::Utf8& title();
        Locale::Utf8 title() const;
        /// @}

        /// @brief Getter for extensions
        /// @{
        ExtensionTypes& extensions();
        const ExtensionTypes& extensions() const;
        /// @}

    private:
        Locale::Utf8 m_givenName;
        Locale::Utf8 m_middleName;
        Locale::Utf8 m_familyName;
        Locale::Utf8 m_birthName;
        Locale::Utf8 m_title;
        ExtensionTypes m_extensions;
};

/**
 * @brief Equal operator compares all members
 * @ingroup Mdib
 */
/// @{
DFL_MDIB_EXPIMP bool operator==(const BaseDemographicsBuilder& lhs, const BaseDemographicsBuilder& rhs);
DFL_MDIB_EXPIMP bool operator==(const BaseDemographicsBuilder& lhs, const BaseDemographics& rhs);
bool operator==(const BaseDemographics& lhs, const BaseDemographicsBuilder& rhs);
/// @}

/**
 * @brief Not equal operator compares all members
 * @ingroup Mdib
 */
/// @{
bool operator!=(const BaseDemographicsBuilder& lhs, const BaseDemographicsBuilder& rhs);
bool operator!=(const BaseDemographics& lhs, const BaseDemographicsBuilder& rhs);
bool operator!=(const BaseDemographicsBuilder& lhs, const BaseDemographics& rhs);
/// @}

/**
 * @brief Factory function to create %Builder based on given immutable @ref BaseDemographics
 * @ingroup Mdib
 */
/// @{
BaseDemographicsBuilder getBuilder(const BaseDemographics& baseDemographics);
BaseDemographicsBuilder getBuilder(const DFL::NotNull<SharedPtr<BaseDemographics>>& baseDemographics);
/// @}

/**
 * @brief Helper function throws runtime_error in case of a not equal member
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP void assertEqual(const BaseDemographics& lhs, const BaseDemographics& rhs);

inline BaseDemographicsBuilder::BaseDemographicsBuilder(const BaseDemographics& baseDemographics) :
    m_givenName(baseDemographics.givenName()),
    m_middleName(baseDemographics.middleName()),
    m_familyName(baseDemographics.familyName()),
    m_birthName(baseDemographics.birthName()),
    m_title(baseDemographics.title()),
    m_extensions(baseDemographics.extensions())
{
}

inline BaseDemographicsBuilder::BaseDemographicsBuilder(const DFL::NotNull<SharedPtr<BaseDemographics>>& baseDemographics) :
    m_givenName(baseDemographics->givenName()),
    m_middleName(baseDemographics->middleName()),
    m_familyName(baseDemographics->familyName()),
    m_birthName(baseDemographics->birthName()),
    m_title(baseDemographics->title()),
    m_extensions(baseDemographics->extensions())
{
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::operator=(const BaseDemographics& baseDemographics)
{
    m_givenName = baseDemographics.givenName();
    m_middleName = baseDemographics.middleName();
    m_familyName = baseDemographics.familyName();
    m_birthName = baseDemographics.birthName();
    m_title = baseDemographics.title();
    m_extensions = baseDemographics.extensions();
    return *this;
}

inline BaseDemographics BaseDemographicsBuilder::build() const
{
    // NOLINTNEXTLINE(modernize-return-braced-init-list)
    return BaseDemographics(m_givenName, m_middleName, m_familyName, m_birthName, m_title, m_extensions);
}

inline bool BaseDemographicsBuilder::isChanged(const BaseDemographics& base) const
{
    return *this != base;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::givenName(Locale::Utf8 givenName)
{
    m_givenName = givenName;
    return *this;
}

inline Locale::Utf8& BaseDemographicsBuilder::givenName()
{
    return m_givenName;
}

inline Locale::Utf8 BaseDemographicsBuilder::givenName() const
{
    return m_givenName;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::middleName(Locale::Utf8 middleName)
{
    m_middleName = middleName;
    return *this;
}

inline Locale::Utf8& BaseDemographicsBuilder::middleName()
{
    return m_middleName;
}

inline Locale::Utf8 BaseDemographicsBuilder::middleName() const
{
    return m_middleName;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::familyName(Locale::Utf8 familyName)
{
    m_familyName = familyName;
    return *this;
}

inline Locale::Utf8& BaseDemographicsBuilder::familyName()
{
    return m_familyName;
}

inline Locale::Utf8 BaseDemographicsBuilder::familyName() const
{
    return m_familyName;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::birthName(Locale::Utf8 birthName)
{
    m_birthName = birthName;
    return *this;
}

inline Locale::Utf8& BaseDemographicsBuilder::birthName()
{
    return m_birthName;
}

inline Locale::Utf8 BaseDemographicsBuilder::birthName() const
{
    return m_birthName;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::title(Locale::Utf8 title)
{
    m_title = title;
    return *this;
}

inline Locale::Utf8& BaseDemographicsBuilder::title()
{
    return m_title;
}

inline Locale::Utf8 BaseDemographicsBuilder::title() const
{
    return m_title;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::extensions(const ExtensionTypes& extensions)
{
    m_extensions = extensions;
    return *this;
}

inline BaseDemographicsBuilder& BaseDemographicsBuilder::extensions(ExtensionTypes&& extensions)
{
    m_extensions = std::move(extensions);
    return *this;
}

inline ExtensionTypes& BaseDemographicsBuilder::extensions()
{
    return m_extensions;
}

inline const ExtensionTypes& BaseDemographicsBuilder::extensions() const
{
    return m_extensions;
}

inline bool operator==(const BaseDemographics& lhs, const BaseDemographicsBuilder& rhs)
{
    return rhs == lhs;
}

inline bool operator!=(const BaseDemographicsBuilder& lhs, const BaseDemographicsBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const BaseDemographics& lhs, const BaseDemographicsBuilder& rhs)
{
    return !(lhs == rhs);
}

inline bool operator!=(const BaseDemographicsBuilder& lhs, const BaseDemographics& rhs)
{
    return !(lhs == rhs);
}

inline BaseDemographicsBuilder getBuilder(const BaseDemographics& baseDemographics)
{
    return BaseDemographicsBuilder(baseDemographics);
}

inline BaseDemographicsBuilder getBuilder(const DFL::NotNull<SharedPtr<BaseDemographics>>& baseDemographics)
{
    return BaseDemographicsBuilder(baseDemographics);
}

}
}
