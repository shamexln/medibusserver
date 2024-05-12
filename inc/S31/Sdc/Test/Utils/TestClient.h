#pragma once

#include <S31/Sdc/Public/Client/Client.h>

#include <S31/Sdc/Test/Utils/CommonConfigurator.h>
#include <S31/Sdc/Test/Utils/OfflineWatcher.h>
#include <S31/Sdc/Public/Common/ThreadPoolDispatcher.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Mdib/Test/Public/WaitingMdibChangesObserver.h>

namespace S31
{
class CoreConfiguration;
class S31CoreFactory;

namespace Sdc
{
class IDispatcher;
class DiscoveryProvider;
class RemoteDevicesProvider;
class CommunicationEndpoint;

namespace Test
{


/**
 * @brief Implementation of an SDC client that runs with dedicated thread pools and network sockets.
 */
class S31_CORE_IT_UTIL_EXPIMP TestClient: public S31::Sdc::Client
{
    public:
        explicit TestClient(const CoreConfiguration& configuration = CommonConfigurator::defaultConfiguration());
        explicit TestClient(NumberOfThreads numberOfThreads, const CoreConfiguration& configuration = CommonConfigurator::defaultConfiguration());

        // no copy
        TestClient(const TestClient& rhs) = delete;
        TestClient& operator=(const TestClient& rhs) = delete;

        // moving allowed
        TestClient(TestClient&& rhs);
        TestClient& operator=(TestClient&& rhs);

        ~TestClient() override;

        std::shared_ptr<DiscoveryProvider> discoveryProvider() const override;

        std::shared_ptr<RemoteDevicesProvider> remoteDevicesProvider() const override;

        /**
         * @brief Connects to the given device (if not already connected).
         * @return pointer to the device if successful, nullptr otherwise
         */
        std::shared_ptr<RemoteDevice> connect(std::chrono::milliseconds waitTime, const S31::Sdc::EndpointReference& deviceEpr);

        /// Connects to the given device (if needed) and waits for the given predicate become true (i.e. waiting for an Mdib change)
        bool waitFor(std::chrono::milliseconds waitTime,
                     const S31::Sdc::EndpointReference& deviceEpr,
                     const std::function<bool(const DFL::Mdib::Mdib&)>& mdibPredicate);

        const std::shared_ptr<Sdc::Client>& sdcClient();

        DFL::NotNull<std::shared_ptr<DFL::Mdib::Test::WaitingMdibChangesObserver>> createMdibChangesObserver(const S31::Sdc::EndpointReference& deviceEpr);

        /// returns the localization client of the given device (connects if needed)
        Sdc::LocalizationClientPtr localizationClient(const S31::Sdc::EndpointReference& deviceEpr,
                                                      std::chrono::milliseconds maxWaitTime = std::chrono::seconds(10));

        /// Returns an object that allows to watching the disconnection of the device with the given urn.
        /// Note that also a 'normal' disconnects have according errors, e.g.: UserDisconnected
        DFL::NotNull<std::shared_ptr<OfflineWatcher>> offlineWatcher(
                const EndpointReference& endpointReference,
                const OfflineWatcher::ErrorPredicate& pred = [](const Utils::Error&) { return true; });

        std::shared_ptr<S31::Sdc::CommunicationEndpoint> communicationEndpoint() const;

    private:
        void commonInit(const CoreConfiguration& configuration);

        std::unique_ptr<S31::S31CoreFactory> m_coreFactory;
        DFL::NotNull<std::shared_ptr<IDispatcher>> m_dispatcher;
        std::shared_ptr<Sdc::Client> m_client;

};

}
}
}
