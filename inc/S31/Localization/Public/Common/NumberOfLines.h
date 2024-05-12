#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::Localization
{

/**
 * @brief Strong type for Number of Lines as used in BICEPS GetLocalizedText.
 * @ingroup S31LocalizationCommon
 */
using NumberOfLines = DFL::StrongTypedef<unsigned int, struct IntTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

}
