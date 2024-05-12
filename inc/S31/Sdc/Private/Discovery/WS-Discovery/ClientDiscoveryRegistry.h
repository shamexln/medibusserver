#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/ResolveRequest.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeRequest.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>

#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class IHelloByeObserver;
class IResolveMatchesCallback;
class IProbeMatchesCallback;

/**
 * \brief Registry for client-side WS-Discovery.
 *
 * \details It allows to subscribe for Hello and Bye listeners as well as the handling of pending Probe and Resolve requests.
 *
 * \ingroup S31SdcWsDiscovery
 */
class ClientDiscoveryRegistry
{
    public:

        void registerHelloByeListener(const std::shared_ptr<IHelloByeObserver>& listener);
        void unregisterHelloByeListener(const std::shared_ptr<IHelloByeObserver>& listener);

        void hello(
                const S31::Sdc::EndpointReference& urn,
                const S31::Sdc::Impl::QNameList& types,
                const std::vector<std::string>& scopeList,
                const std::string& xAddrs,
                S31::Sdc::MetadataVersion metadataVersion,
                const std::string& remoteIp);
        void bye(const S31::Sdc::EndpointReference& urn);

        void addResolveRequest(
                const std::string& messageId,
                std::weak_ptr<IResolveMatchesCallback> callback);
        void resolveMatch(
                const std::string& msgId,
                const S31::Sdc::EndpointReference& urn,
                const S31::Sdc::Impl::QNameList& types,
                const std::vector<std::string>& scopes,
                const std::string& xAddrs,
                S31::Sdc::MetadataVersion metadataVersion,
                const std::string& remoteIp);
        void removeResolveCallback(const std::shared_ptr<IResolveMatchesCallback>& callback);

        void addProbeRequest(
                const std::string& messageId,
                const std::shared_ptr<IProbeMatchesCallback>& callback);
        void probeMatch(
                const std::string& msgId,
                const S31::Sdc::EndpointReference& urn,
                const S31::Sdc::Impl::QNameList& types,
                const std::vector<std::string>& scopeList,
                const std::string& xAddrs,
                S31::Sdc::MetadataVersion metadataVersion,
                const std::string& remoteIp);
        void removeProbeCallback(const std::shared_ptr<IProbeMatchesCallback>& callback);

    private:
        std::vector<std::shared_ptr<IHelloByeObserver>> getHelloByeListeners();

        void removeOldRequests();

        std::map<std::string, ProbeRequest> m_probeRequests;
        std::map<std::string, ResolveRequest> m_resolveRequests;
        std::set<std::weak_ptr<IHelloByeObserver>, std::owner_less<std::weak_ptr<IHelloByeObserver>>> m_listener;
        std::mutex m_mutex;

};

}
