#pragma once

#include <Framework/Format/Private/ExpImp.h>
#include <Framework/Format/Private/Format.h>

#include <string>

namespace DFL
{
namespace Format
{
/**
 * @brief Stream for fast formatting of arbitrary data.
 *
 * Under the hood the open-source library cppformat is used.
 * Since a stack-allocated-buffer is used to perform the formatting
 * it is best to create a stream object once and call clear on
 * subsequent usages of it to consume less stack memory.
 *
 * @ingroup Format
 */
class DFL_FORMAT_EXPIMP Stream
{
public:
    /**
     * @brief Formats value and puts it into stream.
     * @{
     */
    Stream& operator<<(int value);
    Stream& operator<<(unsigned int value);
    Stream& operator<<(long value);
    Stream& operator<<(unsigned long value);
    Stream& operator<<(long long value);
    Stream& operator<<(unsigned long long value);
    Stream& operator<<(float value);
    Stream& operator<<(double value);
    Stream& operator<<(long double value);
    Stream& operator<<(char value);
    Stream& operator<<(const char* value);
    Stream& operator<<(const std::string& value);
    Stream& operator<<(fmt::BasicStringRef<char> value);
    /** @} */
    /**
     * @brief Uses given format specifier to format the value and puts it into
     * stream.
     *
     * @{
     */
    Stream& operator<<(
        fmt::IntFormatSpec<int, fmt::TypeSpec<'x'>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned int, fmt::TypeSpec<'x'>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<long, fmt::TypeSpec<'x'>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned long, fmt::TypeSpec<'x'>, char> const&
            spec);
    Stream& operator<<(
        fmt::IntFormatSpec<long long, fmt::TypeSpec<'x'>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned long long, fmt::TypeSpec<'x'>, char> const&
            spec);
    Stream& operator<<(
        fmt::IntFormatSpec<int, fmt::AlignTypeSpec<0>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned int, fmt::AlignTypeSpec<0>, char> const&
            spec);
    Stream& operator<<(
        fmt::IntFormatSpec<long, fmt::AlignTypeSpec<0>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned long, fmt::AlignTypeSpec<0>, char> const&
            spec);
    Stream& operator<<(
        fmt::IntFormatSpec<long long, fmt::AlignTypeSpec<0>, char> const& spec);
    Stream& operator<<(fmt::IntFormatSpec<unsigned long long,
                                          fmt::AlignTypeSpec<0>,
                                          char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<int, fmt::AlignTypeSpec<'x'>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned int, fmt::AlignTypeSpec<'x'>, char> const&
            spec);
    Stream& operator<<(
        fmt::IntFormatSpec<long, fmt::AlignTypeSpec<'x'>, char> const& spec);
    Stream& operator<<(
        fmt::IntFormatSpec<unsigned long, fmt::AlignTypeSpec<'x'>, char> const&
            spec);
    Stream& operator<<(
        fmt::IntFormatSpec<long long, fmt::AlignTypeSpec<'x'>, char> const&
            spec);
    Stream& operator<<(fmt::IntFormatSpec<unsigned long long,
                                          fmt::AlignTypeSpec<'x'>,
                                          char> const& spec);
    /** @} */
    /**
     * @brief Converts stream to a null terminated string.
     */
    char const* cStr() const;
    /**
     * @brief Clears content so it can be reused.
     */
    void clear() noexcept;

private:
    fmt::MemoryWriter m_writer;
};
}
}
