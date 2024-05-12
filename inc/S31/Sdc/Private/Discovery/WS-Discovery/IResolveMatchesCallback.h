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
 * @brief Clients have to implement this interface for resolve matches messages.
 *
 * \ingroup S31SdcWsDiscovery
 */
class IResolveMatchesCallback
{
    public:
        virtual ~IResolveMatchesCallback() = default;

        /**
         * Is called with the response.
         *
         * In contrast to probes there is only one resolve match.
         */
        virtual void resolveMatches(const S31::Sdc::EndpointReference& eprAddress,
                                    const S31::Sdc::Impl::QNameList& types,
                                    const std::vector<std::string>& scopes,
                                    const std::string& xAddrs,
                                    S31::Sdc::MetadataVersion metadataVersion,
                                    const std::string& remoteIp) = 0;

        /**
         * Function is called when the callback is removed from the internal list.
         *
         * This happens when the corresponding WS-Discovery ResolveMatches message was not received in time.
         */
        virtual void resolveTimeout(const std::string& messageId) = 0;
};

}
}
