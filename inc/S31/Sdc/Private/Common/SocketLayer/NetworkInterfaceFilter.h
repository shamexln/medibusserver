#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Net/Public/Adapter/Infos.h>
#include <Framework/Utils/Public/NotNull.h>

#include <functional>
#include <memory>
#include <mutex>
#include <set>
#include <vector>

namespace S31::Sdc::Impl
{

class NetworkInterfaceManager;

/**
 * @brief Access to filtered sets of network interfaces.
 *
 * @ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP NetworkInterfaceFilter
{
    public:
        using GetAllMulticastNetworkInterfacesCallback = std::function<DFL::Net::Adapter::Infos()>;

        NetworkInterfaceFilter();
        explicit NetworkInterfaceFilter(GetAllMulticastNetworkInterfacesCallback getAllMulticastNetworkInterfacesCallback);
        explicit NetworkInterfaceFilter(const DFL::NotNull<std::shared_ptr<NetworkInterfaceManager>>& networkInterfaceManager);

        ~NetworkInterfaceFilter();

        /**
         * Add interface to white list.
         *
         * @param interfaceName
         */
        void addAllowInterface(const std::string& interfaceName);

        /**
         * Add interface to black list.
         *
         * Interfaces on the black list have a higher priority than interfaces on the white list.
         *
         * @param interfaceName
         */
        void addDenyInterface(const std::string& interfaceName);

        /**
         * Clear white and black list.
         */
        void resetAllowDenyInterfaces();

        /**
         * Return a list of multicast network interfaces, filtered by white and black list.
         */
        DFL::Net::Adapter::Infos getAllMulticastNetworkInterfaces();

    private:
        std::shared_ptr<NetworkInterfaceManager> m_networkInterfaceManager;
        GetAllMulticastNetworkInterfacesCallback m_getAllMulticastNetworkInterfacesCallback;
        /// lists all interfaces, IPv6 interface(s) at the beginning
        std::set<std::string> m_denyInterfaces;
        std::set<std::string> m_allowInterfaces;

        std::mutex m_interfacesFilterMutex;
};

}
