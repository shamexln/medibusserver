#include <S31/Adt/Public/Discovery/DiscoveryObserver.h>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <vector>

#pragma once

namespace S31::Test
{

class AdtDiscoveryListener: public Adt::DiscoveryObserver
{
public:
    void foundDevice(const Adt::RemoteDeviceInfo& device) override;
    void byeFromDevice(const Sdc::EndpointReference& device) override;

    std::vector<Adt::RemoteDeviceInfo> getFoundDevices() const;
    void clearFoundDevices();

    [[nodiscard]] boost::optional<Adt::RemoteDeviceInfo> waitForDevice(const Sdc::EndpointReference& epr,
                                                                       std::chrono::milliseconds timeout = std::chrono::milliseconds{2000}) const;
private:
    template <typename DeviceMatchFn>
    boost::optional<Adt::RemoteDeviceInfo> waitForDevice(std::chrono::milliseconds timeout, DeviceMatchFn deviceMatchFn) const;

    mutable std::mutex mutex;
    mutable std::condition_variable condition;
    std::vector<Adt::RemoteDeviceInfo> foundDevices;
};

}
