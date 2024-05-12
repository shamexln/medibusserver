#pragma once

#include <Framework/Encoding/Public/BytesView.h>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
template <class Algorithm>
inline void apply(Algorithm& algorithm, Encoding::BytesView message)
{
    algorithm.init();
    algorithm.update(message);
    algorithm.final();
}
}
}
}
