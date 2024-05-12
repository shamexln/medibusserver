#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{

/**
 * @brief Base type for supporting the BICEPS extension model
 * @details @ref DFL::Mdib::ExtensionType "Extensions" enhance objects with
 * any kind of information which cannot be otherwise represented by BICEPS.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP HasExtensions
{
    public:
        /**
         * @brief sequence of extensions
         */
        const ExtensionTypes& extensions() const noexcept;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults \ref HasExtensions::extensions() "Extensions" to empty sequence
         */
        HasExtensions() = default;

        /**
         * @brief Construct with provided extensions
         */
        explicit HasExtensions(ExtensionTypes&& extensions);

        /**
         * @brief Construct with provided extensions
         */
        explicit HasExtensions(const ExtensionTypes& extensions);

        /**
         * @brief Protected dtor.
         * @details
         * This data type is used for composition of members only.
         */
        ~HasExtensions() = default;

        HasExtensions(const HasExtensions&) = default;
        HasExtensions(HasExtensions&&) = default;
        HasExtensions& operator=(const HasExtensions&) = default;
        HasExtensions& operator=(HasExtensions&&) = default;
    private:
        ExtensionTypes m_extensions;
};

inline HasExtensions::HasExtensions(ExtensionTypes&& extensions) :
        m_extensions(std::move(extensions))
{
}

inline HasExtensions::HasExtensions(const ExtensionTypes& extensions) : // NOLINT(modernize-pass-by-value)
        m_extensions(extensions)
{
}

inline const ExtensionTypes& HasExtensions::extensions() const noexcept
{
    return m_extensions;
}

}
}
}
