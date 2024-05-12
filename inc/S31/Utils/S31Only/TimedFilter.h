#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SteadyClock.h>

#include <map>
#include <mutex>

namespace S31::Utils
{
/**
 * @brief Support filtering for a time duration.
 * @details This class provides an indicator whether some message or key
 * was previously observed within a given time duration.
 * @ingroup S31Utils
 */
class S31_UTILS_EXPIMP TimedFilter
{
    public:
        /**
         * @brief Construct with the filter duration.
         */
        explicit TimedFilter(DFL::Chrono::Milliseconds duration);

        /**
         * @brief Check if the key was recently observed.
         * @details Returns true if the given key was previously observed
         * within the filter time duration. The filter entry for the key is
         * updated to "now" to prepare for a future check.
         */
        bool wasRecentlyObserved(const std::string& key);

    private:
        using TimePoint = DFL::Chrono::SteadyClock::TimePoint;
        void eraseOldEntries(TimePoint now);

        std::mutex                       m_mutex;
        std::map<std::string, TimePoint> m_filter;
        DFL::Chrono::Milliseconds        m_duration;
};

}
