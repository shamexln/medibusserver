#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_COMPILER_MSVC)
#pragma warning(push)
// conversion from 'X' to 'Y', signed/unsigned mismatch
#pragma warning(disable : 4365)
// 'X' is not defined as a preprocessor macro, replacing with '0' for
// '#if/#elif'
#pragma warning(disable : 4668)
#endif

#include <Framework/Format/SOUP/cppformat/Format.h>

#if defined(DFL_CONFIG_COMPILER_MSVC)
#pragma warning(pop)
#endif
