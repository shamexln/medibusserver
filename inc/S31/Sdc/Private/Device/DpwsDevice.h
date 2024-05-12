#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Common/AtomicMetadataVersion.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Private/Common/SocketLayer/NetworkInterfaceUpdateList.h>
#include <S31/Sdc/Private/Common/UpdatedMessage.h>
#include <S31/Sdc/Private/Device/IHostedServiceUpdateListener.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/LocalUdpEndpointPort.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/CreateDiscoveryMessages.h>
#include <S31/Sdc/S31Only/DeviceDiscoveryTypes.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/LanguageTag.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/Utf8.h>

#include <atomic>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class HostedService;
class IOutgoingSender;
class NetworkInterfaceManager;
class IScheduling;
class IOutgoingJobQueue;
class ISoapContextPool;
class ContextData;

struct DpwsDeviceHttpPortTag;

/**
 * @brief Implementation of a DPWS device model with all its metadata.
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP DpwsDevice:
        public IHostedServiceUpdateListener,
        public std::enable_shared_from_this<DpwsDevice>
{
    public:
        using HttpPort = DFL::StrongTypedef<unsigned short, DpwsDeviceHttpPortTag>;

        DpwsDevice(const std::string& uuid,
                   S31::Sdc::MetadataVersion initialDpwsMetadataVersion,
                   std::shared_ptr<IScheduling> scheduling,
                   std::weak_ptr<IOutgoingSender> multicastSender,
                   std::weak_ptr<IOutgoingSender> unicastSender,
                   DFL::NotNull<std::shared_ptr<NetworkInterfaceManager>> networkInterfaceManager,
                   DFL::NotNull<std::shared_ptr<ISoapContextPool>> soapPool,
                   HttpPort httpPort,
                   DFL::Chrono::Milliseconds appMaxDelay,
    #if defined(S31_SUPPORT_DISABLE_SSL)
                   bool useSslCommunication,
    #endif
                   const std::shared_ptr<IOutgoingJobQueue>& outgoingJobQueue,
                   DeviceDiscoveryTypes discoveryTypes);

        ~DpwsDevice() override;

        /// @returns the URN (e.g., UUID) of the device
        const std::string& urn() const;
        std::string xAddrOfDevice(const std::string& deviceLocalIpAddress) const;

        /// \returns the SOAP-over-UDP endpoint of the device (for e.g. processing unicast Resolve messages from Discovery Proxy)
        boost::optional<DFL::Net::Uri> udpEndpointOfDevice(const std::string& deviceLocalIpAddress) const;

        using LocalizedTextsMap = std::map<DFL::Locale::LanguageTag, DFL::Locale::Utf8>;

        /**
         * @name ThisModel
         *
         * To express device characteristics that are typically fixed across all devices of the same model by their manufacturer.
         * <a href="http://docs.oasis-open.org/ws-dd/dpws/1.1/os/wsdd-dpws-1.1-spec-os.html#_Toc228672093">Specification</a> for ThisModel data elements.
         */
        ///@{

        /**
         * @brief Set the default manufacturer name.
         *
         * @param name sets the manufacturer name of the device (UTF-8 encoded).
         */
        void manufacturer(const DFL::Locale::Utf8& name);

        /**
         * @brief Its possible to set different manufacturer names for different languages.
         *
         * @param lang language code as specified in <a href="https://tools.ietf.org/html/rfc4646">RFC&nbsp;4646</a>,
         * e.g., en, en-US, de, de-DE.
         * Use consistent case to overwrite values in specific languages.
         *
         * @param name manufacturer name for that language (UTF-8 encoded).
         * (Use empty string as manufacturer name to remove a translation.)
         */
        void addManufacturer(const DFL::Locale::LanguageTag& lang, const DFL::Locale::Utf8& name);

        /**
         * @brief Provides the (localized) manufacturer map.
         */
        LocalizedTextsMap manufacturer() const;

        /**
         * @brief Website of the manufacturer.
         */
        void manufacturerUrl(const DFL::Locale::Utf8& url);

        /**
         * @brief Set model name (without language specification).
         */
        void modelName(const DFL::Locale::Utf8& name);

        /**
         * @brief Set model name (with language specification).
         */
        void addModelName(const DFL::Locale::LanguageTag& lang, const DFL::Locale::Utf8& name);

        /**
         * @brief Provides the (localized) model name map.
         */
        LocalizedTextsMap modelName() const;

        /**
         * @brief Set the model number.
         */
        void modelNumber(const DFL::Locale::Utf8& number);

        /**
         * @brief Set website for information about the device model.
         */
        void modelUrl(const DFL::Locale::Utf8& url);

        /**
         * @brief Web interface (on the device itself) for interactive remote control.
         */
        void presentationUrl(const DFL::Locale::Utf8& url);

        ///@}

        /**
         * @name ThisDevice
         *
         * To express device characteristics that typically vary from one device to another of the same kind.
         * <a href="http://docs.oasis-open.org/ws-dd/dpws/1.1/os/wsdd-dpws-1.1-spec-os.html#_Toc228672093">Specification</a> for ThisDevice data elements.
         */
        ///@{
        void friendlyName(const DFL::Locale::Utf8& name);
        void addFriendlyName(const DFL::Locale::LanguageTag& lang, const DFL::Locale::Utf8& name);
        LocalizedTextsMap friendlyName() const;
        void firmwareVersion(const DFL::Locale::Utf8& version);
        void serialNumber(const DFL::Locale::Utf8& serial);
        ///@}

        /**
         * @name (WS-)Discovery
         */
        ///@{
        void addDiscoveryType(DFL::QName qName);
        void addDiscoveryScope(const std::string& scope);
        void discoveryScopes(const std::vector<std::string>& scopes);

        /**
         * @brief Retrieves the current metadata version the DPWS device is using.
         *
         * It is (internally) incremented with each metadata update.
         */
        S31::Sdc::MetadataVersion metadataVersion() const;

        ///@}

        /**
         * @name Life-cycle
         */
        ///@{
        void start();
        void stop();
        bool isRunning() const;
        ///@}

        void sendHello();
        void sendDelayedHello(DFL::Chrono::Milliseconds delay);
        void sendBye();

        /**
         * @name Hosted Services
         */
        ///@{

        /**
         * Create a HOSTED SERVICE on this DPWS device.
         *
         * @param serviceId Value for the service (dpws:Relationship/dpws:Hosted/dpws:ServiceId)
         *
         * @note "Identifier for a HOSTED SERVICE which MUST be persisted
         * across re-initialization and MUST NOT be shared across multiple Hosted elements.
         * ServiceId MUST be unique within a DEVICE.
         * This value should be compared directly, as a case-sensitive string,
         * with no attempt to make a relative URI into an absolute URI,
         * to unescape, or to otherwise canonicalize it."
         */
        std::shared_ptr<S31::Sdc::Impl::HostedService> provideHostedService(const std::string& serviceId);

        /**
         * Retrieve an existing HOSTED SERVICE (or empty pointer).
         *
         * @param serviceId Value for the service (dpws:Relationship/dpws:Hosted/dpws:ServiceId)
         * @returns The desired object or an empty shared_ptr if the interface was not found.
         */
        std::shared_ptr<HostedService> hostedService(const std::string& serviceId) const;

        ///@}

        /**
         * Increases the current sequence number and returns it.
         * @returns Increased sequence number
         */
        AppSequenceMessageNumber increaseAppSequenceNumber();

        /**
         * Sets the discovery proxy address.
         */
        void discoveryProxyAddress(const boost::optional<DFL::Net::Uri>& discoveryProxyAddress,
                                   LocalUdpEndpointPort localUdpEndpointPort);

        // listeners
        void hostedServiceUpdated() override;

        // implementation function
        bool matchesTypes(const S31::Sdc::Impl::QNameList& types) const;
        int matchesScope(const std::vector<std::string>& scopes, const std::string& matchBy) const;
        std::string discoveryTypeList() const;
        std::string scopeList() const;
        DFL::Locale::Utf8 modelNumber() const;
        DFL::Locale::Utf8 modelUrl() const;
        DFL::Locale::Utf8 manufacturerUrl() const;
        DFL::Locale::Utf8 serialNumber() const;
        DFL::Locale::Utf8 firmwareVersion() const;
        DFL::Locale::Utf8 presentationUrl() const;
        std::string xAddrListForService(const std::string& localIp, const std::string& serviceId) const;
        std::map<std::string, std::shared_ptr<HostedService>> hostedServicesMap();

        unsigned short httpPort() const;

    private:
        void setDiscoveryMetadataUpdated();
        void setDpwsMetadataUpdated();
        void setDpwsMetadataReadNoLock() const;

        mutable std::mutex m_mutex;

        std::weak_ptr<IOutgoingSender> m_multicastSender;
        std::weak_ptr<IOutgoingSender> m_unicastSender;
        DFL::NotNull<std::shared_ptr<NetworkInterfaceManager>> m_networkInterfaceManager;
        std::shared_ptr<IScheduling> m_scheduling;
        std::weak_ptr<IOutgoingJobQueue> m_jobQueue;
        DFL::NotNull<std::shared_ptr<ISoapContextPool>> m_soapPool;
        HttpPort m_httpPort;
        DFL::Chrono::Milliseconds m_appMaxDelay;

        // model data
        const std::string m_uuid;
        DFL::Locale::Utf8 m_manufacturerUrl;
        AtomicMetadataVersion m_metadataVersion;
        LocalizedTextsMap m_manufacturer;
        LocalizedTextsMap m_modelName;
        DFL::Locale::Utf8 m_modelNumber;
        DFL::Locale::Utf8 m_modelUrl;
        DFL::Locale::Utf8 m_presentationUrl;
        LocalizedTextsMap m_friendlyName;
        DFL::Locale::Utf8 m_firmwareVersion;
        DFL::Locale::Utf8 m_serialNumber;
        S31::Sdc::Impl::QNameList m_discoveryTypes;
        std::map<std::string, std::shared_ptr<HostedService>> m_hostedServices;
        const unsigned int m_appSequenceInstanceId;
        std::atomic<unsigned int> m_appSequenceMessageNumber{0};
        boost::optional<DFL::Net::Uri> m_discoveryProxyAddress;
        LocalUdpEndpointPort m_localUdpEndpointPort{NoLocalUdpEndpointPort};

        // internal data
        mutable bool m_deviceDataRead{false};
        bool m_neverStarted{true};
        bool m_running{false};
        std::vector<std::string> m_discoveryScopes;
        std::shared_ptr<UpdatedMessage> m_lastHello;

        class NetIfChangeObserver;
        std::shared_ptr<NetIfChangeObserver> m_changeObserver;
    #if defined(S31_SUPPORT_DISABLE_SSL)
        bool m_useSslCommunication;
    #endif
};

}
