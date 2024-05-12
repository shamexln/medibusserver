#pragma once

#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace S31::Test
{
/**
 * Allows to look at a list of connected devices (URNs)
 */
class S31_CORE_IT_UTIL_EXPIMP ConnectedDevicesWatcher: public Sdc::RemoteDevicesObserver
{
    public:

        void online(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice) override;
        void offline(const S31::Sdc::EndpointReference& epr, const S31::Utils::Error& error) override;

        void waitForDeviceNumChange(const std::chrono::milliseconds& timeout);

        std::vector<std::string> getConnectedDevicesURNs();

        void clearConnectedDevicesURNs();

    private:
        std::mutex m_mutex;
        std::condition_variable m_condVar;
        std::vector<std::string> m_connectedDevicesURNs;
        size_t m_lastNumConnectedDevices = 0;
};

}
