#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/SocketLayer/IInterfaceChangeObserver.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceFilter.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceRegistry.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceResolveJob.h>
#include <S31/Utils/Public/ObservableSubject.h>
#include <S31/Utils/Public/Outcome.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Net/Public/Adapter/Infos.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <set>
#include <string>
#include <vector>

namespace S31::AsioDispatch
{
class Dispatcher;
}

namespace S31::Sdc::Impl
{

/**
 * Allow to request all multicast interfaces and listen to interface changes.
 *
 * \ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP NetworkInterfaceManager:
        public Utils::ObservableSubject<IInterfaceChangeObserver>,
        public std::enable_shared_from_this<NetworkInterfaceManager>,
        public Utils::OutcomeConsumer<NetworkInterfaceManager, NetworkInterfaceResolveJobResult>
{
    public:
    
    explicit NetworkInterfaceManager(const DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>>& dispatcher);
        NetworkInterfaceManager(const NetworkInterfaceManager&) = delete;
        NetworkInterfaceManager& operator=(const NetworkInterfaceManager&) = delete;

        ~NetworkInterfaceManager() override;

        void startListeningToNetworkInterfaceChanges();

        /**
         * Find the IP address for a given address family and interface index.
         *
         * @param ifIndex
         * @return IPv4 or IPv6 in string representation.
         */
        std::string getDefaultIP(unsigned int ifIndex);

        /**
         * Return all network interfaces from the registry which support multicast.
         */
        DFL::Net::Adapter::Infos getAllMulticastNetworkInterfaces();

        /**
         * Check if there is a new (connected) interface available.
         *
         * @param ifUpdates A set of interface changes.
         * @return true if there is an interface change and the interface connection flag is set to true, otherwise false.
         */
        static bool hasNewConnectedInterfaceInUpdate(const NetworkInterfaceUpdateList& ifUpdates);

        /**
         * @brief Enables or disables the filter for Loopback Interfaces from the list of multicast interfaces.
         *
         * @param disableFilter Enable or disable the filter.
         */
        void setDisableLoopbackInterfaceFilter(bool disableFilter);

        /**
         * @name Observers
         * @brief Add/remove observer for interface changes.
         */
        ///@{
        void registerObserver(const std::weak_ptr<IInterfaceChangeObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<IInterfaceChangeObserver>& observer) override;
        ///@}

    private:
        using Observable = Utils::ObservableSubjectDelegate<IInterfaceChangeObserver>;

        Observable m_observable;
        HandlerPtr m_networkInterfaceChangeObserverJob;
        std::shared_ptr<NetworkInterfaceRegistry> m_interfaceReg;
        std::weak_ptr<AsioDispatch::Dispatcher> m_dispatcher;
        bool m_disableLoopbackInterfaceFilter{false};
        unsigned int m_resolveJobErrorCount = 0;

};

}
