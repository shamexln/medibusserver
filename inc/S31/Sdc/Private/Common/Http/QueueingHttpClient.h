#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/Http/HttpClient.h>
#include <S31/Sdc/Private/Common/Http/HttpClientRequest.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

namespace S31::Sdc::Impl
{
/**
 * @brief Queueing Https client adapter
 * @details This Https client provides @ref HttpClientRequest queueing based on the peer address.
 * Multiple requests to one peer address are queued and delivered in order. Requests to different
 * peer addresses are not queued.
 * @note It is required that this client is owned in a \c std::shared_ptr.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP QueueingHttpClient : public HttpClient, public std::enable_shared_from_this<QueueingHttpClient>
{
    DFL_NOT_COPYABLE(QueueingHttpClient)

public:
    /**
     * @brief Constructor taking ownership of an @ref HttpClient
     * @details Ready requests are forwarded to the owned client.
     */
    explicit QueueingHttpClient(DFL::NotNull<std::unique_ptr<HttpClient>> httpClient);

    /**
     * @brief Initiate a new request with @ref HttpClientRequest parameters.
     */
    void sendRequest(DFL::NotNull<std::unique_ptr<HttpClientRequest>> request) override;

private:
    void sendToUnderlyingClient(DFL::NotNull<std::unique_ptr<HttpClientRequest>> request);
    void sendNextRequest(const std::string& peerAddress);

    using RemotePeerQueueMap = std::map<std::string, std::queue<DFL::NotNull<std::unique_ptr<HttpClientRequest>>>>;

    DFL::NotNull<std::unique_ptr<HttpClient>> m_httpClient;

    std::mutex         m_queueMutex;
    RemotePeerQueueMap m_remotePeerQueues;
};

}  // namespace S31::Sdc::Impl
