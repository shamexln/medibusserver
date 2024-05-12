#pragma once

#include <S31/S31CoreExImp.h>

#include <string>

namespace S31
{
/**
 * \brief Provide functions to check file hashes.
 *
 * \ingroup S31ErrorGroup
 */
class S31_CORE_EXPIMP FileHashChecker
{
    public:
        /**
         * @brief Create SHA-1 hash of given file and compare it against fileName + ".sha1".
         *
         * @details
         * fileName + ".sha1" shall contain a hex encoded SHA-1 value.
         *
         * @param fileName Any binary file.
         * @return False if SHA-1 does not match or fileName/fileName + ".sha1" cannot be read, otherwise true.
         */
        static bool matchSha1(const std::string& fileName);

        /**
         * @brief Reads the file if matches the sha1 checksum file.
         * @param fileName Any binary file.
         * @return Content of file (if SHA-1 matches) or empty string.
         */
        static std::string readFileIfMatchesSha1File(const std::string& fileName);
};

} /* namespace S31 */
