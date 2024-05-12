#pragma once

#include <S31/History/Private/S31HistoryExImp.h>

#include <Framework/Utils/Public/LanguageTag.h>

#include <vector>

namespace S31::History
{

/**
 * @brief Language filter for history query
 * @ingroup S31CoreHistory
 */
class S31_HISTORY_EXPIMP LanguageFilter
{
public:
    static LanguageFilter createWithoutLanguages();
    static LanguageFilter createWithAllLanguages();
    static LanguageFilter createWithLanguages(std::vector<DFL::Locale::LanguageTag> languages);

    bool noLanguages() const noexcept;
    bool allLanguages() const noexcept;
    const std::vector<DFL::Locale::LanguageTag>& languages() const noexcept;

private:
    LanguageFilter(bool forceAllLanguages, std::vector<DFL::Locale::LanguageTag>);
    bool m_forceAllLanguages{false};
    std::vector<DFL::Locale::LanguageTag> m_languages;
};
}
