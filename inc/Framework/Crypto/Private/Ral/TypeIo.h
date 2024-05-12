#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Ral/Type.h>

#include <iosfwd>

namespace DFL
{
namespace Format
{
class Stream;
}
namespace Crypto
{
namespace Impl
{
namespace Ral
{
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const Type& ral);
DFL_CRYPTO_EXPIMP Format::Stream& operator<<(Format::Stream& str,
                                             const Type& ral);
}
}
}
}
