#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <iosfwd>

namespace DFL
{
namespace Crypto
{
class Configuration;
/**
 * @brief Creates readable form of given configuration.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::ostream& operator<<(std::ostream& str, const Configuration& config);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given configuration.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP Stream& operator<<(Stream& str, const Crypto::Configuration& config);
}
}
