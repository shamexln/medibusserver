#pragma once

#include <Framework/Utils/Public/DoNotOptimize.h>

#include <type_traits>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
class Benchmark
{
public:
    template <class Func>
    static void invoke_n(int n, Func func);
};

template <class Func>
inline void Benchmark::invoke_n(int n, Func func)
{
    for (int i{}; i < n; ++i)
    {
        if constexpr (std::is_void_v<decltype(func())>)
        {
            func();
        }
        else
        {
            volatile auto&& res{func()};
            doNotOptimize(res);
        }
    }
}
}
}
}
