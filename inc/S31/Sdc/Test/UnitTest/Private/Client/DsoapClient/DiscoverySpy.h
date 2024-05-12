#pragma once

#include <gtest/gtest.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IDiscoveryClient.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IHelloByeObserver.h>

namespace S31::Sdc::Impl::Test
{

/**
 * Helper class for discovery based unit tests.
 */
class DiscoverySpy: public Sdc::Impl::IDiscoveryClient
{
    public:
        DiscoverySpy() :
                initialProbe(false),
                lastProbeAddress(),
                lastResolveUrn(),
                metadataEndpoints()
        {
        }

        void reset()
        {
            initialProbe = false;
            lastProbeAddress = "";
            lastResolveUrn = "";
            metadataEndpoints = "";
        }

        void registerListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener) override
        {
            observer = listener;
        }

        void unregisterListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener) override
        {
            if (observer == listener)
            {
                observer.reset();
            }
        }

        void injectHello(const S31::Sdc::EndpointReference& eprAddress, const S31::Sdc::Impl::QNameList& types, const std::vector<std::string>& scopes, const std::string& xAddrs, S31::Sdc::MetadataVersion metadataVersion, const std::string& remoteIp)
        {
            if (observer)
            {
                observer->hello(eprAddress, types, scopes, xAddrs, metadataVersion, remoteIp);
            }
        }

        void injectBye(const S31::Sdc::EndpointReference& eprAddress)
        {
            if (observer)
            {
                observer->bye(eprAddress);
            }
        }

        bool hasObserver()
        {
            return observer != nullptr;
        }

        void probe(const Sdc::Impl::Probe& /*query*/, const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback) override
        {
            initialProbe = true;
            probeMatchesCallback = callback;
        }

        void delayedProbe(const Sdc::Impl::Probe& /*query*/, const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& callback, DFL::Chrono::Milliseconds /*delay*/) override
        {
            initialProbe = true;
            probeMatchesCallback = callback;
        }

        void removeProbeListener(const std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback>& /*callback*/) override
        {
            probeMatchesCallback.reset();
        }

        std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback> getProbeMatchCallback()
        {
            return probeMatchesCallback;
        }

        void directedProbe(ProbeTargetType /*targetType*/, const DFL::Net::Uri& address, LocalUdpEndpointPort /*localUdpEndpointPort*/, const CallbackFunction& /*callback*/, const WSDiscoveryScopes& /*scopes*/) override
        {
            if (address.str().empty())
            {
                ADD_FAILURE() << "directed probe called without transport address";
            }
            lastProbeAddress = address.str();
        }

        void resolve(const S31::Sdc::EndpointReference& eprAddress, const std::shared_ptr<S31::Sdc::Impl::IResolveMatchesCallback>& /*callback*/) override
        {
            if (eprAddress.address().str().empty())
            {
                ADD_FAILURE() << "resolve called without urn";
            }
            lastResolveUrn = eprAddress.address().str();
        }

        void removeResolveListener(const std::shared_ptr<S31::Sdc::Impl::IResolveMatchesCallback>& /*callback*/) override
        {
        }

        std::string getLastResolveUrn() const
        {
            return lastResolveUrn;
        }

        std::string getLastProbeAddress() const
        {
            return lastProbeAddress;
        }

        bool hasProbeTriggered() const
        {
            return initialProbe;
        }

        bool noProbeRequested() const
        {
            return lastProbeAddress.empty();
        }

        bool noResolveRequested() const
        {
            return lastResolveUrn.empty();
        }

    private:
        bool initialProbe;
        std::string lastProbeAddress;
        std::string lastResolveUrn;
        std::string metadataEndpoints;
        std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver> observer;
        std::shared_ptr<S31::Sdc::Impl::IProbeMatchesCallback> probeMatchesCallback;

};

}
