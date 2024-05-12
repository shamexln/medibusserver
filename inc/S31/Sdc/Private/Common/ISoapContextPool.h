#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>

#include <Framework/Utils/Public/NotNull.h>

#include <functional>

namespace S31::Sdc::Impl
{

/**
 * @brief A pool of \ref gSOAP soap contexts.
 *
 * @details
 * Use this pool for all required soap contexts used for communication in dSOAP.
 * Additional functionality (gSOAP plug-ins) will be used for WS-Addressing for example.
 * Later on it may be possible to add HTTP keep-alive for example.
 *
 * @ingroup S31SdcCommon
 */
class ISoapContextPool
{
    public:
        virtual ~ISoapContextPool() = default;

        /**
         * Get a soap context for HTTP communication.
         *
         * The timeouts etc. are set for TCP communication.
         */
        virtual DFL::NotNull<SoapPtr> getSoapPtr() = 0;

        /**
         * Get a soap context for UDP communication.
         *
         * The soap context is pre-configured for UDP (e.g., the timeouts are set to a minimum).
         */
        virtual DFL::NotNull<SoapPtr> getUdpSoapPtr() = 0;

        /**
         * Set the peer authorization callback for an ssl connection.
         */
        using PeerAuthorizationCallback = std::function<int(int, X509_STORE_CTX*)>;
        virtual void setPeerAuthorizationCallback(const PeerAuthorizationCallback& callback) = 0;
};

}
