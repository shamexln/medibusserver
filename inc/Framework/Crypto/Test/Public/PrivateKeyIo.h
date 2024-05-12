#pragma once

#include <Framework/Crypto/Public/Convert.h>
#include <Framework/Crypto/Public/PemString.h>
#include <Framework/Crypto/Public/PemStringIo.h>
#include <Framework/Crypto/Public/PrivateKey.h>

#include <ostream>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Creates readable form of given private key.
 *
 * @ingroup Crypto
 */
std::ostream& operator<<(std::ostream& str, const PrivateKey& pk);

inline std::ostream& operator<<(std::ostream& str, const PrivateKey& pk)
{
    str << ::DFL::Crypto::Convert::toPem(pk);
    return str;
}
}
}
