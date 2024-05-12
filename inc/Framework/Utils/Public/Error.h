#pragma once

#include <Framework/Utils/Private/ExpImp.h>

#include <system_error>

namespace DFL
{
namespace Error
{
/**
 * @brief Returns the errno of the standard C runtime library.
 *
 * @details Since any function of the standard C library can modify the
 * value to some value different from zero, a program should reset it to zero
 * by calling \ref DFL::Error::resetLastLibC().
 *
 * @snippet Utils/Test/UnitTest/TestError.cpp LastLibC
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::error_code lastLibC();
/**
 * @brief Reset the errno of the standard C runtime library.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP void resetLastLibC();
/**
 * @brief Returns the last socket related error code.
 *
 * @details Some OS (e.g., Windows) require to call a different function
 * for socket related error codes in contrast to the standard C library.
 *
 * @snippet Utils/Test/UnitTest/TestError.cpp LastSocket
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::error_code lastSocket();
/**
 * @brief Reset the last socket related error in a platform independent way.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP void resetLastSocket();
/**
 * @brief Returns the last operating system error code.
 *
 * @details Some OS (e.g., Windows) distinguish between standard C library error
 * and OS library errors. So depending on whether a C or an OS function is
 * called different sources provide the error code.
 *
 * @snippet Utils/Test/UnitTest/TestError.cpp LastOs
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::error_code lastOs();
/**
 * @brief Reset the last operating system related error in a platform
 * independent way.
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP void resetLastOs();
}
}
