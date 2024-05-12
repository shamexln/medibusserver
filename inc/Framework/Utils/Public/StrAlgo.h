#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <string>

namespace DFL
{
namespace StrAlgo
{
/**
 * @brief Returns a snake-case formatted version of given string.
 *
 * @snippet Utils/Test/UnitTest/TestStrAlgo.cpp SnakeCase
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::string toSnakeCase(const std::string& txt);
}
}
