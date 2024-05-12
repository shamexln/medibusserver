#pragma once

#include <S31/AsioDispatch/Public/Executor.h>
#include <S31/Sdc/Private/Common/Http/SslHandshakeBroker.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <mutex>
#include <queue>

namespace S31
{
namespace AsioDispatch
{
class ExecutorProvider;
}

namespace Sdc::Impl
{

/**
 * @brief Implements a queue to limit the amount of concurrent SSL handshakes.
 * @details This queue additionally takes an executor, to allow handshakes to
 * run on a different execution context than the normal processing of a tcp stream.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP SslHandshakeBrokerImpl : public SslHandshakeBroker,
                                               public std::enable_shared_from_this<SslHandshakeBrokerImpl>
{
public:
    /**
     * @brief Constructs a queue with initial maximum count of allowed concurrent SSL handshakes.
     */
    SslHandshakeBrokerImpl(
            DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> executorProvider, unsigned int maxCount);

    /**
     * @brief Request a new asio SSL handshake request to be performed.
     * @note The caller must ensure that the lifetime of the ssl stream
     * is longer than the completion handler.  This can be achieved (for
     * example) by capturing shared_from_this of the object owning the stream
     * in the completion handler.
     */
    void
    add(boost::beast::ssl_stream<boost::asio::ip::tcp::socket>& stream,
        boost::asio::ssl::stream_base::handshake_type           type,
        std::chrono::seconds                                    timeout,
        std::function<void(boost::system::error_code)>          completion) override;

private:
    class Request;
    void start(std::shared_ptr<Request> request);
    void finished();
    std::shared_ptr<Request> popRequestOrIncrementAvailable();

    // Ensure lifetime of the executor provider
    DFL::NotNull<std::shared_ptr<AsioDispatch::ExecutorProvider>> m_executorProvider;

    AsioDispatch::Executor               m_executor;
    std::queue<std::shared_ptr<Request>> m_pendingOutgoing;
    std::queue<std::shared_ptr<Request>> m_pendingIncoming;

    std::mutex   m_mutex;
    unsigned int m_available;
};

}  // namespace Sdc::Impl
}  // namespace S31
