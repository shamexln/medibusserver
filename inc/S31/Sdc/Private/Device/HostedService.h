#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace S31::Sdc::Impl
{

class IWebService;
class IHostedServiceUpdateListener;
class IHostedServicePlugin;

/**
 * @brief Implementation of the model of a DPWS Hosted Services.
 * @details
 * Stores all the necessary metadata and a reference to the web services implementation (IWebService).
 * Allows for registering for metadata updates (registerUpdateListener())
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP HostedService
{
        DFL_NOT_COPYABLE(HostedService)

    public:
        /**
         * @brief Constructs a new HostedService instance.
         *
         * @param dpwsServiceId Device unique service id that is stable across cold boots.
         * @param dpwsDeviceEpr Device EndpointReference (typically a UUID)
         */
        HostedService(std::string dpwsServiceId, std::string dpwsDeviceEpr);

        ~HostedService();

        /**
         * @name Metadata
         */
        ///@{

        std::string getServiceId() const;

        /**
         * @brief Sets a pointer to a string where the WSDL for the corresponding web service is stored.
         * @details
         * It Is required for metadata exchange according to DPWS&nbsp;1.1 R2031.
         * @param dataLen size of char[]
         * @param data char[] pointer to WSDL strings
         * @param wsdlTotalLen length of the WSDL string
         */
        void setWSDLPointer(unsigned int dataLen, const char* data[], unsigned int wsdlTotalLen);

        /**
         * @brief Returns the pointer to the n-th chunk of the WSDL file.
         * @param offset Specifies the chunk (0 for first, 1 for second, ...)
         * @returns @c nullptr for out of bound read.
         */
        [[nodiscard]] const char* getWSDLPointer(unsigned int offset) const;

        /**
         * @brief Returns the string length for the n-th chunk of the WSDL file.
         * @param offset Specifies the chunk (0 for first, 1 for second, ...)
         * @returns @c strlen of chunk (0 for non-existing chunks).
         */
        [[nodiscard]] unsigned int getWSDLPointerLen(unsigned int offset) const;

        /**
         * @brief Total length of WSDL string.
         */
        [[nodiscard]] unsigned int getWsdlLength() const noexcept;

        /**
         * @brief Adds an XML QName to the Types element in the Hosted section in the Relationship of a DPWS Device.
         * @param serviceTypes pair of the namespace of the type and the (local) name of the XML QName
         */
        void addServiceTypes(QNameList serviceTypes);

        /**
         * @returns a string containing a list of QNames according to gSOAP format.
         */
        std::string getServiceTypesString() const;

        ///@}

        /**
         * @name Web service
         */
        ///@{

        /**
         * @brief Inject the web service.
         * @details
         * Typically the implementation is based on a @ref gSOAP generated service class from a WSDL file.
         */
        void setWebService(std::shared_ptr<IWebService> service);

        /**
         * @brief Access to injected web service.
         */
        std::shared_ptr<IWebService> getWebService() const;

        /**
         * @brief Register custom plugin.
         */
        void registerPlugin(DFL::NotNull<std::shared_ptr<IHostedServicePlugin>> plugin);
        ///@}

        void registerUpdateListener(std::weak_ptr<IHostedServiceUpdateListener> listener);
        std::vector<DFL::NotNull<std::shared_ptr<IHostedServicePlugin>>> plugins() const;

        void deviceShuttingDown();

    protected:
        /// Is called from setter function in case the metadata is updated.
        /// Takes care of calling registered listeners.
        void updated();

    private:
        const std::string m_serviceId;
        std::string m_deviceEprAddress;
        unsigned int m_wsdlPointerLen{0};
        const char** m_wsdlPointer{nullptr};
        unsigned int m_wsdlPointerCount{0};
        std::shared_ptr<IWebService> m_service;
        Sdc::Impl::QNameList m_serviceTypes;
        std::vector<std::weak_ptr<IHostedServiceUpdateListener>> m_updateListener;
        std::vector<DFL::NotNull<std::shared_ptr<IHostedServicePlugin>>> m_plugins;

};

}
