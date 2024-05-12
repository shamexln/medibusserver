#pragma once

#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * @brief Result of a @ref ResolveHttpJob.
 *
 * @ingroup S31SdcWsDiscovery
 */
struct ResolveHttpJobResult
{
    boost::optional<S31::Sdc::EndpointReference> eprAddress;
    S31::Sdc::Impl::QNameList types;
    std::vector<std::string> scopes;
    std::string xAddrs;
    S31::Sdc::MetadataVersion metadataVersion{0};
};

}
