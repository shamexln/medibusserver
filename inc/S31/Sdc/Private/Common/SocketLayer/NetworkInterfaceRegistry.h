#pragma once

#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Net/Public/Adapter/Infos.h>

#include <mutex>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * \brief Registry to provide the system's network interfaces and to wait for network interface changes.
 *
 * \ingroup S31SdcCommonSocket
 */
class S31_CORE_EXPIMP NetworkInterfaceRegistry
{
    public:
        NetworkInterfaceRegistry() = default;

        /**
         * @brief Return current interface list.
         *
         * @param forceResolve If true, force the registry to query the system for new interfaces. Otherwise,
         *                     interfaces will only be queried if the registry is empty.
         * @return Current list of entries within the registry. If the registry is empty, the routine tries to resolve
         *         interfaces in advance.
         */
        DFL::Net::Adapter::Infos getRegistryEntries(bool forceResolve = false);

        /**
         * @brief Return size of current interface list.
         *
         * @return Current size of registered network interfaces. Return 0 if there are no interfaces or interfaces
         *         haven't been registered yet via NetworkInterfaceRegistry::getRegistryEntries().
         */
        size_t size() const;

        /**
         * @brief Get all interfaces that have been changed since last update.
         *
         * @return List of pairs. The pair's first entry is the interface data of the registry before the interface
         *         had changed (if the interface is new, it evaluates to boost::none). The pair's second entry is the
         *         new interface data. List is empty if there was no change.
         */
        NetworkInterfaceUpdateList getChangedInterfaces();

    private:
        DFL::Net::Adapter::Infos ifRegistry{};
        mutable std::mutex ifRegistryMutex;

        /**
         * @return List of pairs. The pair's first entry is the interface before the update (if there was no interface
         *         before, it evaluates to boost::none. The pair's second entry is the interface after the update.
         */
        static NetworkInterfaceUpdateList getUpdatedInterfaces(
            const DFL::Net::Adapter::Infos& currentIfs, const DFL::Net::Adapter::Infos& registryIfs);

        static NetworkInterfaceUpdateList resolveDisconnectedInterfaces(
            const DFL::Net::Adapter::Infos& currentIfs, const DFL::Net::Adapter::Infos& registryIfs);
};

}
