#pragma once

#include <S31/Test/Private/S31TestUtilsExImp.h>

#include <initializer_list>
#include <string>

namespace S31::Test
{

/**
 * @brief Combine a list of test names into a gtest filter compatible string.
 *
 * @details
 * E.g.: {"test1", "test2.basic"} --> "test1.*:test2.basic"
 *
 */
S31_TESTUTILS_EXPIMP void
addTestCasesToFilterString(std::string& testCaseFilterString, std::initializer_list<const char*> tests);

}  // namespace S31::Test
