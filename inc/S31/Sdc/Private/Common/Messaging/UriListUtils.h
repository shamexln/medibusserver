#pragma once

#include <S31/S31CoreExImp.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * Helper functions for lists of xs:anyUri (std::vector of std::string).
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP UriListUtils
{
    public:

        /**
         * @brief Splits a whitespace (\#x20 | \#x9 | \#xD | \#xA) separated list of strings (URIs, ...).
         */
        static std::vector<std::string> splitWhiteSpaceSeparatedStrings(std::string uriList);

        static bool hasAtLeastOneUriStrcmp0(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs);
};

}
