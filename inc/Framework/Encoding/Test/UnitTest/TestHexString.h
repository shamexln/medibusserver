#pragma once

#include <Framework/Format/Public/Stream.h>

#include <gtest/gtest.h>

#include <array>
#include <sstream>
#include <string>

namespace DFLTest
{
namespace Encoding
{
namespace HexString
{
template <class FromCstr>
inline void testCtor(FromCstr fromCstr)
{
    static const char* goodCstr[] = {"",
                                     "0",
                                     "00",
                                     "a",
                                     "A",
                                     "aA",
                                     "Aa",
                                     "AA",
                                     "0123465789abcdef",
                                     "0123465789ABCDEF"};
    static const char* badCstr[] = {"g", "G", "gG", "Gg", "GG", "-", "+"};

    for (const auto& cstr : goodCstr)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto)
        EXPECT_NO_THROW(fromCstr(cstr))
            << "construction from \"" << cstr << "\" shall not fail";
    }

    for (const auto& cstr : badCstr)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-goto)
        EXPECT_THROW(fromCstr(cstr), std::runtime_error)
            << "construction from \"" << cstr << "\" shall fail";
    }
}

template <class T>
void testEqualityComparable()
{
    //! [equalityComparable]
    EXPECT_EQ(T{}, T{});
    // NOLINTNEXTLINE(readability-container-size-empty)
    EXPECT_FALSE(T{} != T{});

    EXPECT_EQ(T{}, T{""});
    // NOLINTNEXTLINE(readability-container-size-empty)
    EXPECT_FALSE(T{} != T{""});

    EXPECT_NE(T{}, T{"00"});
    // NOLINTNEXTLINE(readability-container-size-empty)
    EXPECT_FALSE(T{} == T{"00"});

    EXPECT_EQ(T{"aa"}, T{"aA"});
    EXPECT_FALSE(T{"aa"} != T{"aA"});
    //! [equalityComparable]
}

template <class T>
void testStreaming()
{
    //! [streaming]
    {
        const std::string expected{};
        const T hexStr{};
        {
            std::ostringstream str{};
            str << hexStr;

            EXPECT_EQ(expected, str.str());
        }
        {
            ::DFL::Format::Stream str{};
            str << hexStr;

            EXPECT_EQ(expected, std::string{str.cStr()});
        }
    }
    {
        const std::string expected{"aB"};
        const T hexStr{expected};
        {
            std::ostringstream str{};
            str << hexStr;

            EXPECT_EQ(expected, str.str());
        }
        {
            ::DFL::Format::Stream str{};
            str << hexStr;

            EXPECT_EQ(expected, std::string{str.cStr()});
        }
    }
    //! [streaming]
}
}
}
}
