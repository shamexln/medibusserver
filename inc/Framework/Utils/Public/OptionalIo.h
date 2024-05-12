#pragma once
#include <optional>
#include <ostream>

// warning: modification of 'std' namespace can result in undefined behavior [cert-dcl58-cpp]
// NOLINTNEXTLINE(cert-dcl58-cpp)
namespace std
{

/**
 * @brief Makes std::optional streamable into a std::ostream.
 *
 * @snippet Utils/Test/UnitTest/TestUtilsOptionalIo.cpp StreamStdOptionalToOstream
 *
 * @ingroup Utils
 */
template <class T>
// NOLINTNEXTLINE(cert-dcl58-cpp)
inline std::ostream& operator<<(std::ostream& str,
                                const std::optional<T>& opt)
{
    if (opt)
    {
        str << *opt;
    }
    else
    {
        str << "--";
    }
    return str;
}

}
