#pragma once

#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class IWebService;

/**
 * @brief Abstract base class for an incoming network request.
 * @details Serves one soap request (should be called in a new process/task/thread if it blocks).
 * @ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP IncomingNetworkRequest
{
        DFL_NOT_COPYABLE(IncomingNetworkRequest)
    protected:
        IncomingNetworkRequest(DFL::NotNull<SoapPtr> soapPtrIn, std::shared_ptr<IWebService> webService);

    public:
        /**
         * @brief Call this function to pre-parse the SOAP header.
         * @details This is useful for UDP datagrams, since they do not block and a first filtering
         * for duplicate message IDs is possible.
         */
        virtual void parseSoapHeader();

        /**
         * @brief Call this function to fully dispatch the SOAP message.
         */
        void serveRequest();

        [[nodiscard]] DFL::NotNull<struct soap*> getSoapHandle() const;

        virtual ~IncomingNetworkRequest() = default;

    protected:
        /**
         * @brief Will be called before reading data from socket.
         */
        virtual void preReceiveHook();

        /**
         * @brief Will be called after dispatching the whole SOAP message.
         */
        virtual void postDispatchHook();

        /**
         * @brief Intended to be used in derived classes to write log messages (in the error case)
         */
        virtual void logOnError() { /* No operation by default */ }

        [[nodiscard]] SoapPtr& soapPtr();
        [[nodiscard]] const SoapPtr& soapPtr() const;

        virtual void handleSoapError();

    private:
        SoapPtr m_soapPtr;
        std::shared_ptr<IWebService> m_webService;
        bool m_headerParsed{false};
        bool m_soapErrorHandled{false};
};

}
