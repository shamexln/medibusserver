#pragma once
#include <S31/Sdc/Private/Common/Http/ConnectionPolicy.h>
#include <S31/Sdc/Private/Common/PeerAuthorization.h>
#include <S31/Sdc/Private/Common/SocketLayer/QualityOfService.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Log/Public/Logger.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Chrono/Public/ChronoIo.h>

#include <cstddef>
#include <memory>

namespace S31::Sdc::Impl
{
/**
 * @brief A basic connection policy
 * @details Credentials for communication are provided by a @ref S31::CoreConfiguration instance.
 * @ingroup S31SdcCommon
 */
class BasicConnectionPolicy : public ConnectionPolicy
{
public:
    explicit BasicConnectionPolicy(DFL::NotNull<std::shared_ptr<const CoreConfiguration>> coreConfiguration)
        : m_coreConfiguration(std::move(coreConfiguration))
    {
    }

    [[nodiscard]] DFL::Crypto::RootCas provideRootCas() const override
    {
        return m_coreConfiguration->provideRootCas();
    }

    [[nodiscard]] std::optional<DFL::Crypto::PrivateKey> providePrivateKey() const override
    {
        if (auto key = m_coreConfiguration->providePrivateKey())
        {
            return std::move(key).value();
        }
        return {};
    }

    [[nodiscard]] DFL::Crypto::CertificateChain provideCertificateChain() const override
    {
        return m_coreConfiguration->provideCertificateChain();
    }

    [[nodiscard]] Nomenclature::WhiteListingState whitelistCheck(const std::string&) const override
    {
        // Basic connections do not check for whitelisting
        return Nomenclature::WhiteListingState::NotWhitelisted;
    }

    [[nodiscard]] Nomenclature::ProvideRoleAuthorizationListFunction provideRoleAuthorizationListFunction() const override
    {
        // Basic connections do not use a RAL.
        return []()
        {
            return DFL::Crypto::RoleAuthorizationList{};
        };
    }

    [[nodiscard]] std::optional<Utils::Error> verifyPeerCredentials(const Nomenclature::Credentials& /* credentials */) const override
    {
        // No additional verification required.
        return {};
    }

    [[nodiscard]] QualityOfService qualityOfService() const override
    {
        // Best effort (unconfigured qos)
        return {};
    }

    [[nodiscard]] int compressionLevel() const override
    {
        return static_cast<int>(m_coreConfiguration->compressionLevel);
    }

    [[nodiscard]] DFL::Chrono::Seconds idleTimeout() const override
    {
        return m_coreConfiguration->idleTimeout;
    }

    [[nodiscard]] std::chrono::seconds connectionTimeout() const override
    {
        return std::chrono::seconds{5};
    }

    [[nodiscard]] std::chrono::seconds requestTimeout() const override
    {
        return std::chrono::seconds{5};
    }

    [[nodiscard]] std::size_t maxReceiveSize() const override
    {
        // 4 MB max recieve size
        return static_cast<std::size_t>(1024 * 1024) * 4;
    }

protected:
    DFL::NotNull<std::shared_ptr<const CoreConfiguration>> m_coreConfiguration;
};


/**
 * @brief A connection policy specialized for Sdc connections.
 * @details Credentials for communication are provided by a @ref S31::CoreConfiguration instance.
 * Additional peer authorization checks are provided, as well as Quality of service configuration.
 * @ingroup S31SdcCommon
 */
class SdcConnectionPolicy : public BasicConnectionPolicy
{
public:
    // Inherit constructor taking core configuration
    using BasicConnectionPolicy::BasicConnectionPolicy;

    [[nodiscard]] Nomenclature::WhiteListingState whitelistCheck(const std::string& peer) const override
    {
        return m_coreConfiguration->whitelistCheck(peer);
    }

    [[nodiscard]] Nomenclature::ProvideRoleAuthorizationListFunction provideRoleAuthorizationListFunction() const override
    {
        std::weak_ptr<const CoreConfiguration> const weakConfiguration = m_coreConfiguration.get();

        return [weakConfiguration]()
        {
            if (auto configuration = weakConfiguration.lock())
            {
                return configuration->provideRoleAuthorizationList();
            }
            return DFL::Crypto::RoleAuthorizationList{};
        };
    }

    [[nodiscard]] std::optional<Utils::Error> verifyPeerCredentials(const Nomenclature::Credentials& credentials) const override
    {
        return PeerAuthorization::verifySdcPeerCredentials(credentials);
    }

    [[nodiscard]] QualityOfService qualityOfService() const override
    {
        QualityOfService qos;
        qos.prepare(m_coreConfiguration->qosEnabled, m_coreConfiguration->defaultQualityOfService);
        return qos;
    }
};


/**
 * @brief A connection policy specialized for DiscoveryProxy connections.
 * @details For discovery proxy communication, idle timeout is based on the
 * discoveryProxyProbeInterval.
 * @ingroup S31SdcCommon
 */
class DiscoConnectionPolicy : public BasicConnectionPolicy
{
public:
    explicit DiscoConnectionPolicy(DFL::NotNull<std::shared_ptr<const CoreConfiguration>> coreConfiguration)
        : BasicConnectionPolicy(std::move(coreConfiguration))
    {
        S31_STREAM_INFO_LOGGER(
                "Asio",
                "Creating Discovery Proxy Connection Policy with idle timeout = ",
                m_coreConfiguration->discoveryProxyProbeInterval * 2);
    }

    [[nodiscard]] DFL::Chrono::Seconds idleTimeout() const override
    {
        // It is expected that a discovery proxy will be contacted at least every discoveryProxyProbeInterval
        // seconds.  Therefore, this value is used as the basis for the idleTimeout.
        return m_coreConfiguration->discoveryProxyProbeInterval * 2;
    }
};

}
