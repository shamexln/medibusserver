#pragma once

#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Format/Public/ToString.h>

namespace S31::SetService
{
/**
 * @brief Helper to anonymize critical set service payload like patient identifying information.
 * @ingroup S31SetService
 */
class S31_CORE_EXPIMP AnonymizedStringConversion
{
    public:
        static std::string anonymize(const ProposedContextStates& payload);

        template<class T_Payload>
        static std::string anonymize(const T_Payload& payload)
        {
            return DFL::Format::toString(payload);
        }
};
}
