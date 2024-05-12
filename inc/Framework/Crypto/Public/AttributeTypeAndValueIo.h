#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class AttributeTypeAndValue;
/**
 * @brief Creates readable form of given attribute.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp Streaming
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const AttributeTypeAndValue& attr);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given attribute.
 *
 * @snippet Crypto/Test/UnitTest/TestAttributeTypeAndValue.cpp Streaming
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::AttributeTypeAndValue& attr);
}
}
