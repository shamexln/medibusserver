#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/RandomDevice.h>

#include <boost/uuid/random_generator.hpp>

#include <string>
#include <string_view>

namespace DFL::Crypto
{
/**
 * @brief Random UUID generator for @c boost::uuids::uuid.
 *
 * @details It is based on the @ref RandomDevice. Therefore the security of the
 * generated random numbers depends on @ref RandomDevice.
 *
 * @snippet Crypto/Sample/Sample.cpp RandomUuidGeneration
 *
 * @ingroup Crypto
 */
using RandomUuidGenerator =
    boost::uuids::basic_random_generator<DFL::Crypto::RandomDevice>;
/**
 * @brief Generates a random UUID as string.
 *
 * @snippet Crypto/Sample/Sample.cpp RandomUuidStr
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::string generateRandomUuidString();

/**
 * @brief Checks that a string is matching the UUID format.
 * @details
 * Lower and uppercase UUID strings will be accepted.
 *
 * @param uuid The string to check.
 *
 * @return True in case the string is a valid UUID.
 */
DFL_CRYPTO_EXPIMP bool isUuid(std::string_view uuid);
}
