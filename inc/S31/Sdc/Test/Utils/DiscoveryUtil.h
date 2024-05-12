#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <string>

namespace S31::Sdc::Test
{
/**
 * @brief Test utility for discovery.
 */
class S31_CORE_IT_UTIL_EXPIMP DiscoveryUtil
{
    public:
        /**
         * @brief Verifies only necessary namespaces are present.
         */
        static bool namespacesValid(const std::string& message);
};

}
