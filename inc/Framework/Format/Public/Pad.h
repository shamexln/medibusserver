#pragma once

#include <Framework/Format/Private/ExpImp.h>
#include <Framework/Format/Private/Format.h>

namespace DFL
{
namespace Format
{
/**
 * @brief Pads the value with the fill character to the specified width.
 *
 * Same as combining std::ostream::fill with std::setw.
 *
 * @snippet Format/Test/UnitTest/TestStream.cpp Pad
 *
 * @ingroup Format
 * @{
 */
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<int, fmt::AlignTypeSpec<0>, char> pad(int value,
                                                         unsigned int width,
                                                         char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned int, fmt::AlignTypeSpec<0>, char> pad(
    unsigned int value,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<long, fmt::AlignTypeSpec<0>, char> pad(long value,
                                                          unsigned int width,
                                                          char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned long, fmt::AlignTypeSpec<0>, char> pad(
    unsigned long value,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<long long, fmt::AlignTypeSpec<0>, char> pad(
    long long value,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned long long, fmt::AlignTypeSpec<0>, char> pad(
    unsigned long long value,
    unsigned int width,
    char fill);

DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<int, fmt::AlignTypeSpec<'x'>, char> pad(
    fmt::IntFormatSpec<int, fmt::TypeSpec<'x'>> const& f,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned int, fmt::AlignTypeSpec<'x'>, char> pad(
    fmt::IntFormatSpec<unsigned int, fmt::TypeSpec<'x'>> const& f,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<long, fmt::AlignTypeSpec<'x'>, char> pad(
    fmt::IntFormatSpec<long, fmt::TypeSpec<'x'>> const& f,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned long, fmt::AlignTypeSpec<'x'>, char> pad(
    fmt::IntFormatSpec<unsigned long, fmt::TypeSpec<'x'>> const& f,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<long long, fmt::AlignTypeSpec<'x'>, char> pad(
    fmt::IntFormatSpec<long long, fmt::TypeSpec<'x'>> const& f,
    unsigned int width,
    char fill);
DFL_FORMAT_EXPIMP
fmt::IntFormatSpec<unsigned long long, fmt::AlignTypeSpec<'x'>, char> pad(
    fmt::IntFormatSpec<unsigned long long, fmt::TypeSpec<'x'>> const& f,
    unsigned int width,
    char fill);
/** @} */
}
}
