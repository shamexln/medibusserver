#pragma once

#include <S31/Sdc/Public/Common/IDispatcher.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <vector>

namespace S31
{
namespace AsioDispatch
{
class DefaultDispatcher;
class DefaultAsioDispatcher;
}

namespace Sdc
{

using NumberOfThreads = DFL::StrongTypedef<unsigned int, struct NumberOfThreadsTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable, DFL::Skill::LessThanComparable>;

/**
 * @brief Implementation of a dispatcher using a thread pool.
 *
 * @details This is intended to be used on:
 * - Windows platform: for test and production
 * - VxWorks platform: for test (i.e. integration tests)
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP ThreadPoolDispatcher: public IDispatcher
{
    public:
        ThreadPoolDispatcher();
        explicit ThreadPoolDispatcher(NumberOfThreads numberOfThreads);
        ~ThreadPoolDispatcher() override;

        /**
         * @brief This is called from S31 to inject the job queue.
         * @details Customers of S31 should not use it.
         */
        void injectJobQueue(const DFL::NotNull<std::shared_ptr<IJobQueue>>& jobQueue) override;

        /**
         * @brief This is called from S31 to access the asio executor provider.
         * @details Customers of S31 should not use it.
         */
        DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>> dispatcher() override;

        void start() override;
        void stop() override;

    private:
        NumberOfThreads m_numberOfThreads;
        std::shared_ptr<IJobQueue> m_queue;

        class Impl;
        std::unique_ptr<Impl> m_impl;

        DFL::NotNull<std::shared_ptr<AsioDispatch::DefaultAsioDispatcher>> m_defaultExecutorProvider;
        DFL::NotNull<std::shared_ptr<AsioDispatch::DefaultDispatcher>> m_dispatcher;

        void internalStop();
};

}
}
