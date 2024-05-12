#pragma once

#include <S31/Utils/Public/Outcome.h>

#include <boost/optional/optional.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief To be used as an outcome consumer proxy in case the real outcome consumer cannot be held as a \c shared_from_this.
 * @ingroup S31SdcCommon
 */
template<class T_Result>
class OutcomeConsumerProxy:
        public Utils::OutcomeConsumer<OutcomeConsumerProxy<T_Result>, T_Result>,
        public std::enable_shared_from_this<OutcomeConsumerProxy<T_Result>>
{
    public:
        using Utils::OutcomeConsumer<OutcomeConsumerProxy<T_Result>, T_Result>::makeOutcomeHandler;
        using HandlerPtr = S31::Utils::OutcomeTypes::HandlerPtr<T_Result>;
        using OutcomeType = S31::Utils::Outcome<T_Result>;

        /**
         * @brief Makes an outcome handler that internally waits for a result.
         * @details Use \ref waitForOutcome() to fetch the result.
         *
         */
        HandlerPtr makeOutcomeHandler()
        {
            return makeOutcomeHandler([&](OutcomeType& outcome)
            {
                std::unique_lock<std::mutex> lock(this->m_mutex);
                if (!this->m_data)
                {
                    this->m_data = std::move(outcome);
                    this->m_conditionVariable.notify_all();
                }
            });
        }

        /**
         * @brief Waits for an outcome.
         * @details If an outcome handler was created using \ref makeOutcomeHandler(), this functions returns
         *          the result as soon as it is present, or it quits after _waitTime_.
         */
        const boost::optional<OutcomeType>& waitForOutcome(std::chrono::seconds waitTime) const
        {
            static const boost::optional<OutcomeType> noneResult{boost::none};
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_data)
            {
                return m_data;
            }
            m_conditionVariable.wait_for(lock, waitTime, [&]() { return this->m_data != boost::none; });
            if (m_data)
            {
                return m_data;
            }
            return noneResult;
        }

    private:
        mutable std::mutex m_mutex;
        mutable std::condition_variable m_conditionVariable;
        boost::optional<OutcomeType> m_data;
};

}
