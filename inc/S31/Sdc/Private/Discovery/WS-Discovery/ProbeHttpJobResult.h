#pragma once

#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <boost/optional/optional.hpp>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief A single result of a @ref S31::Sdc::Impl::DirectedProbeJob, a ProbeMatch.
 * @ingroup S31SdcWsDiscovery
 */
struct ProbeMatchResult
{
    boost::optional<S31::Sdc::EndpointReference> eprAddress;
    S31::Sdc::Impl::QNameList types;
    std::vector<std::string> scopes;
    std::string xAddrs;
    S31::Sdc::MetadataVersion metadataVersion{0};
    std::string remoteIp;
};

/**
 * @brief Sequence of @ref ProbeMatchResult.
 * @ingroup S31SdcWsDiscovery
 */
using DirectedProbeJobResults = std::vector<ProbeMatchResult>;

}
