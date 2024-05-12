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
 * @brief Mutable base type for supporting the BICPES extension model
 * @details @ref DFL::Mdib::ExtensionType "Extensions" enhance objects with
 * any kind of information which cannot be otherwise represented by BICEPS.
 * @note This class is to support types which need mutable data (e.g.
 * \ref DFL::Mdib::BaseDemographics)
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP HasExtensionsMutable
{
    public:
        /**
         * @brief sequence of extensions
         */
        const ExtensionTypes& extensions() const;

        /**
         * @name Setters
         * @brief set a new sequence of extensions
         */
        ///@{
        void extensions(const ExtensionTypes& newExtensions);
        void extensions(ExtensionTypes&& newExtensions);
        ///@}

    private:
        ExtensionTypes m_extensions;
};

inline const ExtensionTypes& HasExtensionsMutable::extensions() const
{
    return m_extensions;
}

inline void HasExtensionsMutable::extensions(const ExtensionTypes& newExtensions)
{
    m_extensions = newExtensions;
}

inline void HasExtensionsMutable::extensions(ExtensionTypes&& newExtensions)
{
    m_extensions = std::move(newExtensions);
}

}
}
}
