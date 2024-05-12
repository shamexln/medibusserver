#pragma once

#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Common/Scheduling/TimerTaskQueue.h>
#include <S31/S31CoreExImp.h>

#include <deque>
#include <memory>
#include <mutex>

namespace S31::Sdc
{
class Job;

namespace Impl
{

class ISocketSelect;
class IIdleKeepAliveSoapContextPool;

/**
 * \brief Implementation for \ref S31::Sdc::Impl::IScheduling.
 *
 * \ingroup S31SdcCommonScheduling
 */
class S31_CORE_EXPIMP SchedulingImpl: public IScheduling, public std::enable_shared_from_this<SchedulingImpl>
{
    public:
        SchedulingImpl();

        ~SchedulingImpl() override;

        JobPtrs executeMainLoopUntilNextHttpRequests(DFL::Chrono::Milliseconds timeout, MaxResultCount maxResultCount) override;
        void executeMainLoop(DFL::Chrono::Milliseconds timeout) override;

        void addOutgoingBlockingHttpRequest(DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> job) override;

        std::size_t pendingJobSize() const override;

        void addMainLoopTask(std::unique_ptr<Job> task, DFL::Chrono::Milliseconds executingDelay) override;
        void addMainLoopTask(std::unique_ptr<Job> task) override;

        void abortMainLoopExecution() override;

        void setMaxConcurrentOutgoingHttpRequests(unsigned int maxConcurrentRequests);
        void setMaxConcurrentIncomingHttpRequests(unsigned int maxConcurrentRequests);

        void setSocketSelect(std::weak_ptr<ISocketSelect> socketSelect);
        void setIdleSocketPool(std::weak_ptr<IIdleKeepAliveSoapContextPool> idleSocketPool);

    private:

        std::unique_ptr<Job> executeMainLoopAndProvideNextAsyncJob();
        std::unique_ptr<OutgoingBlockingHttpRequest> getNextOutgoingHttpRequestJob();

        void executePendingMainLoopTasks();

        DFL::Chrono::Milliseconds calculateTimeoutForBlockedNetworkIo(DFL::Chrono::Milliseconds requestedTimeout);
        DFL::Chrono::Milliseconds getTimeTillNextMainLoopTask();

        class HttpRequestCounter;
        std::shared_ptr<HttpRequestCounter> m_outgoingHttpRequestCounter;
        std::shared_ptr<HttpRequestCounter> m_incomingHttpRequestCounter;

        std::deque<std::unique_ptr<OutgoingBlockingHttpRequest>> m_outgoingHttpRequests;
        S31::Sdc::Impl::TimerTaskQueue m_mainLoopTasks;
        mutable std::mutex m_mutex;

        unsigned int m_maxOutgoingHttpRequestCount;

        std::weak_ptr<ISocketSelect> m_socketSelect;
        std::weak_ptr<IIdleKeepAliveSoapContextPool> m_idleSocketPool;
};

}
}
