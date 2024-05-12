#pragma once

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class HttpClient;

/**
 * @brief Provide access to preconfigured @ref HttpClient instances.
 */
class HttpClientRegistry
{
    public:
        virtual ~HttpClientRegistry() = default;

        /// @brief Provide a client configured for normal priority Sdc communication.
        /// @details This client is intended for use with Sdc Get services, and Event
        /// reporting. It is configured with Sdc participant checks during Ssl verification,
        /// higher priority for scheduling, and a higher priority Assured Forwarding
        /// Quality of service.
        virtual DFL::NotNull<std::shared_ptr<HttpClient>> sdcNormalPriorityClient() const = 0;

        /// @brief Provide a client configured for low priority Sdc communication.
        /// @details This client is intended for use with Sdc Archive or backfill
        /// services. It is configured with Sdc participant checks during Ssl verification,
        /// lower priority for scheduling, and a lower priority Assured Forwarding
        /// Quality of service.
        virtual DFL::NotNull<std::shared_ptr<HttpClient>> sdcLowPriorityClient() const = 0;

        /// @brief Provide a client configured for non-Sdc communication.
        /// @details This client is intended for non-Sdc use. It is configured with
        /// only basic checks during Ssl verification, lower priority for scheduling,
        /// and only "best effort" Quality of service.
        virtual DFL::NotNull<std::shared_ptr<HttpClient>> basicClient() const = 0;

        /// @brief Provide a client configured for DiscoveryProxy communication.
        /// @details This client is intended for DiscoveryProxy communication.
        /// It is the same as the basicClient, except that the idle connection
        /// timeout is based on the discovery proxy probe interval.
        virtual DFL::NotNull<std::shared_ptr<HttpClient>> discoveryClient() const = 0;
};

}