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
 * Clients have to implement this interface for asynchronous probe matches messages.
 *
 * \ingroup S31SdcWsDiscovery
 */
class IProbeMatchesCallback
{
    public:
        virtual ~IProbeMatchesCallback() = default;

        /**
         * Called for each received WS-Discovery ProbeMatches message.
         *
         * Thus multiple calls are possible for one Probe request.
         */
        virtual void probeMatches(const S31::Sdc::EndpointReference& eprAddress,
                                  const S31::Sdc::Impl::QNameList& types,
                                  const std::vector<std::string>& scopes,
                                  const std::string& xAddrs,
                                  S31::Sdc::MetadataVersion metadataVersion,
                                  const std::string& remoteIp) = 0;

        /**
         * Function is called when the callback is removed from the internal list.
         *
         * This happens once for each probe (search request) in case of search timeout or shutdown.
         * It can be used for clean up purposes.
         * No probeMatches callbacks for corresponding probe will be triggered afterwards.
         * If the same callback is used for multiple probes, it will be called multiple times.
         */
        virtual void probeFinished() = 0;

};

}
}
