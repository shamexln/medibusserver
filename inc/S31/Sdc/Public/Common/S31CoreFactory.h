#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Safety/Public/Requirement.h>
#include <S31/Sdc/Public/Common/CommunicationEndpoint.h>
#include <S31/Sdc/Public/Common/CompressionConfiguration.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/InstanceIdentifiersUtil.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/Sdc/Public/Device/LocalMdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Public/Device/MedicalDeviceData.h>
#include <S31/Sdc/Public/Device/MedicalDpwsData.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Oids.h>

#include <boost/optional/optional.hpp>

#include <deque>
#include <memory>
#include <string>

namespace S31
{
namespace Sdc
{
class IDispatcher;
class Client;
class LocalDevice;
class DiscoveryProvider;

namespace Impl
{
class CommunicationEndpoint;
class DiscoveryProvider;
}
}

namespace Localization::Device
{
class LocalizedTextStore;
}

/**
 * @brief Entry point for @ref S31Sdc devices and clients.
 *
 * @details Use an instance of this class to create biceps clients and devices for SDC network communication.
 * The instance requires an @ref S31::Sdc::IDispatcher to allow asynchronous execution of, e.g., network communication.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP S31CoreFactory
{
    public:
        /**
         * @brief Creates an instance for network communication.
         *
         * @details It requires a dispatcher for asynchronous execution (of network requests) and
         * is able to restrict the communication to a specific network interface.
         */
        S31CoreFactory(DFL::NotNull<std::shared_ptr<S31::Sdc::IDispatcher>> dispatcher,
                       const CoreConfiguration& configuration);

        /**
         * @brief Creates an Discovery provider to discover devices in the network.
         */
        std::shared_ptr<Sdc::DiscoveryProvider> createDiscoveryProvider() const;

        /**
         * @brief Creates a Biceps client (SDC consumer) to work with Biceps devices (SDC providers) in the network.
         * @details Allows to discover and to connect to devices.
         */
        std::shared_ptr<Sdc::Client> createBicepsClient() const;

        /**
         * @brief DEPRECATED: Creates a local Biceps device to provide services (e.g., measurements, remote control) to
         * client in the network. Includes types to indicate Sdc Compliance.
         *
         * @deprecated Use other version with container parameters.
         *
         * @param endpointReference The BICEPS device's persistent identifier  (e.g., urn:uuid:a99d2381-3a45-4bc2-98a2-bac92f021f2f).
         * @param initialMetadataVersion
         * @param localMdibAccess
         * @param localizedTextStore Pointer to a localized text store to enable device usage of Localization Service
         * @param shallCompress
         * @param keyPurposes Set of requirements an SDC participant is complying with.
         */
        std::shared_ptr<Sdc::LocalDevice> createBicepsDevice(S31::Sdc::EndpointReference endpointReference,
                                                             S31::Sdc::MetadataVersion initialMetadataVersion,
                                                             const DFL::NotNull<S31::Sdc::LocalMdibAccessSharedPtr>& localMdibAccess,
                                                             const std::shared_ptr<Localization::Device::LocalizedTextStore>& localizedTextStore,
                                                             S31::Sdc::CompressionConfiguration shallCompress,
                                                             const DFL::Oids& keyPurposes = DFL::Oids()) const;

        /**
         * @brief Creates a local Biceps device to provide services (e.g., measurements, remote control) to client in
         *        the network. Includes types to indicate Sdc Compliance.
         * @param dpwsData Contains all relevant information for network communication based on MDPWS (WS-Discovery and DPWS)
         * @param medicalData Contains medical data (e.g., MDIB and corresponding data like localized text store)
         */
        std::shared_ptr<Sdc::LocalDevice>
        createBicepsDevice(Sdc::MedicalDpwsData dpwsData, Sdc::MedicalDeviceData medicalData) const;

        /**
         * @brief Access to functionality of communication endpoint.
         * @details It is for all created devices and clients relevant.
         */
        std::shared_ptr<Sdc::CommunicationEndpoint> communicationEndpoint() const;
    private:
        std::shared_ptr<S31::Sdc::Impl::DiscoveryProvider> createDiscoveryProviderImpl() const;

        DFL::NotNull<std::shared_ptr<S31::Sdc::IDispatcher>> m_dispatcher;
        std::shared_ptr<S31::Sdc::Impl::CommunicationEndpoint> m_communicationEndpoint;
        DFL::NotNull<std::shared_ptr<CoreConfiguration>> m_configuration;
};

}
