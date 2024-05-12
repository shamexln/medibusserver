#pragma once

#include <Framework/Log/Public/Message.h>
#include <Framework/Log/Public/MessageIo.h>

#include <gmock/gmock.h>

#include <regex>
#include <string>

namespace S31::Test
{

/**
 * @brief Matches the given standard regular expression with the match starting at the first character and ending at the last character.
 * @details gmock "MatchesRegex" has very limited (and even OS dependent) regex syntax support, this replacement uses
 * the standard regex library.
 */
MATCHER_P(MatchesStdRegex, pattern, std::string{"MatchesRegex using std::regex with pattern: "} + pattern)
{
    *result_listener << "";
    std::regex regex(pattern);
    return std::regex_match(arg, regex);
}

/**
 * @brief Searches the given standard regular expression in the string for a match.
 * @details gmock "ContainsRegex" has very limited (and even OS dependent) regex syntax support, this replacement uses
 * the standard regex library.
 */
MATCHER_P(ContainsStdRegex, pattern, std::string{"Contains std::regex pattern: "} + pattern)
{
    *result_listener << "";
    std::regex regex(pattern);
    return std::regex_search(arg, regex);
}

/**
 * @brief Checks that a DFL log message text has the given substring.
 * @details Can be combined with Google Test container matchers.
 * Example: Check that a certain substring is in a range of log messages
 *
 *    DFL::Log::Test::MockLogger logger{DFL::Log::Registry::debug()};
 *    ...
 *    EXPECT_THAT(logger, Contains(TextHasSubstr("shall be found at least in one message")));
 *
 * Example: Check that a certain substring is not in a range of log messages
 *
 *    DFL::Log::Test::MockLogger logger{DFL::Log::Registry::debug()};
 *    ...
 *    EXPECT_THAT(logger, Each(Not(TextHasSubstr("shall not be found in any message"))));
 *
 */
MATCHER_P(TextHasSubstr, subStr, std::string{"Log message text contains: '"} + subStr + "'")
{
    *result_listener << "";
    static_assert(std::is_same<decltype(arg), const DFL::Log::Message&>::value, "Matcher is for DFL::Log::Message!");
    return arg.text().str().find(subStr) != std::string::npos;
}

}
