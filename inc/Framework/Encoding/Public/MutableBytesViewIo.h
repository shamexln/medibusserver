#pragma once

#include <Framework/Encoding/Private/ExpImp.h>

#include <iosfwd>

namespace DFL::Format
{
class Stream;
}
namespace DFL::Encoding
{
class MutableBytesView;
}
namespace DFL::Encoding
{
DFL_ENCODING_EXPIMP std::ostream& operator<<(std::ostream& str,
                                             const MutableBytesView& bytes);
DFL_ENCODING_EXPIMP Format::Stream& operator<<(Format::Stream& str,
                                               const MutableBytesView& bytes);
}
