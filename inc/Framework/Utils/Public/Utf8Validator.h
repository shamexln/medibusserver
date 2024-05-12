#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <string>

namespace DFL
{
namespace Locale
{

/**
 * @brief Validates strings for UTF-8 correctness.
 * @ingroup Utils
 */
class DFL_UTILS_EXPIMP Utf8Validator
{
    public:

        /**
         * Validates a buffer for UTF-8 correctness
         *
         * @param buffer The buffer containing the UTF-8 data
         * @returns if buffer contains a valid UTF-8 string
         */
        static bool isValid(const std::string& buffer);

        /**
         * Validates a buffer for UTF-8 correctness
         *
         * @param buffer The buffer containing the UTF-8 data
         * @returns if buffer contains a valid UTF-8 string
         */
        static bool isValid(const char buffer[]);

};

}
}
