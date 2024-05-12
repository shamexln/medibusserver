#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Discovery/DiscoveryObserver.h>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <vector>

#include <boost/optional/optional.hpp>

namespace S31::Test
{

class SdcDiscoveryListener: public Sdc::DiscoveryObserver
{
    public:
        void foundDevice(const Sdc::RemoteDeviceInfo& dev) override;

        void byeFromDevice(const Sdc::EndpointReference& /*device*/) override
        {
        }

        std::vector<Sdc::RemoteDeviceInfo> getFoundDevices() const;

        void clearFoundDevices();

        [[nodiscard]] boost::optional<Sdc::RemoteDeviceInfo> waitForDevice(const Sdc::EndpointReference& epr,
                                                             std::chrono::milliseconds timeout = std::chrono::milliseconds{2000}) const;

        [[nodiscard]] boost::optional<Sdc::RemoteDeviceInfo> waitForDeviceWithLocation(const Sdc::EndpointReference& epr,
                                                                         std::chrono::milliseconds timeout = std::chrono::milliseconds{2000}) const;
    private:
        template <typename DeviceMatchFn>
        boost::optional<Sdc::RemoteDeviceInfo> waitForDevice(std::chrono::milliseconds timeout, DeviceMatchFn deviceMatchFn) const;

        mutable std::mutex mutex;
        mutable std::condition_variable condition;
        std::vector<Sdc::RemoteDeviceInfo> foundDevices;
};

}
