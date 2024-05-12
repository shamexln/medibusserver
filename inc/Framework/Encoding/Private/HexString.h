#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <Framework/Encoding/Public/Byte.h>

namespace DFL
{
namespace Encoding
{
namespace Impl
{
DFL_ENCODING_EXPIMP ::DFL::Encoding::Byte hexNibbleAsByte(char c);
DFL_ENCODING_EXPIMP void ensureHexString(const char* cstr, size_t size);
}
}
}
