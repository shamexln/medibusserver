#pragma once

namespace DFL
{
namespace Log
{
/**
 * @brief Flushes all contents from src into dest.
 *
 * src will be empty afterwards.
 *
 * @ingroup Log
 */
template<class Container, class UnaryFunctor>
inline void flush(Container& src, UnaryFunctor& dest)
{
    typename Container::const_iterator b(src.cbegin());
    typename Container::const_iterator const e(src.cend());
    for(; b != e; ++b)
    {
        static_cast<void>(dest(*b));
    }
    src.clear();
}
}
}
