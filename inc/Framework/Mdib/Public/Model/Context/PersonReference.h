#pragma once

#include <Framework/Mdib/Public/Model/Context/BaseDemographics.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief A reference to an identifiable person with a name.
 * @ingroup Mdib
 */
class PersonReference: public Impl::HasExtensions
{
    public:
        /**
         * @brief Default constructor without identification, name and extentions
         */
        PersonReference() = default;

        /**
         * @brief Constructor
         */
        PersonReference(const InstanceIdentifiers& identification,
                        const boost::optional<BaseDemographics>& name,
                        ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The list of identifiers for the person.
         */
        const InstanceIdentifiers& identification() const;

        /**
         * @brief Name of the person.
         */
        const boost::optional<BaseDemographics>& name() const;

    private:
        InstanceIdentifiers m_identification;
        boost::optional<BaseDemographics> m_name;
};

/**
 * @brief Equal operator for \ref PersonReference.
 */
DFL_MDIB_EXPIMP bool operator==(const PersonReference& lhs, const PersonReference& rhs);

/**
 * @brief Not-equal operator for \ref PersonReference.
 */
DFL_MDIB_EXPIMP bool operator!=(const PersonReference& lhs, const PersonReference& rhs);

inline PersonReference::PersonReference(const InstanceIdentifiers& identification, // NOLINT(modernize-pass-by-value)
                                        const boost::optional<BaseDemographics>& name, // NOLINT(modernize-pass-by-value)
                                        ExtensionTypes extensions):
        Impl::HasExtensions(std::move(extensions)),
        m_identification(identification),
        m_name(name)
{
}

inline const InstanceIdentifiers& PersonReference::identification() const
{
    return m_identification;
}

inline const boost::optional<BaseDemographics>& PersonReference::name() const
{
    return m_name;
}

} /* namespace Mdib */
} /* namespace DFL */
