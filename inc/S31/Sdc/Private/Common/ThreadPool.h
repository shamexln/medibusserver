#pragma once

#include <S31/Error/Public/GeneratedRemosErrorCodes.h>
#include <S31/Error/S31Only/EventCodeRegistry.h>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Public/Common/ThreadPoolDispatcher.h>
#ifdef VXWORKS
#include <S31/Sdc/Private/Common/ThreadPoolThread_VxWorks.h>
#else
#include <S31/Sdc/Private/Common/ThreadPoolThread_Default.h>
#endif
#include <S31/Base/S31Only/Exception.h>

#include <Framework/Config/Public/WindowsProxy.h>
#include <Framework/Crypto/Public/OpenSsl.h>

#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <vector>

namespace S31::Sdc::Impl
{

using Task = std::function<void()>;

/**
 * @brief Implements a thread pool.
 * @ingroup S31SdcCommon
 */
class ThreadPool
{
    public:
        explicit ThreadPool(NumberOfThreads numberOfThreads)
        {
            if (numberOfThreads.get() < 1 || numberOfThreads > MaxNumberOfThreads)
            {
                S31_THROW_EXCEPTION(InternalResourceMissing, "Invalid number of threads.");
            }

            startThreads(numberOfThreads);
        }

        ~ThreadPool()
        {
            try
            {
                clearTasks();
                join();
                return;
            }
            catch (const std::exception& e)
            {
                S31_SERVICE_STREAM_ERROR_LIMITED(Error::RemosCodes::REMOS_ERR_GENERAL_SOFTWARE_ERROR,
                        "Failed to join while shutting down: ", e.what());
            }
            try
            {
                S31::Error::EventCodeRegistry::instance()->addEvent(S31::Error::EventCode::GENERAL_SOFTWARE_ERROR);
            }
            catch (const std::exception& e)
            {
                S31_SERVICE_STREAM_ERROR(Error::RemosCodes::REMOS_ERR_GENERAL_SOFTWARE_ERROR,
                        "Failed to raise general software error event: ", e.what());
            }
        }

        /**
         * @brief The given task will be executed by some thread of the pool.
         * @param t The task.
         */
        void asyncExecute(Task t)
        {
            {
                std::lock_guard<std::mutex> const guard(m_mutex);
                m_tasks.push(std::move(t));
            }
            m_condVar.notify_one();
        }

    private:

        void threadFunction()
        {
            while (true)
            {
                Task task;

                {
                    std::unique_lock<std::mutex> lock(m_mutex);

                    if (!m_running)
                    {
                        break;
                    }

                    if (m_tasks.empty())
                    {
                        m_condVar.wait(lock);
                    }

                    if (m_tasks.empty())
                    {
                        continue;
                    }

                    task =  std::move(m_tasks.front());
                    m_tasks.pop();
                }

                try
                {
                    task();
                }
                catch(const std::exception& e)
                {
                    S31_SERVICE_STREAM_ERROR_LIMITED(Error::RemosCodes::REMOS_ERR_GENERAL_SOFTWARE_ERROR,
                            "Execution of task failed with exception. ", e.what());
                    Error::EventCodeRegistry::instance()->addEvent(Error::EventCode::GENERAL_SOFTWARE_ERROR);
                }
            }
            DFL::Crypto::OpenSsl::threadStop();
        }

        void startThreads(NumberOfThreads numberOfThreads)
        {
            {
                std::lock_guard<std::mutex> const guard(m_mutex);
                m_running = true;
            }
            for (unsigned int i = 0; i < numberOfThreads.get(); ++i)
            {
                PoolThread t([this](){ this->threadFunction(); });
                m_threads.push_back(std::move(t));
            }
        }

        void join()
        {
            {
                std::lock_guard<std::mutex> const guard(m_mutex);
                m_running = false;
            }
            m_condVar.notify_all();

            for (auto& t : m_threads)
            {
                if (t.joinable())
                {
                    t.join();
                }
            }
        }

        void clearTasks()
        {
            std::lock_guard<std::mutex> const guard(m_mutex);
            m_tasks = std::queue<Task>();
        }

        constexpr static const NumberOfThreads MaxNumberOfThreads{1024};

        std::vector<PoolThread> m_threads;
        std::queue<Task> m_tasks;
        std::mutex m_mutex;
        std::condition_variable m_condVar;
        bool m_running{false};

};

}
