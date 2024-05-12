#pragma once

#include <S31/Sdc/Private/Client/Metadata/IHostedServiceMetadata.h>
#include <S31/Utils/Public/Outcome.h>
#include <S31/Sdc/Private/Client/Metadata/DeviceMetadata.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/DirectedProbeJob.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IHelloByeObserver.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IProbeMatchesCallback.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/IResolveMatchesCallback.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeHttpJobResult.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/ProbeTargetType.h>
#include <S31/Sdc/Private/Common/CommunicationEndpoint.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/Common/WhitelistType.h>
#include <S31/Nomenclature/Test/Public/CertHelper.h>

#include <Framework/Utils/Public/Uri.h>

#include <string>
#include <utility>

namespace S31
{
class CoreConfiguration;
namespace Sdc
{
class IDispatcher;
namespace Impl
{
class IDiscoveryClient;

namespace Test
{
class DiscoveryQueryCallback;
class MetadataClient;

/**
 * @brief Indicates the type of the certificate to be generated.
 */
enum class CertificateType
{
       BasicConstraintCaTrue, ///< Generate a leaf certificate with basic constraint as CA = true
       Normal ///< Creates a normal leaf certificate with all roles.
};

/**
 * @brief Discovery client creates a DpwsClient for discovery, metadata exchange.
 */
class DiscoveryClient
{
    public:
        /**
         * @brief Creates a DpwsClient responsible for discovery, metadata exchange.
         *
         * @param metadataClientCertName is the file name of the certificate which is provided to metadata client.
         * @param certType is the enum indicating type pf certificate to be generated for the client.
         * @param whiteListType is the type of the whitelist to be generated.
         */
        explicit DiscoveryClient(const std::string& metadataClientCertName = "ITTestRunnerDev",
                                 CertificateType certType = CertificateType::Normal,
                                 S31::Sdc::Test::WhitelistType whiteListType = S31::Sdc::Test::WhitelistType::WildCard,
                                 S31::Utils::Test::CertHelper::ExtendedKeyUsage extendedKeyTypeEnum = S31::Utils::Test::CertHelper::ExtendedKeyUsage::WithAllRoles);

        /**
         * @name HostedServices
         */
        ///@{
        /// @brief Returns a list of hosted services from the remote device.
        std::vector<std::shared_ptr<IHostedServiceMetadata>> getHostedServices(const S31::Sdc::EndpointReference& urn);

        std::shared_ptr<IHostedServiceMetadata> getBicepsCombinedService(const S31::Sdc::EndpointReference& urn);

        std::shared_ptr<IHostedServiceMetadata> getService(const S31::Sdc::EndpointReference& urn, const DFL::QName& service);
        ///@}

        /**
         * @brief Attempts a metadata request but expects to fail
         */
        void triggerFailingMetadataRequest(const S31::Sdc::EndpointReference& urn);

        /**
         * @brief Trigger a probe.
         * @param urn device to probe, results contain only probe matches with this urn.
         */
        S31::Sdc::Impl::DirectedProbeJobResults triggerProbe(const S31::Sdc::EndpointReference& urn);

        /**
         * @brief Triggers a resolve from the client to device of given urn
         * @param urn device to probe
         */
        S31::Sdc::Impl::DirectedProbeJobResults triggerResolve(const S31::Sdc::EndpointReference& urn);

        /**
         * @brief Triggers a directed probe from the client to a particular address
         * @param urn address to probe
         */
        S31::Sdc::Impl::DirectedProbeJobResults triggerDirectedProbe(ProbeTargetType targetType, const S31::Sdc::EndpointReference& address);

        /**
         * @brief Provide information from WS-Transfer get.
         */
        S31::Sdc::Impl::DeviceMetadata getDeviceMetadata(const std::string& urn);
        S31::Sdc::Impl::DeviceMetadata getDeviceMetadata(const DFL::Net::Uri& urn);
        S31::Sdc::Impl::DeviceMetadata getDeviceMetadata(const S31::Sdc::EndpointReference& urn);

        /**
         * @brief Returns the endpoint address from device meta data.
         */
        /// @{
        std::string getMetadataXAddrs(const std::string& urn);
        std::string getMetadataXAddrs(const DFL::Net::Uri& urn);
        std::string getMetadataXAddrs(const S31::Sdc::EndpointReference& epr);
        std::string getHistoryMetadataXAddrs(const std::string& urn);
        std::string getHistoryMetadataXAddrs(const DFL::Net::Uri& urn);
        std::string getHistoryMetadataXAddrs(const S31::Sdc::EndpointReference& epr);
        std::string getAdtMetadataXAddrs(const std::string& urn);
        std::string getAdtMetadataXAddrs(const DFL::Net::Uri& urn);
        std::string getAdtMetadataXAddrs(const S31::Sdc::EndpointReference& epr);
        /// @}

        /**
         * @brief Getter for Metadata client.
         */
        std::shared_ptr<S31::Sdc::Impl::Test::MetadataClient> metadataClient() const;

        /**
         * @brief Getter for CommunicationEndpoint.
         */
        std::shared_ptr<S31::Sdc::Impl::CommunicationEndpoint> communicationEndpoint() const;

        /**
         * @brief Registers a listener for Hellos and Byes with the discoveryClient
         * @param listener the hello/bye listener
         */
        void registerListener(const std::shared_ptr<S31::Sdc::Impl::IHelloByeObserver>& listener);

    private:

        enum class ExpectedRequestResult
        {
                Failure,
                Success
        };
        std::vector<std::shared_ptr<IHostedServiceMetadata>> getHostedServices(const S31::Sdc::EndpointReference& urn, ExpectedRequestResult expectedResult);

        void createClient(const std::string& metadataClientCertName,
                          CertificateType certType,
                          S31::Sdc::Test::WhitelistType whiteListType,
                          S31::Utils::Test::CertHelper::ExtendedKeyUsage extendedKeyTypeEnum);

        S31::Sdc::Impl::DeviceMetadata getDeviceMetadata(const S31::Sdc::EndpointReference& urn, ExpectedRequestResult expectedResult);

        static S31::Sdc::Impl::DirectedProbeJobResults waitForCallbackDetails(const S31::Sdc::EndpointReference& urn, DiscoveryQueryCallback& callback);

        std::string getMetadataXAddrs(const S31::Sdc::EndpointReference& epr, const DFL::QName&  serviceName);

        std::shared_ptr<S31::Sdc::Impl::CommunicationEndpoint> m_dpwsEndpoint;
        std::shared_ptr<S31::Sdc::Impl::IDiscoveryClient> m_discoveryClient;
        std::shared_ptr<S31::Sdc::Impl::Test::MetadataClient> m_metadataClient;
        std::shared_ptr<S31::Sdc::IDispatcher> m_clientDispatcher;

};
}
}
}
}
