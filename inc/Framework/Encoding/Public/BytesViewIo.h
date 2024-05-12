#pragma once

#include <Framework/Encoding/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Encoding
{
class BytesView;
/**
 * @brief Creates readable form of given bytes view.
 *
 * @snippet Encoding/Test/UnitTest/TestBytesView.cpp streaming
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP std::ostream& operator<<(std::ostream& str,
                                             const BytesView& bytes);
}
}

namespace DFL
{
namespace Encoding
{
class BytesView;
}
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given bytes view.
 *
 * @snippet Encoding/Test/UnitTest/TestBytesView.cpp streaming
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP Stream& operator<<(Stream& str,
                                       const Encoding::BytesView& bytes);
}
}
