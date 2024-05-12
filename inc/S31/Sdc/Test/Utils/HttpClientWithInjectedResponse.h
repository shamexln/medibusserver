#pragma once


#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>
#include <S31/Sdc/Private/Common/Http/HttpResult.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31::Sdc::Impl::Test
{
/**
 * @brief Helper to inject a response body to an HttpClient request for tests.
 */
class HttpClientWithInjectedResponse : public HttpClient
{
public:
    struct RequestedMessage
    {
        std::string messageBody;
        std::string acceptEncoding;
    };

    explicit HttpClientWithInjectedResponse(std::string injectResponse);

    void sendRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters) override;

    const RequestedMessage& requestedMessage() const;

private:
    RequestedMessage m_requestedMessage;
    std::string m_injectedResponse;
};

inline HttpClientWithInjectedResponse::HttpClientWithInjectedResponse(std::string injectResponse)
    : m_injectedResponse(std::move(injectResponse))
{
}

inline void
HttpClientWithInjectedResponse::sendRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters)
{
    m_requestedMessage.acceptEncoding = requestParameters->acceptEncoding();

    // Capture the request message body
    const auto& requestBody = requestParameters->body();

    if (const auto* stringBody = std::get_if<std::string>(&requestBody))
    {
        m_requestedMessage.messageBody = *stringBody;
    }
    else if (const auto* creationFunction = std::get_if<CreateRequestBody>(&requestBody))
    {
        auto createBody = [](const CreateRequestBody& callable) -> std::string
        {
            if (callable)
            {
                ConnectionContext const connectionInfo{"127.0.0.1"};
                return callable(connectionInfo);
            }
            return {};
        };
        m_requestedMessage.messageBody = createBody(*creationFunction);
    }

    // Complete with injected response.
    HttpResult result{
            HttpContentTypeView{"application/soap+xml"},
            HttpContentEncodingView{},
            m_injectedResponse,
            DFL::asNotNull(std::make_shared<S31::Sdc::Impl::HttpSessionContext>(
                    S31::Sdc::Impl::ConnectionDirection::Outgoing))};

    requestParameters->notifyCompletion(result);
}

inline const HttpClientWithInjectedResponse::RequestedMessage& HttpClientWithInjectedResponse::requestedMessage() const
{
    return m_requestedMessage;
}

}  // namespace S31::Sdc::Impl::Test
