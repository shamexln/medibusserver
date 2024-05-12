#pragma once

#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/Sdc/Test/Utils/TestClient.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Utils/Public/NotNull.h>

namespace DFL::Net
{
class Uri;
}

namespace S31::Sdc::Test
{

/**
 * @brief Creates clients that run with dedicated thread pools and network sockets.
 */
class S31_CORE_IT_UTIL_EXPIMP TestClientFactory
{
    public:
        /**
         * @brief Creates a test client that uses a default configuration retrieved via
         *        \ref CommonConfigurator::defaultConfiguration().
         */
        static DFL::NotNull<std::unique_ptr<TestClient>> createTestClient();

        /**
         * @brief Creates a test client that uses a default configuration retrieved via
         *        \ref CommonConfigurator::defaultConfiguration().
         * @details In contrast to \ref TestClientFactory::createTestClient(), this function generates a certificate
         *          without the consumer role.
         */
        static DFL::NotNull<std::unique_ptr<TestClient>> createTestClientWithMissingConsumerRole();

        /**
         * @brief Creates a test client that uses a default configuration retrieved via
         *        \ref CommonConfigurator::defaultConfiguration().
         * @details In contrast to \ref TestClientFactory::createTestClient(), this function configures a discovery
         *          proxy with a probing interval for automated probing (default 5 minutes).
         */
        static DFL::NotNull<std::unique_ptr<TestClient>> createTestClientWithDiscoveryProxy(const DFL::Net::Uri& discoveryProxyAddress,
                                                                                            DFL::Chrono::Seconds probeInterval = DFL::Chrono::Seconds(300));

        /**
         * @brief Creates a test client that uses a default configuration retrieved via
         *        \ref CommonConfigurator::defaultConfiguration().
         * @details In contrast to \ref TestClientFactory::createTestClient(), this function configures a ConnectionPriorityGroup.
         */
        static DFL::NotNull<std::unique_ptr<TestClient>> createTestClientWithConnectionPriority(S31::Sdc::ConnectionPriorityGroup connectionPriority);

        /**
         * @brief Same as \ref TestClientFactory::createTestClient(), but with custom configuration.
         */
        static DFL::NotNull<std::unique_ptr<TestClient>> createTestClient(const CoreConfiguration& configuration);
};

}
