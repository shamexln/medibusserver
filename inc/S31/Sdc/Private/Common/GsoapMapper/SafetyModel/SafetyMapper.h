#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannelHash.h>
#include <S31/Safety/Public/Requirement.h>
#include <S31/S31CoreExImp.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <memory>

namespace S31::Sdc::Impl::Gsoap
{

/**
 * @brief Mapper for safety data from MDPWS specification (IEEE Std 11073-20702-2016 section 9).
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP SafetyMapper
{
    public:
        static Safety::Requirement mapSafetyRequirementsFromGsoap(const pm__AbstractDescriptor& src);
        static void mapSafetyRequirementsToGsoap(pm__AbstractDescriptor& dest, const Safety::Requirement& src);

        static Safety::Context fromGsoap(const si__T_USCORESafetyContext& src);
        static Safety::Context fromGsoap(const std::shared_ptr<si__T_USCORESafetyContext>& src);

        static Safety::DualChannelHashes fromGsoap(const si__T_USCOREDualChannel& src);
        static Safety::DualChannelHashes fromGsoap(const std::shared_ptr<si__T_USCOREDualChannel>& src);
};

}
