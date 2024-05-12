#pragma once

#include <Framework/Config/Public/Config.h>

namespace DFL
{
/**
 * @brief Parameter shall not be optimized by compiler.
 *
 * @ingroup Utils
 */
template <class T>
void doNotOptimize(T&& t);

#if defined(DFL_CONFIG_COMPILER_MSVC)
#pragma optimize("", off)
template <class T>
inline void doNotOptimize(T&& t)
{
    reinterpret_cast<char volatile&>(t) =
        reinterpret_cast<char const volatile&>(t);
}
#pragma optimize("", on)
#else
template <class T>
inline void doNotOptimize(T&& t)
{
    asm volatile("" ::"m"(t) : "memory");
}
#endif
}
