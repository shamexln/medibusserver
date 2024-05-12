#pragma once

#include <Framework/Mdib/Public/Model/AbstractMultiState.h>
#include <Framework/Mdib/Public/Model/Context/ContextAssociation.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Mdib/Public/Model/VersionCounter.h>
#include <Framework/Mdib/Private/CompilerGenerated.h>

#include <boost/optional.hpp>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Context state that specify that the \ref Mds is able to provide spatial information.
 * @ingroup Mdib
 */
class AbstractContextState: public AbstractMultiState
{
    DFL_MDIB_IMMUTABLE(AbstractContextState)

    public:
        /**
         * @brief Association of a context.
         */
        ContextAssociation contextAssociation() const;

        /**
         * @brief Points to the version of an MDIB when a binding of the context state to an \ref Mds starts.
         * @return MDIB version number or \c boost::none if undefined.
         */
        boost::optional<VersionCounter> bindingMdibVersion() const;

        /**
         * @brief Points to the version of an MDIB when a binding of a context state to an \ref Mds ends
         * (i.e., the version where the context association was disassociated the first time).
         * @return MDIB version number or \c boost::none if undefined.
         */
        boost::optional<VersionCounter> unbindingMdibVersion() const;

        /**
         * @brief Time when a binding of a context state to an \ref Mds starts.
         * @return Start time or \c boost::none if undefined.
         */
        const boost::optional<Timestamp>& bindingStartTime() const;

        /**
         * @brief Time when a binding of a context state to an \ref Mds ends.
         * @return End time or \c boost::none if undefined.
         */
        const boost::optional<Timestamp>& bindingEndTime() const;

        /**
         * @brief List of actors (e.g., persons, devices or any identifiable systems) which have
         * confirmed that a binding of a context state to an \ref Mds is correct.
         */
        const InstanceIdentifiers& validators() const;

        /**
         * @brief Ordered list of identifiers for the context.
         * @details The list is ordered by the position of the identifiers in the list where the element
         * with the lower list index has a higher relevance than any entry with a higher list index.

         * \note Identifications can be used to span a communication context between service providers and service consumers.
         * \note Identifications can be empty, e.g., if \ref contextAssociation() is "No".
         * @return List of identifiers or \c boost::none if undefined.
         */
        const InstanceIdentifiers& identifications() const;

    protected:
        /**
         * @brief Default constructor.
         * @details Defaults
         *
         * - \ref AbstractContextState::contextAssociation() "Context Association" to \ref ContextAssociation::NotAssociated "not associated"
         * - \ref AbstractContextState::bindingMdibVersion() "Binding MDIB version" to none
         * - \ref AbstractContextState::unbindingMdibVersion() "Unbinding MDIB version" to none
         * - \ref AbstractContextState::bindingStartTime() "Binding start time" to none
         * - \ref AbstractContextState::bindingEndTime() "Binding end time" to none
         * - \ref AbstractContextState::validators() "Validators" to empty sequence
         * - \ref AbstractContextState::identifications() "Identifications" to empty sequence
         *
         * \note Also applies defaults from \ref AbstractMultiState.
         */
        AbstractContextState() = default;

        /**
         * @brief Full constructor.
         */
        AbstractContextState(const boost::optional<CodedValue>& category,
                             ContextAssociation contextAssociation,
                             boost::optional<VersionCounter> bindingMdibVersion,
                             boost::optional<VersionCounter> unbindingMdibVersion,
                             boost::optional<Timestamp> bindingStartTime,
                             boost::optional<Timestamp> bindingEndTime,
                             const InstanceIdentifiers& validators,
                             const InstanceIdentifiers& identifications,
                             ExtensionTypes&& extensions);

        ~AbstractContextState() = default;
    private:
        ContextAssociation m_contextAssociation{ContextAssociation::NotAssociated};
        boost::optional<VersionCounter> m_bindingMdibVersion{boost::none};
        boost::optional<VersionCounter> m_unbindingMdibVersion{boost::none};
        boost::optional<Timestamp> m_bindingStartTime{boost::none};
        boost::optional<Timestamp> m_bindingEndTime{boost::none};
        InstanceIdentifiers m_validators{};
        InstanceIdentifiers m_identifications{};
};

inline AbstractContextState::AbstractContextState(const boost::optional<CodedValue>& category,
                                                  ContextAssociation contextAssociation,
                                                  boost::optional<VersionCounter> bindingMdibVersion,
                                                  boost::optional<VersionCounter> unbindingMdibVersion,
                                                  boost::optional<Timestamp> bindingStartTime,
                                                  boost::optional<Timestamp> bindingEndTime,
                                                  const InstanceIdentifiers& validators, // NOLINT(modernize-pass-by-value)
                                                  const InstanceIdentifiers& identifications, // NOLINT(modernize-pass-by-value)
                                                  ExtensionTypes&& extensions) :
        AbstractMultiState(category, std::move(extensions)),
        m_contextAssociation(contextAssociation),
        m_bindingMdibVersion(std::move(bindingMdibVersion)),
        m_unbindingMdibVersion(std::move(unbindingMdibVersion)),
        m_bindingStartTime(std::move(bindingStartTime)),
        m_bindingEndTime(std::move(bindingEndTime)),
        m_validators(validators),
        m_identifications(identifications)
{
}

inline ContextAssociation AbstractContextState::contextAssociation() const
{
    return m_contextAssociation;
}

inline boost::optional<VersionCounter> AbstractContextState::bindingMdibVersion() const
{
    return m_bindingMdibVersion;
}

inline boost::optional<VersionCounter> AbstractContextState::unbindingMdibVersion() const
{
    return m_unbindingMdibVersion;
}

inline const boost::optional<Timestamp>& AbstractContextState::bindingStartTime() const
{
    return m_bindingStartTime;
}

inline const boost::optional<Timestamp>& AbstractContextState::bindingEndTime() const
{
    return m_bindingEndTime;
}

inline const InstanceIdentifiers& AbstractContextState::validators() const
{
    return m_validators;
}

inline const InstanceIdentifiers& AbstractContextState::identifications() const
{
    return m_identifications;
}

}
}
