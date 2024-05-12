#pragma once

#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

struct WSDiscoveryScopeTag{};
using WSDiscoveryScope = DFL::StrongTypedef<DFL::Net::Uri, WSDiscoveryScopeTag, DFL::Skill::Streamable, DFL::Skill::EqualityComparable>;
using WSDiscoveryScopes = std::vector<WSDiscoveryScope>;

inline std::string toString(const WSDiscoveryScopes& scopes)
{
    std::string result;
    for (const auto& scope : scopes)
    {
        if (!result.empty())
        {
            result.append(" ");
        }
        result.append(scope.get().str());
    }
    return result;
}

}
