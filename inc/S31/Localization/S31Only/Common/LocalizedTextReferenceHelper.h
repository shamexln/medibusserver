#pragma once

#include <S31/Localization/Public/Common/LocalizedTextReference.h>
#include <S31/Localization/Public/Common/S31LtsExImp.h>
#include <S31/Localization/S31Only/Common/LocalizedTextFilter.h>

#include <Framework/Utils/Public/LanguageTag.h>

#include <vector>

namespace S31::Localization
{


/**
 * @brief Pair of filter and references.
 * @details Used to express that the filter and the references describe the same Localized Texts.
 *
 * Note that not every filter can be transformed into references. (i.e. because of 'catch all' filters, and a filter can have multiple languages).
 *
 * Given references (plus a language) can be transformed into multiple filters. (@ref makeFilters()).
 *
 * @ingroup S31LocalizationCommon
 */
struct FilterAndReferences
{
        LocalizedTextFilter filter;
        LocalizedTextReferences references;
};

/**
 * @brief Alias to a vector of @ref FilterAndReferences.
 * @ingroup S31LocalizationCommon
 */
using FilterAndReferencesContainer = std::vector<FilterAndReferences>;

/**
 * @brief Make filters + references from the given references and language.
 * @details Filters are sliced from the references to be useable in requests to the devices.
 *
 * ### How the filters are build
 * Given an arbitrary references set. For each combination of version, text width, and number of lines the according
 * references form a filter (together with the given language). An empty text width or number of lines are
 * regarded as separate values. Note that the @ref S31::Localization::LocalizedTextReferences are guaranteed to
 * be disjunct (in respect of describing the referenced localized text(s)).
 *
 * Filter and references correspond for each element in the result.
 *
 * Note: This function does not limit the size of the created filters.
 *
 * @ingroup S31LocalizationCommon
 */
S31_LTS_EXPIMP FilterAndReferencesContainer makeFilters(const LocalizedTextReferences& references, const DFL::Locale::LanguageTag& language);

/**
 * @brief Slices the given @ref S31::Localization::LocalizedTextReferences into two @ref S31::Localization::LocalizedTextReferences.
 * @details The given reference have to be sliceable, i.e. have to contain at least 2 elements. Otherwise boost::none is returned.
 * The resulting sets have half the size of the given set.
 * @return two sets of references build from the given references, or boost::none.
 */
S31_LTS_EXPIMP boost::optional<std::pair<LocalizedTextReferences, LocalizedTextReferences>> sliceReferences(LocalizedTextReferences&& references);

}
