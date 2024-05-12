#pragma once

#include <S31/AsioDispatch/Test/DummyExecutorProvider.h>
#include <S31/Sdc/Public/Common/IDispatcher.h>

namespace S31::Sdc::Test
{
class DispatcherSpy : public S31::Sdc::IDispatcher
{
public:
    void injectJobQueue(const DFL::NotNull<std::shared_ptr<S31::Sdc::IJobQueue>>& jobQueue) override
    {
        if (!m_startCalled)
        {
            m_injectCalledBeforeStart = true;
        }
        m_jobQueue = jobQueue.get();
    }
    
    DFL::NotNull<std::shared_ptr<S31::AsioDispatch::Dispatcher>> dispatcher() override
    {
        ++m_asioDispatcherCalls;
        return m_dispatcher;
    }

    void start() override
    {
        m_startCalled = true;
    }
    void stop() override
    {
        m_stopCalled = true;
    }
    [[nodiscard]] bool injectCalledBeforeStart() const
    {
        return m_injectCalledBeforeStart;
    }
    [[nodiscard]] bool startCalled() const
    {
        return m_startCalled;
    }
    [[nodiscard]] bool stopCalled() const
    {
        return m_stopCalled;
    }
    [[nodiscard]] std::shared_ptr<S31::Sdc::IJobQueue> jobQueue() const
    {
        return m_jobQueue;
    }
    [[nodiscard]] unsigned asioDispatcherCalls() const
    {
        return m_asioDispatcherCalls;
    }

    void injectDispatcher(DFL::NotNull<std::shared_ptr<S31::AsioDispatch::Dispatcher>> dispatcher)
    {
        m_dispatcher = std::move(dispatcher);
    }

private:
    bool m_injectCalledBeforeStart{false};
    bool m_startCalled{false};
    bool m_stopCalled{false};

    std::shared_ptr<S31::Sdc::IJobQueue> m_jobQueue{};
    
    DFL::NotNull<std::shared_ptr<S31::AsioDispatch::Dispatcher>> m_dispatcher{AsioDispatch::Test::makeDispatcherWithDummyExecutorProvider()};

    unsigned m_asioDispatcherCalls{0};
};
}
