#pragma once

#include <S31/History/Private/S31HistoryExImp.h>

#include <memory>
#include <string>

namespace S31::History
{

/**
 * @brief Represent a history service ChangeSequenceReport.
 * @details
 * Instances of this report are self-contained and can be used as is.
 * They could be send as SOAP payload for example to SDC clients.
 * @ingroup S31CoreHistory
 */
class ChangeSequenceReport
{
public:
    /**
     * @brief The (maybe compressed) XML ChangeSequenceReport message.
     */
    std::string report;
};

class ResultItImpl;
class ResultImpl;

/**
 * @brief Iterator type for result.
 * @details
 * The "real" implementation is done in the ResultItImpl which is injected in the ctor.
 *
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP ResultIt
{
public:
    /**
     * @brief Default ctor is the end iterator.
     */
    ResultIt() = default;

    ResultIt(std::shared_ptr<const ResultImpl> resultImpl, std::shared_ptr<ResultItImpl> itImpl);

    /**
     * @brief Pre-increment operator to move to the next ChangeSequenceReport.
     */
    ResultIt& operator++();

    [[nodiscard]] const ChangeSequenceReport& operator*() const;

    [[nodiscard]] const ChangeSequenceReport* operator->() const;

    [[nodiscard]] bool equals(const ResultIt& rhs) const noexcept;

private:
    std::shared_ptr<const ResultImpl> m_resultImpl;
    std::shared_ptr<ResultItImpl> m_itImpl;
    ChangeSequenceReport m_report;
};

/**
 * @ingroup S31CoreHistory
 */
S31_HISTORY_EXPIMP bool operator==(const ResultIt& lhs, const ResultIt& rhs) noexcept;

/**
 * @ingroup S31CoreHistory
 */
S31_HISTORY_EXPIMP bool operator!=(const ResultIt& lhs, const ResultIt& rhs) noexcept;

/**
 * @brief Result type for a history service query.
 * @details
 * The result is iterable for the individual ChangeSequenceReports as defined by the history service.
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP Result
{
public:
    explicit Result(std::shared_ptr<ResultImpl> impl);

    using iterator_type = ResultIt;
    [[nodiscard]] iterator_type begin() const;
    [[nodiscard]] iterator_type end() const;

private:
    std::shared_ptr<ResultImpl> m_impl;
};

// ----- implementation -----


}  // namespace S31::History
