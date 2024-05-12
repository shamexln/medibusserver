#pragma once

#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Scheduling/IIdleKeepAliveSoapContextPool.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc::Impl
{
class IScheduling;
class SoapContextPool;
class OutgoingBlockingHttpRequest;
class HttpClientRegistry;

/**
 * \copydoc IOutgoingJobQueue
 *
 * The queue's length is limited to \b 5000. It throws on overflow.
 *
 * \todo Fix queue length.
 *
 * \ingroup S31SdcCommonScheduling
 */
class S31_CORE_EXPIMP OutgoingJobQueue : public IOutgoingJobQueue, public IIdleKeepAliveSoapContextPool
{
    public:
        OutgoingJobQueue(
                DFL::NotNull<std::shared_ptr<IScheduling>>        scheduling,
                DFL::NotNull<std::shared_ptr<SoapContextPool>>    soapPool,
                DFL::NotNull<std::shared_ptr<HttpClientRegistry>> httpClientRegistry);

        void setIdleTimeout(DFL::Chrono::Seconds idleTimeout) override;

        void setMaxNumberOfIdleSoapContexts(unsigned int maxNumberOfIdleSoapContexts) override;

        void jobFinishedFor(const std::string& peerTransportAddr, DFL::NotNull<SoapPtr> soapPtr) override;

        void jobFinishedFor(const std::string& peerTransportAddr) override;

        void addAsyncJob(DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> req) override;

        boost::optional<SoapPtr> getIdleSoapContextForTransport(const std::string& transportAddress) override;

    private:
        class OutgoingJobQueueImpl;
        std::shared_ptr<OutgoingJobQueueImpl> impl;
};

}
