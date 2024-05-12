#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/Sdc/Public/Common/JobPtrs.h>
#include <S31/Sdc/Public/Common/MaxResultCount.h>
#include <S31/Utils/Public/UniquePtrVector.h>

#include <Framework/Chrono/Public/Duration.h>

#include <memory>
#include <vector>

namespace S31::Sdc
{

class Job;

/**
 * @brief Job queue for @ref S31::Sdc::IDispatcher.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP IJobQueue
{
    public:
        virtual ~IJobQueue() noexcept = default;

        /**
         * @brief Runs task in %S31 main loop until next asynchronous jobs are available.
         * @param timeout Maximum time tasks are executed.
         * @param maxResultCount Limits the amount of jobs that will be returned.
         * @return returns A group of jobs. Can be empty. These are multiple jobs because of socket-select handling.
         */
        virtual Sdc::JobPtrs executeMainLoopUntilNextAsyncJobs(DFL::Chrono::Milliseconds timeout, Sdc::MaxResultCount maxResultCount) = 0;

        /**
         * @brief Runs tasks in %S31 without providing asynchronous jobs.
         * @details Call this method if there are no worker available for asynchronous execution.
         * @param timeout Maximum time tasks are executed
         */
        virtual void executeMainLoop(DFL::Chrono::Milliseconds timeout) = 0;

        /**
         * @brief Interrupts the blocking main loop call.
         */
        virtual void abortMainLoopExecution() = 0;

        virtual size_t getQSize() const = 0;
};

}
