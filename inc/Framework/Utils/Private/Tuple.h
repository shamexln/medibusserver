#pragma once

#include <boost/mp11/integer_sequence.hpp>

#include <cstddef>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

namespace DFL
{
namespace StdExt
{
namespace Impl
{
template <class Tuple>
using tuple_size = std::tuple_size<typename std::remove_reference<Tuple>::type>;

template <std::size_t N, class Tuple>
inline constexpr Tuple replace_at(Tuple a, Tuple b)
{
    return std::get<N>(a) = std::get<N>(b), a;
}

template <class Tuple, class OutIter, std::size_t... Is>
inline /*constexpr in c++14*/ void slide(Tuple&& a,
                                         Tuple&& b,
                                         OutIter out,
                                         boost::mp11::index_sequence<Is...>)
{
    // see
    // https://codereview.stackexchange.com/questions/51407/stdtuple-foreach-implementation/67394#67394
    int const dummy[] = {0, ((*out++ = replace_at<Is>(a, b)), 0)...};
    static_cast<void>(dummy);
}

template <class Tuple, class OutIter>
inline /*constexpr in c++14*/ void slide(Tuple&& a, Tuple&& b, OutIter out)
{
    slide(std::forward<Tuple>(a),
          std::forward<Tuple>(b),
          out,
          boost::mp11::make_index_sequence<tuple_size<Tuple>::value>{});
}
}
}
}
