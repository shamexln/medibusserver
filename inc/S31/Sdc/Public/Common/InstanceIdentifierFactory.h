#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>

#include <boost/optional/optional.hpp>

namespace DFL::Mdib
{
class LocationDetail;
}
namespace S31::Sdc
{

/**
 * @brief Source of globally defined \ref DFL::Mdib::InstanceIdentifier for re-use.
 * @details
 * This is the central place to define which identifier shall be used for what purpose.
 * Code should use specific function that might map all to the same identifier.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP InstanceIdentifierFactory
{
    public:
        /**
         * @brief This validator expresses that the data is confirmed locally via the user interface.
         * @returns \ref DFL::Mdib::InstanceIdentifier with user validator as \ref DFL::Mdib::Root.
         */
        static DFL::Mdib::InstanceIdentifier userValidated();

        /**
         * @brief This validator expresses that the data is confirmed locally with a clinical super user being the validating actor.
         * @returns \ref DFL::Mdib::InstanceIdentifier with user validator as \ref DFL::Mdib::Root.
         */
        static DFL::Mdib::InstanceIdentifier clinicalSuperUserValidator();

        /**
         * @brief This validator expresses that the data is associated (confirmed) by a Biomed.
         * @returns \ref DFL::Mdib::InstanceIdentifier with Biomed validator as \ref DFL::Mdib::Root.
         */
        static DFL::Mdib::InstanceIdentifier bioMedValidated();

        /**
         * @brief This validator expresses that the data comes from the local system (Service Personnel confirmed).
         * @returns \ref DFL::Mdib::InstanceIdentifier with Service Personnel validator as \ref DFL::Mdib::Root.
         */
        static DFL::Mdib::InstanceIdentifier servicePersonnelValidated();

        /**
         * @brief This validator expresses that the data is confirmed by a Remote Service Operation.
         * @returns \ref DFL::Mdib::InstanceIdentifier with Remote Service Operation validator as \ref DFL::Mdib::Root.
         */
        static DFL::Mdib::InstanceIdentifier remoteServiceOperationValidated();

        /**
         * @brief This validator expresses that the data is confirmed with technical means.
         * @returns \ref DFL::Mdib::InstanceIdentifier with Technical validator as \ref DFL::Mdib::Root.
         */
        static DFL::Mdib::InstanceIdentifier technicalValidated();

        /**
         * @brief Uses SDC fallback instance identifier algorithm.
         * @details In SDC IEEE 11073-20701-2018 section 9.4.1.1 an algorithm is provided to create
         * an DFL::Mdib::InstanceIdentifier from DFL::Mdib::LocationDetail, in case no other
         * instance identifier can be assigned from an authority.
         */
        static boost::optional<DFL::Mdib::InstanceIdentifier> fallbackInstanceIdentifier(const DFL::Mdib::LocationDetail& location);

};

}
