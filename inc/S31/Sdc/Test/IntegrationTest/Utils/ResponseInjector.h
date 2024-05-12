#pragma once

#include <S31/Gsoap/Test/NonConnectingSoap.h>
#include <S31/Sdc/Private/Common/SoapPtr.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestFunctionsHelper.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/BicepsTestTypes.h>
#include <S31/Sdc/Test/Public/Common/SoapContextPoolMock.h>
#include <S31/Sdc/Test/Utils/HttpClientRegistryMock.h>
#include <S31/Sdc/Test/Utils/HttpClientWithInjectedResponse.h>

#include <istream>
#include <memory>
#include <ostream>
#include <sstream>

namespace S31Test::Sdc
{
using S31::Sdc::Impl::Test::HttpClientWithInjectedResponse;
using S31::Sdc::Impl::Test::HttpClientRegistryMock;

/**
 * @brief Helper to inject a response e.g. into a job derived of @ref S31::Sdc::Impl::OutgoingBlockingHttpRequest.
 */
class ResponseInjector
{
    public:
        explicit ResponseInjector(const InjectedResponseFilename& response, SoapXmlFormat outputFormat = SoapXmlFormat::Indent)
            : m_injectedSoapResponse(readXmlFile(response.get()).str())
            , m_soapPool(create(m_injectedSoapResponse, m_receivedSoapRequest, outputFormat))
            , m_mockClient(std::make_shared<HttpClientWithInjectedResponse>(injectedSoapResponse()))
            , m_mockClientRegistry(std::make_shared<HttpClientRegistryMock>(m_mockClient))
        {
        }

        explicit ResponseInjector(std::istream& response, SoapXmlFormat outputFormat = SoapXmlFormat::Indent)
            : m_injectedSoapResponse(copyStream(response))
            , m_soapPool(create(m_injectedSoapResponse, m_receivedSoapRequest, outputFormat))
            , m_mockClient(std::make_shared<HttpClientWithInjectedResponse>(injectedSoapResponse()))
            , m_mockClientRegistry(std::make_shared<HttpClientRegistryMock>(m_mockClient))
        {
        }

        explicit ResponseInjector(const InjectedResponse& response, SoapXmlFormat outputFormat = SoapXmlFormat::Indent)
            : m_injectedSoapResponse(response.get())
            , m_soapPool(create(m_injectedSoapResponse, m_receivedSoapRequest, outputFormat))
            , m_mockClient(std::make_shared<HttpClientWithInjectedResponse>(injectedSoapResponse()))
            , m_mockClientRegistry(std::make_shared<HttpClientRegistryMock>(m_mockClient))
        {
        }

        /// soap context pool containing the one fake context with the injected response
        std::shared_ptr<S31::Sdc::Test::SoapContextPoolMock>& soapPool()
        {
            return m_soapPool;
        }

        /// http client registry containing the one fake http client with the injected response
        std::shared_ptr<S31::Sdc::Impl::HttpClientRegistry> httpClientRegistry()
        {
            return m_mockClientRegistry;
        }

        /// The content of the given injected response
        std::string injectedSoapResponse() const
        {
            return m_injectedSoapResponse.str();
        }

        std::string receivedSoapRequest() const
        {
            return m_receivedSoapRequest.str();
        }

    private:
        static std::shared_ptr<S31::Sdc::Test::SoapContextPoolMock> create(
                std::istream& soapResponse,
                std::ostream& soapRequest,
                SoapXmlFormat outputFormat)
        {
            // output stream is only used to suppress printing to stdout
            auto soapPtr = newSoapPtr(soapResponse, soapRequest, outputFormat);
            // to prevent gSoap from opening network socket
            S31::Gsoap::Test::deactivateSocketHandling(soapPtr);
            return std::make_shared<S31::Sdc::Test::SoapContextPoolMock>(std::move(soapPtr));
        }

        static std::string copyStream(std::istream& source)
        {
            std::stringstream destination;
            destination << source.rdbuf();
            return destination.str();
        }

        std::ostringstream m_receivedSoapRequest;
        std::istringstream m_injectedSoapResponse;
        std::shared_ptr<S31::Sdc::Test::SoapContextPoolMock> m_soapPool;

        std::shared_ptr<HttpClientWithInjectedResponse> m_mockClient;
        std::shared_ptr<HttpClientRegistryMock>         m_mockClientRegistry;
};

}
