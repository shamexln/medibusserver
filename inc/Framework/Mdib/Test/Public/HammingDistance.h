#pragma once

#include <algorithm>
#include <cstdint>
#include <type_traits>

namespace DFL::Mdib::Test
{

inline int numberOfSetBits(unsigned int n)
{
    std::size_t count = 0U;
    while (n)
    {
        count += n & 1U;
        n >>= 1;
    }
    return static_cast<int>(count);
}

template<class T>
int hammingDistance(T a, T b)
{
    static_assert(sizeof(T) == sizeof(unsigned int));
    if constexpr (std::is_enum<T>::value)
    {
        using U = typename std::underlying_type<T>::type;
        U const d = static_cast<U>(a) ^ static_cast<U>(b);
        return numberOfSetBits(d);
    }
    else
    {
        T d = a ^ b;
        return numberOfSetBits(d);
    }
}

template<class T>
int hammingDistance(T a, T b, T c)
{
    return (std::min)(
        {hammingDistance(a, b), hammingDistance(a, c), hammingDistance(b, c)});
}

template<class T>
int hammingDistance(T a, T b, T c, T d)
{
    return (std::min)({hammingDistance(a, b),
                       hammingDistance(a, c),
                       hammingDistance(a, d),
                       hammingDistance(b, c, d)});
}

}
