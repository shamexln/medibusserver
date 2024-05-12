#pragma once

#include <S31/Error/S31Only/EventCodeObserver.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>

#include <condition_variable>
#include <mutex>

namespace S31::Error::Test
{

class EventCodeObserverSpy: public EventCodeObserver
{
    public:
        void eventAdded(EventCode id) override
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_added.push_back(id);
            m_addedConditionDataReceived = true;
            m_addedCondition.notify_all();
        }

        void eventRemoved(EventCode id) override
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_removed.push_back(id);
        }

        std::vector<EventCode> getAddedEvents()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_added;
        }

        std::vector<EventCode> getRemovedEvents()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_removed;
        }

        void waitForAddedErrorStates(std::size_t requiredAddedStates)
        {
            std::size_t receivedAddedStates;
            bool timeout = false;
            auto tStart = DFL::Chrono::SteadyClock::now();
            auto wait = std::chrono::milliseconds(5000);

            std::unique_lock<std::mutex> lock(m_mutex);
            do
            {
                if (m_addedConditionDataReceived)
                {
                    m_addedConditionDataReceived = false;
                    receivedAddedStates = m_added.size();
                    continue;
                }

                m_addedCondition.wait_for(lock, wait);
                if (!m_addedConditionDataReceived)
                {
                    break;
                }

                m_addedConditionDataReceived = false;
                receivedAddedStates = m_added.size();
                auto tDelta = DFL::Chrono::SteadyClock::now() - tStart;
                wait -= std::chrono::milliseconds(DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(tDelta).count());
                timeout = wait.count() <= 0;
            } while (receivedAddedStates < requiredAddedStates || !timeout);
        }

        void resetSpy()
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_added.clear();
            m_removed.clear();
            m_addedConditionDataReceived = false;
        }
    private:
        std::mutex m_mutex;
        std::condition_variable m_addedCondition;
        bool m_addedConditionDataReceived = false;
        std::vector<EventCode> m_added;
        std::vector<EventCode> m_removed;
};

}
