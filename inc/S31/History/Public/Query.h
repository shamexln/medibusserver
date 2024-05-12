#pragma once

#include <S31/History/Private/S31HistoryExImp.h>
#include <S31/History/Public/LanguageFilter.h>
#include <S31/History/Public/TimeRange.h>
#include <S31/History/Public/VersionRange.h>

#include <variant>

namespace S31::History
{

/**
 * @brief Specify if initial MDIB shall be provided.
 * @ingroup S31CoreHistory
 */
enum class InitialMdib
{
    /**
     * @brief Do not add the initial MDIB.
     */
    Skip,

    /**
     * @brief Initial MDIB shall be provided in response data.
     */
    Required
};

/**
 * @brief History query payload to specify requested history MDIB data.
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP Query
{
public:
    Query(InitialMdib, TimeRange);
    Query(InitialMdib, VersionRange);
    Query(InitialMdib, TimeRange, LanguageFilter);
    Query(InitialMdib, VersionRange, LanguageFilter);

    bool isVersionRangeQuery() const noexcept;
    const VersionRange& versionRange() const;

    bool isTimeRangeQuery() const noexcept;
    const TimeRange& timeRange() const;

    InitialMdib initialMdib() const noexcept;

private:
    InitialMdib m_mdib{InitialMdib::Skip};
    LanguageFilter m_languages{LanguageFilter::createWithoutLanguages()};
    std::variant<TimeRange,VersionRange> m_type;
};
}
