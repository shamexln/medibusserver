#pragma once

#include <gtest/gtest.h>

#include <algorithm>

namespace DFLTest
{
namespace Encoding
{
template <class Actual, class Expected>
void isContiguousContainer(const Actual& actual, const Expected& expected)
{
    ASSERT_EQ(expected.size(), actual.size());
    EXPECT_EQ(expected.empty(), actual.empty());

    for (size_t i = 0; i < actual.size(); ++i)
    {
        SCOPED_TRACE(i);
        SCOPED_TRACE("at index: ");
        EXPECT_EQ(expected[i], actual[i]);
    }
    EXPECT_EQ(expected.front(), actual.front());
    EXPECT_EQ(expected.back(), actual.back());

    EXPECT_TRUE(
        std::equal(actual.begin(), actual.end(), std::cbegin(expected)));
    EXPECT_TRUE(
        std::equal(actual.cbegin(), actual.cend(), std::cbegin(expected)));
    EXPECT_TRUE(
        std::equal(actual.rbegin(), actual.rend(), std::crbegin(expected)));
    EXPECT_TRUE(
        std::equal(actual.crbegin(), actual.crend(), std::crbegin(expected)));
}
}
}
