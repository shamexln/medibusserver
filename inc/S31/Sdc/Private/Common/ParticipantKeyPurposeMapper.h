#pragma once

#include <S31/Nomenclature/Public/Roles.h>

#include <Framework/Mdib/Public/Model/Uri.h>
#include <Framework/Utils/Public/Oid.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Impl
{

/**
 * @brief Maps an Oid (such as \ref S31::Nomenclature::SdcServiceProvider) to ParticipantKeyPurpose Uri and vice versa.
 * @details PKP Uris are sent out in WS-Discovery message to signal requirements that the SDC participant is complying with.
 * See 11073-20701-2018 Section 9.3 for PKP algorithm.
 * @ingroup S31SdcCommon
 */
class ParticipantKeyPurposeMapper
{
    public:
        /**
         * @brief Convert Oid to ParticipantKeyPurpose Uri
         */
        static DFL::Mdib::Uri toUri(const DFL::Oid& keyPurposeOid);

        /**
         * @brief Convert ParticipantKeyPurpose Uri to Oid
         */
        static boost::optional<DFL::Oid> toOid(const DFL::Mdib::Uri& pkpUri);

};

}
