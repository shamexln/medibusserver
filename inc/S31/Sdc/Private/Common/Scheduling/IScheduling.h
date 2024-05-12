#pragma once

#include <S31/Sdc/Public/Common/Job.h>
#include <S31/Sdc/Public/Common/JobPtrs.h>
#include <S31/Sdc/Public/Common/MaxResultCount.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <vector>

namespace S31::Sdc::Impl
{
class OutgoingBlockingHttpRequest;

/**
 * @brief Public entry point for dSOAP scheduling.
 * @details
 * HTTP requests are implemented with blocking IO.
 * They have to run in worker threads to avoid a delay in the execution of other tasks.
 * All other tasks shall run in the S31 main loop, since they do not block.
 *
 * @ingroup S31SdcCommonScheduling
 */
class IScheduling
{
    public:
        virtual ~IScheduling() = default;

        /**
         * @name S31 main loop
         */
        ///@{

        /**
         * @brief Runs the S31 main loop until the next HTTP requests are available.
         * @param timeout Maximum time the main loop shall be running.
         * @param maxResultCount limits the number of returned jobs.
         * @return New HTTP requests to be executed in a worker context or empty (e.g., in case of timeout).
         */
        virtual JobPtrs executeMainLoopUntilNextHttpRequests(DFL::Chrono::Milliseconds timeout, MaxResultCount maxResultCount) = 0;

        /**
         * @brief Runs the S31 main loop for the given time.
         * @param timeout Maximum time the main loop shall be running.
         */
        virtual void executeMainLoop(DFL::Chrono::Milliseconds timeout) = 0;

        /**
         * @brief Interrupts the blocking main loop call.
         */
        virtual void abortMainLoopExecution() = 0;

        ///@}

        /**
         * @brief Outgoing HTTP requests are queued until a free worker executes them.
         * @param job Job with outgoing HTTP request.
         */
        virtual void addOutgoingBlockingHttpRequest(DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> job) = 0;

        /**
         * Provides the number of currently pending jobs.
         */
        virtual std::size_t pendingJobSize() const = 0;

        /**
         * @brief Add a non-block task.
         * @details The non-blocking task will be run in the S31 main loop.
         *
         */
        virtual void addMainLoopTask(std::unique_ptr<Job> job, DFL::Chrono::Milliseconds executingDelay) = 0;


        void addMainLoopTask(std::unique_ptr<Job> job, std::chrono::milliseconds executingDelay)
        {
            addMainLoopTask(std::move(job), DFL::Chrono::Milliseconds{executingDelay.count()});
        }

        /**
         * @brief Add a non-block task that is immediately executed.
         * @details The non-blocking task will be run in the S31 main loop.
         *
         */
        virtual void addMainLoopTask(std::unique_ptr<Job> job) = 0;

};

}
