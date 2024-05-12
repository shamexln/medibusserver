#pragma once

#include <S31/Nomenclature/Public/CryptoFunctions.h>
#include <S31/Nomenclature/Public/Whitelist.h>
#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/Sdc/Public/Common/AssuredForwardingClass.h>
#include <S31/Sdc/Public/Common/InstanceIdentifiersUtil.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Config/Public/Attributes.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <Framework/Crypto/Public/RoleAuthorizationList.h>
#include <Framework/Utils/Public/Uri.h>

#include <boost/optional/optional.hpp>

#include <cstdint>
#include <functional>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace S31
{

/**
 * @brief Callback functions that provide root CAs.
 * @ingroup S31SdcCommon
 */
using ProvideRootCasFunction = Nomenclature::ProvideRootCasFunction;

/**
 * @brief Callback functions that provide possibly a private key.
 * @ingroup S31SdcCommon
 */
using ProvidePrivateKeyFunction = Nomenclature::ProvidePrivateKeyFunction;

/**
 * @brief Callback functions that provide the certificate chain.
 * @ingroup S31SdcCommon
 */
using ProvideCertificateChainFunction = Nomenclature::ProvideCertificateChainFunction;

/**
 * @brief Callback functions that check a peer's name against a whitelist.
 * @ingroup S31SdcCommon
 */
using WhitelistCheckFunction = Nomenclature::WhitelistCheckFunction;

/**
 * @brief Callback functions that provide a Role Authorization List.
 * @ingroup S31SdcCommon
 */
using ProvideRoleAuthorizationListFunction = Nomenclature::ProvideRoleAuthorizationListFunction;

/**
 * @brief Global S31.Core configuration.
 *
 * @details
 * Certificates and related configuration
 * ======================================
 * If no explicit configuration is done (i.e. setting the functions that provide certificates, whitelist,...) then
 * by default the according items from the crypto store are used.
 * This should be the preferred way for most users.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP CoreConfiguration
{
    public:
        CoreConfiguration();

        /**
         * @brief Update interval for crypto store cache.
         * @details
         * The DFL crypto store has non-deterministic access times. Therefore, the data is cached.
         * Specify the update interval for the low priority background job to update the cache asynchronously.
         */
        void setCryptoStoreCacheUpdateInterval(DFL::Chrono::Seconds interval);

        /**
         * @brief Disable periodic DFL crypto store cache updates.
         * @details
         * In case S31 customers are providing all crypto data by their own, it is recommended to disable the
         * periodic DFL crypto store cache update that S31 would do internally.
         */
        void disableCryptoStoreCacheUpdates();

        [[nodiscard]] boost::optional<DFL::Chrono::Seconds> getCryptoStoreCacheUpdateInterval() const noexcept;

        /**
         * @brief Set the function that provides root CAs.
         * @details If not set then by default the root CAs from the cached DFL crypto store are provided.
         * @see setCryptoStoreCacheUpdateInterval() for configuration.
         */
        void provideRootCasFunction(ProvideRootCasFunction f);
        /**
         * @brief Provides the configured root CAs.
         * @see provideRootCasFunction().
         */
        [[nodiscard]] DFL::Crypto::RootCas provideRootCas() const;

        /**
         * @brief Set the function that provides the private key.
         * @details If not set then by default the private key from the cached DFL crypto store is provided (if there is one).
         * @see setCryptoStoreCacheUpdateInterval() for configuration.
         */
        void providePrivateKeyFunction(ProvidePrivateKeyFunction f);
        /**
         * @brief Provides the configured private key.
         * @see providePrivateKeyFunction().
         */
        [[nodiscard]] boost::optional<DFL::Crypto::PrivateKey> providePrivateKey() const;

        /**
         * @brief Set the function that provides the certificate chain of this peer's certificate.
         * @details Certificate chain starting with the subjects certificate up to the root CA with all intermediate CAs in between.
         * If not set then by default the certificate chain from the cached DFL crypto store is provided (if there is one).
         * @see setCryptoStoreCacheUpdateInterval() for configuration.
         */
        void provideCertificateChainFunction(ProvideCertificateChainFunction f);
        /**
         * @brief Provides the configured certificate chain of this peer's certificate.
         * @see provideCertificateChainFunction().
         */
        [[nodiscard]] DFL::Crypto::CertificateChain provideCertificateChain() const;

        /**
         * @brief Sets the function to check whether a peer's common name is on the whitelist.
         * @details If not set then by default the whitelist from the cached DFL crypto store is used.
         * @see setCryptoStoreCacheUpdateInterval() for configuration.
         */
        void whitelistCheckFunction(WhitelistCheckFunction f);
        /**
         * @brief Checks the given peer against the configured whitelist check.
         * @see whitelistCheckFunction().
         */
        [[nodiscard]] Nomenclature::WhiteListingState whitelistCheck(const std::string& peer) const;

        /**
         * @brief Set the function that provides the Role Authorization List(RAL).
         * @details If not set then by default the RAL from the cached DFL crypto store is used.
         * @see setCryptoStoreCacheUpdateInterval() for configuration.
         */
        void provideRoleAuthorizationListFunction(ProvideRoleAuthorizationListFunction f);
        /**
         * @brief Provides the configured Role Authorization List(RAL).
         * @see provideRoleAuthorizationListFunction().
         */
        [[nodiscard]] DFL::Crypto::RoleAuthorizationList provideRoleAuthorizationList() const;

#if defined(S31_SUPPORT_DISABLE_SSL)
        /// Set @c true to prevent S31 from using SSL communication
        bool disableSslUsage;
#endif
        /**
         * @brief Maximum number of idle keep-alive outgoing connections.
         * @details It covers connections from a device to the client (event sink)
         * as well as from a client to a device (e.g., GetMDIB calls)
         */
        unsigned int maxIdleOutgoingConnections;

        /**
         * @brief Maximum number of idle keep-alive incoming connections.
         * @details On a device it covers requests such as GetMDIB or WS-Eventing subscribe.
         * In a client it is the max numbers of notifications connections.
         */
        unsigned int maxIdleIncomingConnections;

        /// Timeout duration for idle keep-alive connections.
        DFL::Chrono::Seconds idleTimeout;

        /// Maximum of concurrent SSL handshakes
        unsigned int maxConcurrentSslHandshakes;

        /// Maximum of concurrent outgoing running HTTP requests.
        unsigned int maxConcurrentOutgoingHttpRequests;

        /// Maximum of concurrent incoming running HTTP requests.
        unsigned int maxConcurrentIncomingHttpRequests;

        std::uint8_t udpMulticastTtl;

        bool disableLoopbackInterfaceFilter{false};

        /**
         * @brief Compression level for zip (only relevant on device side).
         * @details
         * Default is 1 which should be sufficient for Sdc.
         * If compression is not turned on (on device side) then this value has no effect.
         * Allowed value are 1 (fastest) .. 9 (slowest, more effective); 0 is also allowed but should be used only together with turned-off compression.
         */
        unsigned short compressionLevel{1};

        int httpIPv4Port;

        /**
         * @brief Port number to use for UDP WS-Discovery.
         * @details
         * This port is used to bind a UDP socket for WS-Discovery communication.
         * It is used for all outgoing (multicast and unicast) UDP messages
         * (Hello, Bye, Probe, Resolve, ProbeMatches, ResolveMatches)
         * and incoming unicast traffic (ProbeMatches, ResolveMatches).
         *
         * For incoming multicast traffic (Hello, Bye, Probe, Resolve) a different
         * UDP socket is used with the fixed port 3702 as specified in WS-Discovery:
         * http://docs.oasis-open.org/ws-dd/discovery/1.1/os/wsdd-discovery-1.1-spec-os.html#_Toc234231817
         *
         * When using the ANY (port 0) configuration a dynamic port number is
         * chosen from the dynamic port range of the operating system.
         */
        int udpIPv4Port;

        /**
         * @brief Deny some network interfaces for communication.
         * @details
         * In some scenarios blacklisting of network interfaces works better then whitelisting.
         * Example: IACS has 4 network interfaces, where specific ones shall not be used.
         */
        std::set<std::string> deniedInterfaces;

        /**
         * @brief Allow only specific network interfaces for SDC communication.
         * @details
         * If no network interfaces are specified, all available network interfaces are possible for communication.
         * Right now S31 officially only supports one interface, but multiple seem to work also (at least in some
         * setups).
         */
        std::set<std::string> allowedInterfaces;

        static constexpr int PORTNUMBER_DEFAULT_HTTPS = 6464;
        static constexpr int PORTNUMBER_DEFAULT_UDP = 6464;

        /**
         * @brief Setting this number leads to binding of sockets to an OS chosen (=random) port number.
         */
        static constexpr int PORTNUMBER_ANY = 0;
        static constexpr std::uint8_t DefaultUdpMulticastTtl = 15;

        std::vector<std::shared_ptr<X509_CRL> > certificateRevocationList;

        /**
         * @brief Application Level Transmission Delay
         * @details
         *
         * > ..., before sending some message types defined herein, a Target Service MUST wait
         * > for a timer to elapse before sending the message using the bindings described above. This timer
         * > MUST be set to a random value between 0 and APP_MAX_DELAY. (wsdd-discovery-1.1, 3.1.3 Application Level Transmission Delay)
         *
         * Default is 2500 milliseconds (by wsdd-dpws-1.1).
         *
         * @note Test use 100ms often, to run faster.
         */
        DFL::Chrono::Milliseconds customAppMaxDelay;

        /**
         * @copydoc S31::Sdc::ConnectionPriorityGroup
         */
        S31::Sdc::ConnectionPriorityGroup priorityGroup = S31::Sdc::ConnectionPriorityGroup::NoDelay;

        /**
         * @brief Optional Discovery Proxy (DP) in addition to multicast WS-Discovery.
         *
         * @details
         * For the DP an absolute URL is required, e.g., https://10.11.12.13:6464/discovery_proxy/.
         * The host can also be in the form of a hostname rather than a numerical ip, e.g., https://my-discovery-proxy/.
         * However, it is vital to include the "path" component of a URI, i.e. at least a '/' at the end is required.
         * For more information about valid URIs, refer to @ref DFL::Net::Uri.
         *
         * On Device side, the Discovery Proxy is used in addition to multicast, so that the implicit discovery
         * (with multicast Hello/Bye message) is supported as long as multicast works.
         * On Client side, the Discovery Proxy is preferred over multicast, so that discovery via multicast
         * is only done as a fallback solution in case the Discovery Proxy provides no suitable results.
         * (Suitable means: Errors or No/Empty {Probe/Resolve}Matches).
         *
         * When using the DP, SDC clients have to develop a strategy to find new devices. It has to consist of
         * - when do a probe for devices?
         * - what is a suitable value for @ref discoveryProxyProbeInterval?
         */
        boost::optional<DFL::Net::Uri> discoveryProxy;

        /**
         * @brief Enable QOS DSCP configuration.
         * @details Set @c true to configure DSCP @ref S31::Sdc::AssuredForwardingClass for all %SDC communication,
         *          @c false will disable any configuration of quality of service for all %SDC communications.
         */
        bool qosEnabled = false;

        /**
         * @brief @ref S31::Sdc::AssuredForwardingClass for high priority services.
         * @details Only applicable if @ref S31::CoreConfiguration::qosEnabled is @c true.  High priority services
         * include Get Service, Set Service, Context Service, Containment Tree Service, and Localization Service
         * (all services except Archive Service).
         * @note @ref S31::Sdc::AssuredForwardingClass::None will disable attempts to set quality of service
         * in case the platform environment cannot support it.
         */
        S31::Sdc::AssuredForwardingClass defaultQualityOfService = S31::Sdc::AssuredForwardingClass::AF22;

        /**
         * @brief @ref S31::Sdc::AssuredForwardingClass for Archive Service.
         * @details Only applicable if @ref S31::CoreConfiguration::qosEnabled is @c true.
         * @note @ref S31::Sdc::AssuredForwardingClass::None will disable attempts to set quality of service for Archive
         * in case the platform environment cannot support it.
         */
        S31::Sdc::AssuredForwardingClass archivingQualityOfService = S31::Sdc::AssuredForwardingClass::AF23;

        /**
         * @brief Timing between automated probes of the Discovery Proxy.
         *
         * @details If a discovery proxy is in use or a multicast error occurs, hello messages from devices on the network may be missed.
         * To receive probe matches of available devices from a discovery proxy, the client will automatically send periodic directed probe
         * messages to the proxy at a default frequency of every 5 minutes. These periodic probes will be sent iff a discovery proxy
         * address is provided in CoreConfiguration.
         */
        DFL::Chrono::Seconds discoveryProxyProbeInterval;

        /**
         * @brief Maximum number of concurrently running subscriptions on a device.
         * @details Note that a typical connection between a client and a device needs 2 subscriptions,
         * one for Mdib change notifications, and one for set operations' invocation reports. Both are
         * needed to establish a connection.
         *
         * This setting has no effect on client side.
         *
         * By default this is 1024K (virtually unlimited), for production environments this has to be
         * limited below this default value.
         */
        unsigned int maxConcurrentSubscriptionsOnDevice;

    private:

        ProvideRootCasFunction m_provideRootCas;
        ProvidePrivateKeyFunction m_providePrivateKey;
        ProvideCertificateChainFunction m_provideCertificateChain;
        WhitelistCheckFunction m_whitelistCheckFunction;
        ProvideRoleAuthorizationListFunction m_provideRoleAuthorizationList;
        boost::optional<DFL::Chrono::Seconds> m_cryptoStoreCacheUpdateInterval;
};

} /* namespace S31 */
