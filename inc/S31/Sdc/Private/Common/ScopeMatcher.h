#pragma once

#include <S31/S31CoreExImp.h>

#include <string>
#include <string_view>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Provides different matching rules WS-Discovery scope matching.
 *
 * \ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ScopeMatcher
{
    public:
        static bool
        match(const std::vector<std::string>& probeScopes,
              const std::vector<std::string>& targetServiceScopes,
              std::string_view                matchingRule);

    private:
        static bool matchesStrcmp0Rule(const std::string& s1, const std::string& s2);
        static bool matchesRFC3986Rule(const std::string& s1, const std::string& s2);

        static bool isSubsetOf(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs,
                bool (*cmp)(const std::string& subsetValue, const std::string& supersetValue));
};

}
