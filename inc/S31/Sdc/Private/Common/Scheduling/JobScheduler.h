#pragma once

#include <S31/Sdc/Public/Common/IJobQueue.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <memory>

namespace S31::Sdc::Impl
{
class IScheduling;

/**
 * @brief Class to get scheduled S31 jobs.
 * @details Acts as a facade to the dsoap scheduler.
 * @ingroup S31SdcCommonScheduling
 */
class S31_CORE_EXPIMP JobScheduler: public IJobQueue
{
        DFL_NOT_COPYABLE(JobScheduler)
    public:
        explicit JobScheduler(const std::shared_ptr<Sdc::Impl::IScheduling>& scheduler);
        ~JobScheduler() noexcept override = default;

        JobPtrs executeMainLoopUntilNextAsyncJobs(DFL::Chrono::Milliseconds timeout, MaxResultCount maxResultCount) override;

        void executeMainLoop(DFL::Chrono::Milliseconds timeout) override;

        void abortMainLoopExecution() override;

        size_t getQSize() const override;

    private:
        std::weak_ptr<S31::Sdc::Impl::IScheduling> m_scheduler;
};

}
