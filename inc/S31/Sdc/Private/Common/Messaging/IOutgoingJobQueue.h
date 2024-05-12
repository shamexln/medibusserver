#pragma once

#include <S31/Sdc/Private/Common/SoapPtr.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <string>


namespace S31::Sdc::Impl
{
class OutgoingBlockingHttpRequest;

/**
 * Interface for outgoing client requests.
 *
 * A client can start jobs to get information about a
 * remote devices.
 *
 * \ingroup S31SdcCommonScheduling
 */
class IOutgoingJobQueue
{
    public:
        virtual ~IOutgoingJobQueue() noexcept = default;

        /**
         * Set the maximum idle HTTP keep-alive connection in \ref gSOAP soap contexts.
         */
        virtual void setMaxNumberOfIdleSoapContexts(unsigned int maxNumberOfIdleSoapContexts) = 0;

        /**
         * Set the timeout for outgoing HTTP keep-alive connections.
         */
        virtual void setIdleTimeout(DFL::Chrono::Seconds idleTimeout) = 0;

        /**
         * Send the job finished information to the queue.
         */
        virtual void jobFinishedFor(const std::string& peerTransportAddr, DFL::NotNull<SoapPtr> soapPtr) = 0;

        /**
         * Send the job finished information to the queue.
         */
        virtual void jobFinishedFor(const std::string& peerTransportAddr) = 0;

        /**
         * Queue a job for asynchronous execution.
         * The job will be executed as soon as a thread is free for processing.
         */
        virtual void addAsyncJob(DFL::NotNull<std::unique_ptr<OutgoingBlockingHttpRequest>> req) = 0;
};

}
