#pragma once

#include <S31/History/Private/S31HistoryExImp.h>

#include <Framework/Mdib/Public/Model/Timestamp.h>

namespace S31::History
{
/**
 * @brief Request filter for historic MDIB data based on a time range.
 * @details
 * Such a request might contain different MDIB sequences.
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP TimeRange
{
public:
    TimeRange(DFL::Mdib::Timestamp start, DFL::Mdib::Timestamp end);

    DFL::Mdib::Timestamp start() const noexcept;
    DFL::Mdib::Timestamp end() const noexcept;

private:
    DFL::Mdib::Timestamp m_startTime;
    DFL::Mdib::Timestamp m_endTime;
};

// ------ implementation ------

inline DFL::Mdib::Timestamp TimeRange::start() const noexcept
{
    return m_startTime;
}

inline DFL::Mdib::Timestamp TimeRange::end() const noexcept
{
    return m_endTime;
}

}
