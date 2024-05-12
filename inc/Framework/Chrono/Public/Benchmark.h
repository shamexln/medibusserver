#pragma once

#include <Framework/Chrono/Private/Benchmark.h>
#include <Framework/Chrono/Public/Stopwatch.h>

#include <Framework/Config/Public/Config.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <utility>

namespace DFL
{
namespace Chrono
{
/**
 * @brief Iterations tag type.
 *
 * @ingroup Chrono
 */
struct IterationsTag;
/**
 * @brief Named parameter for the specifying the amount of iterations.
 *
 * @ingroup Chrono
 */
using Iterations = StrongTypedef<int, IterationsTag>;
/**
 * @brief Executes given function n-times and returns the execution time
 * measured by given stopwatch type.
 *
 * @snippet Chrono/Test/UnitTest/TestBenchmark.cpp FuncWithSwN
 *
 * @ingroup Chrono
 */
template <class StopwatchType, class Func>
typename StopwatchType::duration benchmark(Iterations n, Func func);
/**
 * @brief Executes given function once and returns the execution time
 * measured by given stopwatch type.
 *
 * @snippet Chrono/Test/UnitTest/TestBenchmark.cpp FuncWithSw
 *
 * @ingroup Chrono
 */
template <class StopwatchType, class Func>
typename StopwatchType::duration benchmark(Func func);
/**
 * @brief Executes given function n-times and returns the execution time.
 *
 * Uses @ref DFL::Chrono::Stopwatch for measuring execution time.
 *
 * @snippet Chrono/Test/UnitTest/TestBenchmark.cpp FuncN
 *
 * @ingroup Chrono
 */
template <class Func>
Stopwatch::duration benchmark(Iterations n, Func func);

/**
 * @brief Executes given function once and returns the execution time.
 *
 * Uses @ref DFL::Chrono::Stopwatch for measuring execution time.
 *
 * @snippet Chrono/Test/UnitTest/TestBenchmark.cpp Func
 *
 * @ingroup Chrono
 */
template <class Func>
Stopwatch::duration benchmark(Func func);

#if defined(DFL_CONFIG_COMPILER_MSVC)
#pragma warning(push)
#pragma warning(disable : 4702)
// : warning C4702: unreachable code
//
// This warning only occurs in non debug builds.
// Reason being that the to be benchmarked function is executed within a
// loop.
// Since this function might throw on the first call the part of the loop
// incrementing the iterations counter is never executed. Thus this warning
// is emitted and can be safely ignored.
#endif

template <class StopwatchType, class Func>
inline typename StopwatchType::duration benchmark(Iterations n, Func func)
{
    StopwatchType sw{};
    sw.start();
    Impl::Benchmark::invoke_n(n.get(), std::move(func));
    sw.stop();
    return sw.elapsed();
}

#if defined(DFL_CONFIG_COMPILER_MSVC)
#pragma warning(pop)
#endif

template <class StopwatchType, class Func>
inline typename StopwatchType::duration benchmark(Func func)
{
    return benchmark<StopwatchType>(Iterations{1}, std::move(func));
}

template <class Func>
inline Stopwatch::duration benchmark(Iterations n, Func func)
{
    return benchmark<Stopwatch>(n, std::move(func));
}

template <class Func>
inline Stopwatch::duration benchmark(Func func)
{
    return benchmark(Iterations{1}, std::move(func));
}
}
}
