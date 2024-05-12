#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_COMPILER_MSVC)
#if !defined(_MSC_FULL_VER)
#error "did not detect msvc"
#endif
#endif

#if defined(DFL_CONFIG_COMPILER_GCC)
#if !defined(__GNUC_MINOR__)
#error "did not detect gcc"
#endif
#endif

#if defined(DFL_CONFIG_COMPILER_CLANG)
#if !defined(__clang_minor__)
#error "did not detect clang"
#endif
#endif
