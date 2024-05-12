#pragma once

#include <S31/Utils/S31Only/Timer.h>
#include <S31/Utils/S31Only/TimerFactory.h>
#include <S31/Log/Public/Logger.h>

#include <Framework/Chrono/Public/Duration.h>

#include <boost/asio/deadline_timer.hpp>
#include <boost/thread/thread.hpp>

#include <chrono>
#include <mutex>

namespace S31::Utils::Test
{

/**
 * @brief A timer utility which runs a deadline timer in it's own thread. Calls a given function once the timer has expired.
 * @ingroup S31Utils
 */
class BoostTimer: public Timer
{
    public:

        /**
         * @brief Constructor
         * @param timeoutFunc The function which will be triggered once the timer has timed out.
         */
        explicit BoostTimer(std::function<void()> timeoutFunc);
        ~BoostTimer() override;

        /**
         * @brief (Re-)start the timer
         */
        void start(std::chrono::milliseconds timeout) override;

    private:
        void handler(const boost::system::error_code& error);
        void run();
        void internalStopNoLock();

        std::function<void()> m_timeoutFunc;
        bool m_running{false};
        std::mutex m_mutex;

        boost::thread m_waitThread;
        boost::asio::io_context m_ioContext;
        boost::asio::deadline_timer m_timer;
};

class BoostTimerFactory: public TimerFactory
{
public:
    [[nodiscard]] DFL::NotNull<std::unique_ptr<Timer>>
    inline createTimer(std::function<void()> timeoutFunc) override
    {
        return DFL::asNotNull(std::make_unique<BoostTimer>(timeoutFunc));
    }
};

inline BoostTimer::BoostTimer(std::function<void()> timeoutFunc) :
    m_timeoutFunc(std::move(timeoutFunc)),
    m_timer(m_ioContext)
{
}

inline void BoostTimer::handler(const boost::system::error_code& error)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (!m_running)
    {
        return;
    }

    if (!error)
    {
        m_timeoutFunc();
    }
    else if (error != boost::asio::error::operation_aborted)
    {
        S31_STREAM_ERROR_LOGGER("Test", "Utility timer ran into an unknown error, error message: ", error.message());
    }

    m_running = false;
}

inline BoostTimer::~BoostTimer()
{
    internalStopNoLock();
}

inline void BoostTimer::run()
{
    m_ioContext.run();
}

inline void BoostTimer::start(std::chrono::milliseconds timeout)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_running)
    {
        lock.unlock();
        internalStopNoLock();
    }

    if (!m_waitThread.joinable())
    {
        m_running = true;
        m_timer.expires_from_now(boost::posix_time::milliseconds(timeout.count()));
        m_timer.async_wait([this](const auto& ec) { handler(ec); });
        m_waitThread = boost::thread(&BoostTimer::run, this);
    }
}

inline void BoostTimer::internalStopNoLock()
{
    try
    {
        m_running = false;

        m_timer.cancel();
        m_waitThread.interrupt();
        if (m_waitThread.joinable())
        {
            m_waitThread.join();
        }

        m_ioContext.reset();
    }
    catch(const std::exception& e)
    {
        S31_STREAM_ERROR_LOGGER("Test", "Error thrown stopping Timer: ", e.what());
    }
}

}
