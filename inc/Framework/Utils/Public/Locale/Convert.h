#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <string>

namespace DFL
{
namespace Locale
{
namespace Convert
{
namespace WideString
{
/**
 * @brief Converts null terminated wide string to narrow string.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::string toNarrowString(const wchar_t* wide);

/**
 * @brief Converts wide character sequence [first, last) to narrow string.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::string toNarrowString(const wchar_t* first, const wchar_t* last);

/**
 * @brief Converts wide string to narrow string.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::string toNarrowString(const std::wstring& wide);
}
namespace NarrowString
{
/**
 * @brief Converts null terminated narrow string to wide string.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::wstring toWideString(const char* narrow);

/**
 * @brief Converts narrow character sequence [first, last) to wide string.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::wstring toWideString(const char* first, const char* last);

/**
 * @brief Converts narrow string to wide string.
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::wstring toWideString(const std::string& narrow);
}
}
}
}
