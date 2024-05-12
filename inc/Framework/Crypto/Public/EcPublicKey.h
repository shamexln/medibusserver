#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

namespace DFL::Crypto
{
class Coordinates;
class PublicKey;
}
namespace DFL::Crypto::EcPublicKey
{
/**
 * @brief Returns the coordinates of given public-key.
 *
 * @throws std::runtime_error If key is not an elliptic-curve-key or openssl
 * could not retrieve the coordinates from given key.
 *
 * @snippet Crypto/Test/UnitTest/TestEcPublicKey.cpp coordinates
 *
 * @ingroup Crypto
 */
[[nodiscard]] DFL_CRYPTO_EXPIMP Coordinates
affineCoordinates(const PublicKey& pub);
}
