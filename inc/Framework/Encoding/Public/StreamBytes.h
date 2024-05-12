#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>

#include <iostream>

namespace DFL
{
namespace Encoding
{
/**
 * @brief Contains functions for extracting/appending bytes from/to streams.
 * @ingroup Encoding
 */
namespace Stream
{
/**
 * @brief Appends the given bytes to the given ostream.
 *
 * @snippet Encoding/Test/UnitTest/TestStreamBytes.cpp appendBytesAscii
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP void appendBytes(BytesView bytes, std::ostream& os);
/**
 * @brief Extracts bytes from the given istream.
 *
 * @snippet Encoding/Test/UnitTest/TestStreamBytes.cpp extractBytesAscii
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP Bytes extractBytes(std::istream& is);
}
}
}
