#pragma once

#include <boost/config.hpp>

/**
 * @ingroup Config
 * @{
 *
 * @file
 * @brief Macros controlling shared library symbol visibility.
 *
 * Some compilers support C++ extensions that control which symbols will be
 * exported from shared libraries such as dynamic shared objects (DSO's) on
 * Unix-like systems or dynamic-link libraries (DLL's) on Windows. The Microsoft
 * VC++ compiler has long supplied __declspec(dllexport) and
 * __declspec(dllimport) extensions for this purpose, as do virtually all other
 * compilers targeting the Windows platform. Modern versions of the GNU GCC
 * compiler provide the __attribute__((visibility("default"))) extension to
 * indicate that a symbol should be exported. All other symbols may be hidden by
 * using the -fvisibility-hidden or -fvisibility-ms-compat compiler switches.
 */
#if defined(PLATFORM_DO_STATIC_LINKAGE)
#define DFL_DLL_IMPORT
#define DFL_DLL_EXPORT
#else
#define DFL_DLL_IMPORT BOOST_SYMBOL_IMPORT
#define DFL_DLL_EXPORT BOOST_SYMBOL_EXPORT
#endif
/** @} */
