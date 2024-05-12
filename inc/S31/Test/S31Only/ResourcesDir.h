#pragma once

#include <S31/Test/Private/S31TestUtilsExImp.h>
#include <string>

namespace S31::Test
{

/**
 * @brief Looks for the path containing the given file.
 * @details Throws is the path could not be found.
 * @return The path or empty
 */
S31_TESTUTILS_EXPIMP std::string resolveTestResourcePath(const std::string& neededFileForTest);

}
