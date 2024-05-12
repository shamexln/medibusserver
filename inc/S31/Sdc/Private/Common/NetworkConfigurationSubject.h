#pragma once

#include <S31/Sdc/Private/Common/INetworkConfigurationObserver.h>
#include <S31/Sdc/Private/Common/INetworkConfigurationSubject.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class NetworkInterfaceManager;
class NetworkInterfaceFilter;

/**
 * \brief Implementation of \ref S31::Sdc::Impl::INetworkConfigurationSubject.
 *
 * \ingroup S31SdcCommon
 */
class NetworkConfigurationSubject : public INetworkConfigurationSubject
{
        DFL_NOT_COPYABLE(NetworkConfigurationSubject)

    public:
        NetworkConfigurationSubject(const DFL::NotNull<std::shared_ptr<NetworkInterfaceManager>>& networkInterfaceManager,
                                    const DFL::NotNull<std::shared_ptr<NetworkInterfaceFilter>>& networkInterfaceFilter);

        void registerObserver(const std::weak_ptr<INetworkConfigurationObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<INetworkConfigurationObserver>& observer) override;

        void addMediaObserver(const std::weak_ptr<INetworkMediaObserver>& observer) override;
        void addMediaObserverWithInitialCallback(const std::shared_ptr<INetworkMediaObserver>& observer) override;

    private:
        class NetIfChangeObserver;
        const DFL::NotNull<std::shared_ptr<NetIfChangeObserver>> m_netIfChangeObserver;


};

}
