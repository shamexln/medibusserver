#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Utils/Public/Outcome.h>

#include <memory>

namespace S31::Utils::Test
{

/**
 * @brief Mock to ignore outcome.
 * @ingroup S31Utils
 */
template<typename T_ResultData>
class OutcomeMock:
        public std::enable_shared_from_this<OutcomeMock<T_ResultData>>,
        public OutcomeConsumer<OutcomeMock<T_ResultData>, T_ResultData>
{
    public:
        using HandlerPtr = OutcomeTypes::HandlerPtr<T_ResultData>;
        using OutcomeType = Outcome<T_ResultData>;
        HandlerPtr makeIgnoreOutcomeHandler()
        {
            return OutcomeConsumer<OutcomeMock<T_ResultData>, T_ResultData>::makeOutcomeHandler(
                [&](OutcomeType& outcome)
                {
                    if (outcome.hasError())
                    {
                        S31_STREAM_INFO_LOGGER("Test", "Outcome error: ", outcome.errorMessage());
                        m_lastErrorMessage = outcome.errorMessage();
                        return;
                    }
                    m_lastErrorMessage.clear();
                    S31_STREAM_INFO_LOGGER("Test", "Outcome success");
                });
        }
        DFL::Locale::Utf8 m_lastErrorMessage;
};

}
