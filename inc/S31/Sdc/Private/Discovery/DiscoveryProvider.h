#pragma once

#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Discovery/IDpwsDiscoveryObserver.h>
#include <S31/Sdc/Public/Discovery/DiscoveryObserver.h>
#include <S31/Sdc/Public/Discovery/DiscoveryProvider.h>
#include <S31/Utils/Public/ObservableSubject.h>
#include <S31/S31CoreExImp.h>

namespace S31::Sdc::Impl
{
class IDpwsDiscoverySubject;

/**
 * @brief DPWS discovery of remote devices.
 * @details Implementation for discovery of DPWS-based SDC devices in the network.
 *
 * @ingroup S31SdcDiscovery
 */
class S31_CORE_EXPIMP DiscoveryProvider:
        public S31::Sdc::Impl::IDpwsDiscoveryObserver,
        public Sdc::DiscoveryProvider,
        public std::enable_shared_from_this<DiscoveryProvider>
{
    public:
        explicit DiscoveryProvider(std::shared_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject> dpwsDiscoverySubject,
                                   std::weak_ptr<IScheduling> scheduling);

        void foundDevice(const EndpointReference& epr,
                         const Sdc::Impl::QNameList& types,
                         const std::vector<std::string>& scopes,
                         const std::string& xAddrs,
                         S31::Sdc::MetadataVersion metadataVersion,
                         const std::string& remoteIp) override;

        void byeFromDevice(const EndpointReference& epr) override;

        void registerObserver(const std::weak_ptr<Sdc::DiscoveryObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<Sdc::DiscoveryObserver>& observer) override;

        void probeForRemoteDevices() override;
        void probeForRemoteDevices(const DFL::Mdib::CodedValue& mdsType) override;
        void probeForRemoteDevices(const DFL::Mdib::LocationDetail& location) override;

        std::unique_ptr<LocationContextDiscoveryRegistry> createLocationContextDiscoveryRegistry(
                const DFL::Mdib::LocationDetail& location,
                DiscoveryTimeout discoveryTimeout,
                ProbeInterval probeInterval,
                const boost::optional<EndpointReference>& ignoredEpr) override;

        const std::shared_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject>& dpwsDiscoverySubject() const;

    private:
        S31::Utils::ObservableSubjectDelegate<Sdc::DiscoveryObserver> m_discoverySubject;
        std::shared_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject> m_dpwsDiscoverySubject;
        std::weak_ptr<IScheduling> m_scheduling;

};
}
