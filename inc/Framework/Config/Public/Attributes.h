#pragma once

#include <Framework/Config/Public/Config.h>
#include <boost/config/helper_macros.hpp>

/**
 * @def DFL_ATTRIBUTE_NODISCARD
 * @brief Define for [[nodiscard]].
 *
 * @details
 * Workaround for older doxygen versions which cannot handle documentation of
 * [[nodiscard]] types properly.
 *
 * @ingroup Config
 */
#define DFL_ATTRIBUTE_NODISCARD [[nodiscard]]

/**
 * @def DFL_ATTRIBUTE_DEPRECATED
 * @brief Marks a symbol as deprecated.
 *
 * The deprecated warning has to be enabled by defining \c
 * DFL_ENABLE_DEPRECATED. In that case it either resolves to [[deprecated(msg)]]
 * or to [[gnu::deprecated(msg)]] if gcc is detected.
 * If your software only has to support msvc do not use this macro just use the
 * c++14 deprecated attribute. Compilers typically issue warnings on such uses.
 * The string-literal msg, is usually included in the warnings.
 * This attribute is allowed in declarations of the following names or entities:
 * @snippet Config/Test/UnitTest/TestAttributes.cpp Deprecations
 *
 * @ingroup Config
 */
#if !defined(DFL_ENABLE_DEPRECATED)
#define DFL_ATTRIBUTE_DEPRECATED(msg)
#elif defined(DFL_CONFIG_COMPILER_GCC)
#define DFL_ATTRIBUTE_DEPRECATED(msg) [[gnu::deprecated(msg)]]
#else
#define DFL_ATTRIBUTE_DEPRECATED(msg) [[deprecated(msg)]]
#endif
/**
 * @def DFL_HEADER_DEPRECATED
 * @brief Macro to mark a header file as deprecated.
 * @details The deprecated warning has to be enabled by defining \c
 * DFL_ENABLE_DEPRECATED. For gcc it generates a compiler warning, while for
 * MSVC only prints out a message in warning format to allow for warning
 * parsing.
 *
 * The deprecated error has to be enabled by defining both \c
 * DFL_ENABLE_DEPRECATED and \c DFL_ENABLE_DEPRECATED_ERROR. For both gcc and
 * MSVC it generates a compilation error.
 *
 * @ingroup Config
 */
#if !defined(DFL_ENABLE_DEPRECATED)
// warnings are not enabled, default is to be off
#define DFL_HEADER_DEPRECATED(x)
#elif !defined(DFL_ENABLE_DEPRECATED_ERROR)
// warnings are enabled, errors are not enabled
#if defined(DFL_CONFIG_COMPILER_GCC) || defined(DFL_CONFIG_COMPILER_CLANG)
#define DFL_HEADER_DEPRECATED(x) _Pragma(BOOST_STRINGIZE(GCC warning x))
#elif defined(DFL_CONFIG_COMPILER_MSVC)
// It is required to add a warning number (e.g., C4996) for the Jenkins
// MSBuild Warnings plug-in for example. The plug-in requires the value
// to fill the "Category" column in the output.
// Also the filename is added to the message to provide correct details in the
// output. MSVC creates the following log message for the deprecated attribute:
// source.cpp(19): warning C4996: 'i': was declared deprecated
// The macro now expand to
// source.h(15): warning C4996: 'C:\full\directory\path\source.h': this header
// was declared deprecated, MyMessageString
#define DFL_HEADER_DEPRECATED(x)                                               \
    __pragma(message(__FILE__ "(" BOOST_STRINGIZE(                             \
        __LINE__) "): warning C4996: '" __FILE__                               \
                  "': this header was declared deprecated, " x))
#else
// unknown compiler
#define DFL_HEADER_DEPRECATED(x)
#endif
#else
// errors are enabled
#if defined(DFL_CONFIG_COMPILER_GCC) || defined(DFL_CONFIG_COMPILER_CLANG)
#define DFL_HEADER_DEPRECATED(x) _Pragma(BOOST_STRINGIZE(GCC error x))
#elif defined(DFL_CONFIG_COMPILER_MSVC)
// source.h(15): error C2338: 'C:\full\directory\path\source.h': this header was
// declared deprecated, MyMessageString
#define DFL_HEADER_DEPRECATED(x)                                               \
    static_assert(!"deprecated",                                               \
                  "'" __FILE__ "': this header was declared deprecated, " x);
#else
#error Unknown compiler
#endif
#endif
