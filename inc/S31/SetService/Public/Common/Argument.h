#pragma once

#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Utils/Public/Utf8.h>

#include <vector>

namespace S31::SetService
{
/**
 * @brief Holds any simple type (string, integer, double) as defined by XML Schema xsd:anySimpleType.
 * @ingroup S31SetService
 */
using AnySimpleType = DFL::Locale::Utf8;

/**
 * @brief Holds a simple type and an extension as defined by XML Schema msg:Argument
 * @ingroup S31SetService
 */
class Argument
{
    public:
        /**
         * @brief Creates an argument with ArgValue and empty extension.
         * @param anySimpleType The utf8-coded string for the argument
         */
        explicit Argument(AnySimpleType anySimpleType) : m_argValue(std::move(anySimpleType)) {}

        /**
         * @brief Creates an argument with ArgValue with extensions.
         * @param anySimpleType The utf8-coded string for the argument
         * @param extensions A list of extensions
         */
        Argument(AnySimpleType anySimpleType, DFL::Mdib::ExtensionTypes extensions) :
                m_argValue(std::move(anySimpleType)),
                m_extensions(std::move(extensions))
        {}

        /**
         * @brief Returns true if there is an extension which must be understood
         */
        bool hasExtensionsWithMustUnderstand() const
        {
            return std::any_of(m_extensions.cbegin(), m_extensions.cend(), [](const DFL::Mdib::ExtensionType& extension)
            {
                return extension.mustUnderstand();
            });
        }

        const DFL::Mdib::ExtensionTypes& extensions() const
        {
            return m_extensions;
        }

        const AnySimpleType& argValue() const
        {
            return m_argValue;
        }

    private:
        AnySimpleType m_argValue;
        DFL::Mdib::ExtensionTypes m_extensions;
};

inline bool operator ==(const S31::SetService::Argument& lhs, const S31::SetService::Argument& rhs) noexcept
{
    return lhs.argValue() == rhs.argValue() && lhs.extensions() == rhs.extensions();
}

inline bool operator !=(const Argument& lhs, const Argument& rhs) noexcept
{
    return !(lhs==rhs);
}

/**
 * @brief A sequence of \ref Arguments objects.
 * @ingroup S31SetService
 */
using Arguments = std::vector<Argument>;

}
