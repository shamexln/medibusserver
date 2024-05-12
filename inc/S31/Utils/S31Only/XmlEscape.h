#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Utils/Public/Utf8.h>

#include <string>
#include <string_view>

namespace S31::Utils::Xml
{
/**
 * @brief Escape characters used for XML syntax.
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP std::string escape(std::string_view input);

/**
 * @brief Escape characters used for XML syntax.
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP std::string escape(const DFL::Locale::Utf8& input);

}  // namespace S31::Utils::Xml
