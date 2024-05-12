#pragma once

#include <Framework/Chrono/Private/BasicDateTime.h>

#include <ostream>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
template <typename T>
inline std::ostream& operator<<(std::ostream& str, const BasicDateTime<T>& bdt)
{
    str << bdt.toIso8601();
    return str;
}
}
}
}
