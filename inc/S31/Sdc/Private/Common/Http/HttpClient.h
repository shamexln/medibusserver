#pragma once

#include <S31/Sdc/Private/Common/Http/HttpClientRequestBuilder.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface for an Http Client.
 * @ingroup S31SdcCommon
 */
class HttpClient
{
public:
    virtual ~HttpClient() = default;

    /**
     * @brief Initiate a new request with @ref S31::Sdc::Impl::HttpClientRequest "HttpClientRequest" parameters.
     */
    virtual void sendRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> requestParameters) = 0;

    /**
     * @brief Support functions to create @ref HttpClientRequestBuilder instances.
     */
    /// @{
    static HttpClientRequestBuilder httpPost(const DFL::Net::Uri& httpsUrl);
    static HttpClientRequestBuilder httpGet(const DFL::Net::Uri& httpsUrl);
    /// @}
};

inline HttpClientRequestBuilder HttpClient::httpPost(const DFL::Net::Uri& httpsUrl)
{
    return {HttpMethod::Post, httpsUrl};
}

inline HttpClientRequestBuilder HttpClient::httpGet(const DFL::Net::Uri& httpsUrl)
{
    return {HttpMethod::Get, httpsUrl};
}

}
