#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>

namespace DFLTest
{
namespace Utils
{
struct MoveOnlyType
{
    explicit MoveOnlyType(int aa)
        : a{aa}
    {
    }
    explicit MoveOnlyType(std::unique_ptr<int> ee)
        : e{std::move(ee)}
    {
    }
    //! [CtorMoveOnlyType]
    MoveOnlyType(int aa,
                 std::string bb,
                 int cc,
                 double dd,
                 std::unique_ptr<int> ee = nullptr)
        : a{aa}
        , b{std::move(bb)}
        , c{cc}
        , d{dd}
        , e{std::move(ee)}
    {
    }
    //! [CtorMoveOnlyType]
    int a{};
    std::string b{};
    int c{};
    double d{};
    std::unique_ptr<int> e{};
};

inline bool operator==(const MoveOnlyType& a, const MoveOnlyType& b)
{
    if (a.e && b.e)
    {
        return std::tie(a.a, a.b, a.c, a.d, *a.e) ==
               std::tie(b.a, b.b, b.c, b.d, *b.e);
    }
    return std::tie(a.a, a.b, a.c, a.d, a.e) ==
           std::tie(b.a, b.b, b.c, b.d, b.e);
}

inline bool operator!=(const MoveOnlyType& a, const MoveOnlyType& b)
{
    return !(a == b);
}

inline std::ostream& operator<<(std::ostream& out, const MoveOnlyType& a)
{
    out << "a=" << a.a << " b=" << a.b << " c=" << a.c << " d=" << a.d << " e=";
    if (a.e)
    {
        out << (*a.e);
    }
    else
    {
        out << "nullptr";
    }
    return out;
}
}
}
