#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{
class IOutgoingJobQueue;
class OutgoingBlockingHttpRequest;

/**
 * @brief Support queueing an Http request Job for delayed delivery
 * @details When executed, this Job adds the given @ref S31::Sdc::Impl::OutgoingBlockingHttpRequest
 * into the given @ref S31::Sdc::Impl::IOutgoingJobQueue.
 * This Job can be added to a scheduler main loop with a delay. Effectively, the
 * @ref S31::Sdc::Impl::OutgoingBlockingHttpRequest "http job" can be delayed in this manner.
 * @ingroup S31SdcCommon
 */
class QueueHttpJob: public Job
{
    public:
        QueueHttpJob(
                DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> job,
                DFL::NotNull<std::shared_ptr<IOutgoingJobQueue>>           jobQueue);

        void execute() override;
        std::string jobName() const override;

    private:
        std::unique_ptr<OutgoingBlockingHttpRequest> m_job;
        std::weak_ptr<IOutgoingJobQueue>             m_jobQueue;
};

}
