#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Sequence of \ref LocalizedText.
 * @ingroup Mdib
 */
using LocalizedTexts = std::vector<LocalizedText>;

/**
 * @brief Get the default text.
 *
 * The default text is the element found by the following priority order
 * -a localized text without language code
 * -a localized text with default language code 'en-US'
 * -the first localized text with a language code starting with 'en'
 * -the first non-empty localized text
 *
 * @param texts The localized texts
 * @return the detected default text or an empty localized text with no language code.
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP LocalizedText getDefaultText(const LocalizedTexts &texts);

} /* namespace Mdib */
} /* namespace DFL */
