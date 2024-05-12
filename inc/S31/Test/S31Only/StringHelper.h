#pragma once

#include <S31/Test/Private/S31TestUtilsExImp.h>

#include <string>
#include <string_view>

namespace S31::Test
{

/**
 * @brief Normalize a string containing XML
 */
S31_TESTUTILS_EXPIMP std::string normalizeXml(std::string text);

/**
 * @brief Returns the given string stripped from line breaks.
 */
S31_TESTUTILS_EXPIMP std::string removeCrLf(const std::string& text);

/**
 * @brief Returns a message that shows how two texts are different.
 * @details Useful when comparing longer text to be equal in tests.
 *
 * Exemplary usage: `EXPECT_EQ(expected, actual) << explainDifference(expected, actual)`
 *
 * Generally it shows the place where first difference is (with context) and handles some
 * special cases: when there are differences only in spaces or line breaks.
 */
S31_TESTUTILS_EXPIMP std::string explainDifference(const std::string& expectedMessage, const std::string& actualMessage);

/**
 * @brief Replaces first occurrence of pattern start..end, including start and end with the new pattern
 */
S31_TESTUTILS_EXPIMP void replaceByPattern(std::string& s, const std::string& startPattern, const std::string& endPattern, const std::string& newSubstr);

/**
 * @brief Returns the text between the first occurrence of pattern start..end (excluding start and end)
 */
S31_TESTUTILS_EXPIMP std::string_view getTextBetweenPatterns(std::string_view s, std::string_view startPattern, std::string_view endPattern);

struct StringReplacementResult
{
    unsigned int numberOfReplacements = 0;
};

/**
 * @brief Replace all occurrences of a substring with a new one.
 * @details From https://stackoverflow.com/questions/3418231/replace-part-of-a-string-with-another-string
 * @returns Result type that contains the number of done replacements
 */
S31_TESTUTILS_EXPIMP StringReplacementResult replaceAllOccurences(std::string& s, const std::string_view& pattern, const std::string_view& replacementForPattern);

/**
 * @brief Count the appearance of a string within another string.
 */
S31_TESTUTILS_EXPIMP std::size_t countSubstring(std::string_view haystack, std::string_view needle);

}
