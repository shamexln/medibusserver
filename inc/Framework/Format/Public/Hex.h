#pragma once

#include <Framework/Format/Private/ExpImp.h>
#include <Framework/Format/Private/Format.h>

namespace DFL
{
namespace Format
{
/**
 * @brief Given value will converted to its hex representation.
 *
 * The representation is identical if streamed via std::hex.
 *
 * @snippet Format/Test/UnitTest/TestStream.cpp Hex
 *
 * @ingroup Format
 * @{
 */
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<int, fmt::TypeSpec<'x'>, char> hex(int value);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned int, fmt::TypeSpec<'x'>, char> hex(
    unsigned int value);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<long, fmt::TypeSpec<'x'>, char> hex(long value);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned long, fmt::TypeSpec<'x'>, char> hex(
    unsigned long value);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<long long, fmt::TypeSpec<'x'>, char> hex(long long value);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned long long, fmt::TypeSpec<'x'>, char> hex(
    unsigned long long value);
/** @} */
}
}
