#pragma once

#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>
#include <S31/Sdc/Public/Common/ErrorDefinitions.h>
#include <S31/Sdc/Test/Public/Client/RemoteDeviceMock.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <atomic>
#include <mutex>

namespace S31::Sdc::Test
{

/**
 * @brief Mock implementation for \ref S31::Sdc::RemoteDevicesProvider.
 * @ingroup S31SdcClient
 */
class RemoteDevicesProviderMock: public S31::Sdc::RemoteDevicesProvider
{
        DFL_NOT_COPYABLE(RemoteDevicesProviderMock)

    public:
        RemoteDevicesProviderMock() = default;

        void connectToRemoteDevice(const EndpointReference& epr) override;
        void connectToRemoteDevice(const EndpointReference& endpointReference,
                                   const MdibSubscriptionTypes& subscriptions) override;
        void connectToRemoteDevice(const EndpointReference& epr, SubscriptionReports reports) override;

        void disconnectFromRemoteDevice(const EndpointReference& endpointReference) override;

        std::shared_ptr<RemoteDevice> waitForRemoteDevice(const EndpointReference& endpointReference, DFL::Chrono::Milliseconds waitTime) override;

        void registerObserver(const std::weak_ptr<S31::Sdc::RemoteDevicesObserver>& observer) override;

        void unregisterObserver(const std::weak_ptr<S31::Sdc::RemoteDevicesObserver>& observer) override;

        void connectableRemoteDevice(const std::shared_ptr<S31::Sdc::Test::RemoteDeviceMock>& remoteDevice);

        std::shared_ptr<S31::Sdc::RemoteDevice> remoteDevice(const S31::Sdc::EndpointReference& epr) override;

    private:
        mutable std::mutex m_mutex;
        std::map<S31::Sdc::EndpointReference, std::shared_ptr<S31::Sdc::Test::RemoteDeviceMock>, S31::Sdc::EprAddressLessCompare> m_connectableRemoteDevices;
        std::map<S31::Sdc::EndpointReference, std::shared_ptr<S31::Sdc::Test::RemoteDeviceMock>, S31::Sdc::EprAddressLessCompare> m_connectedRemoteDevices;
        S31::Utils::ObservableSubjectDelegate<S31::Sdc::RemoteDevicesObserver> m_nodeSubject;
        std::vector<S31::Sdc::EndpointReference> m_connectRequests;
        std::vector<S31::Sdc::EndpointReference> m_disconnectRequests;
};

inline void RemoteDevicesProviderMock::connectToRemoteDevice(const S31::Sdc::EndpointReference& epr)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_connectRequests.push_back(epr);

    auto it = m_connectedRemoteDevices.find(epr);
    if (it != m_connectedRemoteDevices.end())
    {
        return;
    }

    auto itPool = m_connectableRemoteDevices.find(epr);
    if (itPool == m_connectableRemoteDevices.end())
    {
        return;
    }

    m_connectedRemoteDevices[epr] = m_connectableRemoteDevices[epr];
    auto nodeToNotify = m_connectedRemoteDevices[epr];
    lock.unlock();

    m_nodeSubject.notify([&nodeToNotify](S31::Sdc::RemoteDevicesObserver& observer)
    {
        if (nodeToNotify)
        {
            observer.online(DFL::asNotNull(nodeToNotify));
        }
    });
}

inline void RemoteDevicesProviderMock::connectToRemoteDevice(const EndpointReference& endpointReference,
                                                             const MdibSubscriptionTypes& /* subscriptions */)
{
    connectToRemoteDevice(endpointReference);
}

inline void RemoteDevicesProviderMock::connectToRemoteDevice(
        const EndpointReference& endpointReference, SubscriptionReports /*reports*/)
{
    connectToRemoteDevice(endpointReference);
}

inline void RemoteDevicesProviderMock::disconnectFromRemoteDevice(const EndpointReference& epr)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_disconnectRequests.push_back(epr);

    auto it = m_connectedRemoteDevices.find(epr);
    if (it == m_connectedRemoteDevices.end())
    {
        return;
    }

    auto nodeToNotifyOffline = it->second;
    m_connectedRemoteDevices.erase(it);
    lock.unlock();

    m_nodeSubject.notify([&](S31::Sdc::RemoteDevicesObserver& observer)
    {
        auto error = Utils::makeError(S31::Sdc::Errors::UserDisconnected{});
        observer.offline(epr, error);
    });
}

inline std::shared_ptr<RemoteDevice> RemoteDevicesProviderMock::waitForRemoteDevice(const EndpointReference&, DFL::Chrono::Milliseconds)
{
    return nullptr;
}

inline std::shared_ptr<S31::Sdc::RemoteDevice> RemoteDevicesProviderMock::remoteDevice(const S31::Sdc::EndpointReference& epr)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_connectedRemoteDevices.find(epr);
    if (it != m_connectedRemoteDevices.end())
    {
        return it->second;
    }

    return std::shared_ptr<S31::Sdc::Test::RemoteDeviceMock>();
}

inline void RemoteDevicesProviderMock::connectableRemoteDevice(const std::shared_ptr<S31::Sdc::Test::RemoteDeviceMock>& remoteDevice)
{
    if (remoteDevice)
    {
        m_connectableRemoteDevices[remoteDevice->endpointReference()] = remoteDevice;
    }
}

inline void RemoteDevicesProviderMock::registerObserver(const std::weak_ptr<S31::Sdc::RemoteDevicesObserver>& observer)
{
    m_nodeSubject.registerObserver(observer);
}

inline void RemoteDevicesProviderMock::unregisterObserver(const std::weak_ptr<S31::Sdc::RemoteDevicesObserver>& observer)
{
    m_nodeSubject.unregisterObserver(observer);
}

}
