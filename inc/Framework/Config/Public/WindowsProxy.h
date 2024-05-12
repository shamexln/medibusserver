#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

/**
 * @ingroup Config
 * @{
 *
 * @file WindowsProxy.h
 * @brief A proxy header file to be used instead of <Windows.h>.
 *
 * It configures windows.h so that just a subset of header files is included.
 * This avoids compile errors with other libraries which define the same symbols
 * as some headers from the win32 API.
 */

/** @} */
