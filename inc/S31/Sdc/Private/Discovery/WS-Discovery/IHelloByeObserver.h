#pragma once

#include <string>
#include <vector>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>

namespace S31::Sdc
{

class EndpointReference;

namespace Impl
{

/**
 * @brief Callback interface for customers interested in WS-Discovery Hello and Bye information.
 *
 * \ingroup S31SdcWsDiscovery
 */
class IHelloByeObserver
{
    public:
        virtual ~IHelloByeObserver() = default;

        virtual void hello(const S31::Sdc::EndpointReference& eprAddress,
                           const S31::Sdc::Impl::QNameList& types,
                           const std::vector<std::string>& scopes,
                           const std::string& xAddrs,
                           S31::Sdc::MetadataVersion metadataVersion,
                           const std::string& remoteIp) = 0;

        virtual void bye(const S31::Sdc::EndpointReference& eprAddress) = 0;
};

}
}
