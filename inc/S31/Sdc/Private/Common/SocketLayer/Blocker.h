#pragma once

#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Chrono/Public/Duration.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Can be used to mark a certain operation as blocked for a certain time.
 * @ingroup S31SdcCommonSocket
 */
class Blocker
{
    public:
        void blockFor(DFL::Chrono::Milliseconds blockDuration);
        bool isBlocked() const;
    private:
        mutable bool m_isBlocked{false};
        DFL::Chrono::SteadyClock::TimePoint m_blockedUntil{};
};

inline void Blocker::blockFor(DFL::Chrono::Milliseconds blockDuration)
{
    m_blockedUntil = DFL::Chrono::SteadyClock::now() + blockDuration;
    m_isBlocked = true;
}

inline bool Blocker::isBlocked() const
{
    if (!m_isBlocked)
    {
        return false;
    }

    if (DFL::Chrono::SteadyClock::now() > m_blockedUntil)
    {
        m_isBlocked = false;
        return false;
    }

    return true;
}

}
