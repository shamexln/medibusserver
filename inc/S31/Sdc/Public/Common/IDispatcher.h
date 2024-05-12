#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
namespace AsioDispatch
{
class Dispatcher;
}

namespace Sdc
{
class IJobQueue;

/**
 * @brief Subclasses of this interface are responsible to work on the @ref S31::Sdc::IJobQueue.
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP IDispatcher
{
    public:

        virtual ~IDispatcher() noexcept = default;

        /**
         * The job queue will be injected before starting the dispatcher.
         */
        virtual void injectJobQueue(const DFL::NotNull<std::shared_ptr<IJobQueue>>& jobQueue) = 0;

        /**
         * Access the Asio dispatcher.
         */
        virtual DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>> dispatcher() = 0;

        /**
         * start working on the job queue
         *
         */
        virtual void start() = 0;

        /**
         * request stop of jobs
         * jobs might continue running
         */
        virtual void stop() = 0;
};

}
}
