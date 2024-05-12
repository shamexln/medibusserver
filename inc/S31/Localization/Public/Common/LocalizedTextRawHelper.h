#pragma once

#include <Framework/Mdib/Public/Model/LocalizedTextRaw.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>
#include <Framework/Utils/Public/NotNull.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

namespace S31::Localization
{

/**
 * @brief Provides localized texts from the raw localized text data.
 * @details To be used for e.g. raw data generated from Xliff.
 * @ingroup S31LocalizationCommon
 */
template <std::size_t Size>
DFL::Mdib::LocalizedTexts makeTexts(const DFL::Mdib::LocalizedTextRaw(&texts)[Size])
{
    const auto begin = std::begin(texts);
    const auto end = std::end(texts);

    auto optionalWidth = [](const DFL::Mdib::LocalizedTextRaw& text)
        -> boost::optional<DFL::Mdib::LocalizedTextWidth>
    {
        if (text.hasWidth)
        {
            return text.width;
        }
        return boost::none;
    };

    DFL::Mdib::LocalizedTexts result;
    result.reserve(Size);

    std::for_each(begin, end,
        [&](const DFL::Mdib::LocalizedTextRaw& text)
        {
            result.emplace_back(
                        DFL::Mdib::LocalizedText(
                            DFL::Locale::Utf8(text.text),
                            DFL::Locale::LanguageTag(text.language),
                            DFL::Mdib::LocalizedTextRef(DFL::Locale::Utf8(text.ref)),
                            DFL::Mdib::VersionCounter(static_cast<std::uint64_t>(text.version)),
                            optionalWidth(text)));
        });

    return result;
}

}
