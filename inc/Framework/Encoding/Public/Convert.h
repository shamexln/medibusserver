#pragma once

#include <Framework/Encoding/Private/ExpImp.h>
#include <Framework/Encoding/Public/Byte.h>
#include <Framework/Encoding/Public/Bytes.h>
#include <Framework/Encoding/Public/BytesView.h>
#include <Framework/Encoding/Public/MutableBytesView.h>

#include <string>
#include <type_traits>

namespace DFL
{
namespace Encoding
{
class HexString;
class HexStringView;

/**
 * @brief Contains conversion functions.
 * @ingroup Encoding
 */
namespace Convert
{
/**
 * @brief Contains functions for converting bytes.
 * @ingroup Encoding
 */
namespace Bytes
{
/**
 * @brief Converts the given bytes into a hex string.
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp bytesAsHexString
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP Encoding::HexString asHexString(BytesView bytes);
/**
 * @brief Converts the given bytes into a string.
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp bytesAsString
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP std::string asString(BytesView bytes);
/**
 * @brief Converts the given bytes into bytes.
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp bytesAsBytes
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP ::DFL::Encoding::Bytes asBytes(BytesView bytes);
/**
 * @brief Converts the given container into a bytes view.
 *
 * Expects the container to be contiguous, (e. g. std::array, std::vector) and
 * expects that a pointer to the beginning of the contiguous memory can be
 * obtained via a call to data(container) and the size via size(container).
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp containerAsView
 *
 * @ingroup Encoding
 *
 * @{
 */
// for const LValues
template <class Container>
inline BytesView asView(const Container& c)
{
    using std::data;
    using std::size;
    return BytesView{data(c), size(c)};
}
// for non-const LValues
template <class Container>
inline BytesView asView(Container& c)
{
    using std::data;
    using std::size;
    return BytesView{data(c), size(c)};
}
// delete everything else
// especially RValues
// since that would lead to undefined behaviour
// a view with a dangling reference would be created
template <class Container>
auto asView(Container&&) = delete;
/**
 * @}
 */
/**
 * @brief Converts the given container into a mutable bytes view.
 *
 * Expects the container to be contiguous, (e. g. std::array, std::vector) and
 * expects that a pointer to the beginning of the contiguous memory can be
 * obtained via a call to data(container) and the size via size(container).
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp containerAsMutView
 *
 * @ingroup Encoding
 */
template <class Container>
inline MutableBytesView asMutableView(Container& c)
{
    using std::data;
    using std::size;
    return MutableBytesView{data(c), size(c)};
}
}
/**
 * @brief Contains functions for converting hex strings.
 * @ingroup Encoding
 */
namespace HexString
{
/**
 * @brief Converts the given hex string into bytes.
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp hexStringAsBytes
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP ::DFL::Encoding::Bytes asBytes(HexStringView hexString);
/**
 * @brief Converts the given hex string into a string.
 *
 * @snippet Encoding/Test/UnitTest/TestEncodingConvert.cpp hexStringAsString
 *
 * @ingroup Encoding
 */
DFL_ENCODING_EXPIMP std::string asString(HexStringView hexString);
}
}
}
}
