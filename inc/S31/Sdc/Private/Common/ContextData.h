#pragma once

#include <S31/Nomenclature/Public/Credentials.h>
#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/SdcMessageObserverRegistry.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/Sdc/Private/Common/SocketLayer/QualityOfService.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/EnumClass.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Oids.h>

#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace S31
{
class CoreConfiguration;

namespace Sdc::Impl
{
class SocketController;
class IScheduling;
class LocalDeviceRegistry;
class ISslHandshakeSemaphore;
class HttpSessionContext;

/**
 * @brief Passes data into the dispatch methods implemented.
 *
 * @details @ref gSOAP generated the skeleton for the Web services operations.
 * To pass in data it has to be attached to to the <tt>struct soap</tt> handle.
 * The implementation will attach an instance of this class to the <tt>void* user</tt> member in the <tt>soap struct</tt>.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ContextData
{
        DFL_NOT_COPYABLE(ContextData)
    public:
        /// Creates new object that is already marked as 'in use'.
        ContextData();
        ~ContextData();

        std::shared_ptr<LocalDeviceRegistry> deviceRegistry() const;
        void deviceRegistry(std::weak_ptr<LocalDeviceRegistry> deviceRegistry);

        void sslHandshakeSemaphore(std::weak_ptr<ISslHandshakeSemaphore> sslHandshakeSemaphore);
        std::shared_ptr<ISslHandshakeSemaphore> sslHandshakeSemaphore() const;

        void sdcMessageObserverRegistry(std::weak_ptr<SdcMessageObserverRegistry> sdcMessageObserverRegistry);

        std::shared_ptr<SdcMessageObserverRegistry> sdcMessageObserverRegistry() noexcept;

        void clearData();

        void localIp(const std::string& ip);
        const std::string& localIp() const;
        void localPort(std::uint16_t port);
        std::uint16_t localPort() const;
        void remoteIp(const std::string& ip);
        const std::string& remoteIp() const;
        void remotePort(std::uint16_t port);
        std::uint16_t remotePort() const;

        void credentials(const S31::Nomenclature::Credentials& credentials);
        void credentials(S31::Nomenclature::Credentials&& credentials);
        const S31::Nomenclature::Credentials& credentials() const;

        void httpSessionContext(DFL::NotNull<std::shared_ptr<const HttpSessionContext>> context);
        std::shared_ptr<const HttpSessionContext> httpSessionContext() const;

        /**
         * To avoid a out of memory situation when receiving incoming SOAP messages,
         * we can limit the amount of data for each request.
         * (The incoming data is cropped.)
         * \param[in] length max size of byte for one web service request
         */
        ///@{
        void maxInboundSize(size_t length);
        size_t maxInboundSize() const;
        ///@}

        size_t maxOutboundSize() const;

        size_t inboundByteCount() const;
        void addInboundByteCount(size_t in);
        size_t outboundByteCount() const;
        void addOutboundByteCount(size_t out);

        void resetByteCounts() noexcept;

        void socketFamily(sa_family_t family);
        sa_family_t socketFamily() const;
        void interfaceIndex(unsigned int ifIndex);
        unsigned int interfaceIndex() const;

        /**
         * @name Last outbound message
         * @brief The raw last message sent.
         * @details Only available in DEBUG mode.
         * @{
         */
        const std::string& lastOutboundMessage() const;
        void addToLastOutboundMessage(const char *msg, std::size_t msgLen);
        void clearLastOutboundMessage();
        ///@}

        /**
         * @name Last inbound message
         * @brief The last XML SOAP message received.
         * @{
         */
        const std::string& lastInboundMessage() const;
        void addToLastInboundMessage(const char *msg, std::size_t msgLen);
        void clearLastInboundMessage() noexcept;
        ///@}

        void configuration(const std::shared_ptr<CoreConfiguration>& config);
        std::shared_ptr<CoreConfiguration> configuration() const;

        void acceptEncoding(std::string_view enc);
        const std::string& acceptEncoding() const;

        void remoteDeviceEpr(const S31::Sdc::EndpointReference& epr);
        const boost::optional<S31::Sdc::EndpointReference>& remoteDeviceEpr() const;

        enum class ConnectionDirection
        {
            Incoming,
            Outgoing
        };
        void connectionDirection(ConnectionDirection direction);
        ConnectionDirection connectionDirection() const;

        /**
         * @brief Peer EKU roles required for authorization during TLS handshake
         * @details For outgoing connections, specific roles in the peer certificate
         * may be requested for checking during TLS handshake.  If the list is empty,
         * a default set of roles will be checked (SdcProvider or SdcConsumer).
         */
        ///@{
        void requirePeerRolesForHandshake(const DFL::Oids& peerRoles);
        const DFL::Oids& requiredPeerRolesForHandshake() const;
        ///@}

        /**
         * @name Status
         * @brief Handling of the status of the ContextData object itself.
         * @details The functions are thread safe (in regard to their use cases).
         */
        ///@{

        /// @return true if object was in use and is now marked for deletion
        [[nodiscard]] bool markForDeletionIfInUse();

        /// @returns true if the object is now set as used (and was not before)
        [[nodiscard]] bool tryMarkAsUsed();

        enum class DeletionStatus
        {
            deletionRequested,
            deletionNotRequested
        };

        [[nodiscard]] DeletionStatus markUnused();

        ///@}

        /**
         * @name Tls Connection Status
         * @brief Record if a TLS connection is made successfully, or if error is observed
         */
        ///@{
        void markTlsConnectionSuccess();
        bool tlsConnectionSuccess() const;
        void tlsConnectionError(const Utils::Error& error);
        void tlsConnectionError(Utils::Error&& error);
        const boost::optional<Utils::Error>& tlsConnectionError() const;
        void clearTlsConnectionStatus();
        ///@}

        /// @brief Access quality of service configuration
        QualityOfService& qualityOfService();

        /// @brief Save and restore soap header
        /// @details soap_wsa_reply will replace the soap header with a new header
        /// containing new %WSA header information.  If a fault is detected later, the
        /// original request header needs to be restored so that the %WSA headers for
        /// fault will be derived from the original request.
        ///@{
        void saveSoapHeader(const soap& soapHandle);
        void restoreSoapHeader(soap& soapHandle);
        ///@}

        /// @brief Flag to discard a soap fault
        /// @details Work around gSoap Fault forwarding, such that if a fault should be
        /// discarded (ie. due to wsa:FaultTo address), delay sending empty response
        /// until after fault has been logged or otherwise handled completely.
        ///@{
        void discardSoapFault(bool discard);
        bool discardSoapFault() const;
        ///@}

        /// @brief Clean up per-message data for customized fault handling
        void clearFaultMessagePreparations();

        static ContextData& getContext(const soap& soapHandle);
        static ContextData& getContext(const DFL::NotNull<soap*>& soapHandle);
        static ContextData& getContext(const DFL::NotNull<SoapPtr>& soapPtr);

    private:
        std::weak_ptr<LocalDeviceRegistry> m_deviceRegistry;
        std::weak_ptr<ISslHandshakeSemaphore> m_sslHandshakeSemaphore;
        std::weak_ptr<SdcMessageObserverRegistry> m_sdcMessageObserverRegistry;
        std::string m_local_ip;
        std::string m_remote_ip;
        boost::optional<S31::Sdc::EndpointReference> m_remoteDeviceEpr;
        std::uint16_t m_localPort{0};
        std::uint16_t m_remotePort{0};
        std::string m_acceptEncoding;
        ConnectionDirection m_connectionDirection;
        DFL::Oids m_requiredPeerRoles;

        size_t m_maxInboundByte;
        size_t m_inboundByteCount{0};

        size_t m_maxOutboundByte;
        size_t m_outboundByteCount{0};

        sa_family_t m_socketFamily{0};
        unsigned int m_ifIndex{0};
        std::string m_lastOutboundMessage;
        std::string m_lastInboundMessage;
        std::shared_ptr<CoreConfiguration> m_configuration;
        bool m_isUsed{true};
        bool m_markDeletion{false};

        bool m_tlsConnectionSuccess{false};
        boost::optional<Utils::Error> m_tlsConnectionError;

        S31::Nomenclature::Credentials m_credentials;
        QualityOfService m_qualityOfService;

        // HttpSessionContext provides an alternate source of Credentials, local, and remote endpoint information.
        // It will be used if available to provide those fields.
        std::shared_ptr<const HttpSessionContext> m_httpSessionContext;

        mutable std::mutex m_mutex;

        // Header is owned by soap handle, this is only an observing pointer.
        SOAP_ENV__Header* m_savedSoapHeader{nullptr};
        bool m_discardFault{false};
};

inline ContextData& ContextData::getContext(const soap& soapHandle)
{
    return *static_cast<ContextData*>(soapHandle.user);
}

inline ContextData& ContextData::getContext(const DFL::NotNull<soap*>& soapHandle)
{
    return *static_cast<ContextData*>(soapHandle->user);
}

inline ContextData& ContextData::getContext(const DFL::NotNull<SoapPtr>& soapPtr)
{
    return getContext(*soapPtr.get());
}

DFL_ENUM_CLASS_STREAM_OPERATOR(ContextData::ConnectionDirection, (Incoming)(Outgoing))

}
}
