#pragma once

#include <S31/History/Public/Query.h>
#include <S31/History/Public/Result.h>

#include <optional>

namespace S31::Sdc::Impl
{
/**
 * @brief Stores the subscription information for a history service request.
 * @ingroup S31SdcDevice
 */
class HistorySubscription
{
public:
    explicit HistorySubscription(History::Query query);

    const History::Query& query() const noexcept;

    const std::optional<History::Result>& result() const noexcept;

    void result(History::Result result);

    const History::Result::iterator_type& iterator() const noexcept;

    void iterator(History::Result::iterator_type iterator);

private:
    const History::Query           m_query;
    std::optional<History::Result> m_result;
    History::Result::iterator_type m_iterator;
};
}  // namespace S31::Sdc::Impl
