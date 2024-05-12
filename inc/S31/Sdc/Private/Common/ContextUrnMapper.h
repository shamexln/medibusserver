#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Context/LocationContextState.h>
#include <Framework/Mdib/Public/Model/Uri.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Maps \ref DFL::Mdib::InstanceIdentifier from contexts (e.g., location) to URN and vice versa.
 * @details The URNs are used for context-based discovery with WS-Discovery scopes.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ContextUrnMapper
{
    public:
        /**
         * @brief Maps for an \ref DFL::Mdib::ContextAssociation::Associated state
         * all \ref DFL::Mdib::LocationContextState::identifications() to URIs.
         */
        static DFL::Mdib::Uris associatedInstanceIdentifiersToUris(const DFL::Mdib::LocationContextState& loc);

        /**
         * @brief Maps one identifier.
         * @details May be used for all context state (also for patient context state).
         */
        static DFL::Mdib::Uri toUri(const DFL::Mdib::InstanceIdentifier& instanceIdentifier);

        /**
         * @brief Version for location context state only with additional location detail.
         */
        static DFL::Mdib::Uri toUri(const DFL::Mdib::InstanceIdentifier& ii, const DFL::Mdib::LocationDetail& locDetails);

        /**
         * @brief Extracts an instance identifier from the context-based discovery.
         * @details Might be used for all context types (e.g, patient, location).
         * Especially for location contexts see \ref locationUriToInstanceIdentifier().
         */
        static boost::optional<DFL::Mdib::InstanceIdentifier> uriToInstanceIdentifier(const DFL::Mdib::Uri& contextUri);

        /**
         * @brief Extracts an instance identifier from a location context-base discovery URI.
         * @details A specialized version of \ref uriToInstanceIdentifier() for location context.
         */
        static boost::optional<DFL::Mdib::InstanceIdentifier> locationUriToInstanceIdentifier(const DFL::Mdib::Uri& locationContextUri);


};

}
