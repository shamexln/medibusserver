#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <limits>

namespace DFL
{
namespace Crypto
{
/**
 * @brief A uniformly-distributed random bit generator (URBG) that uses the
 * random source injected via @ref DFL::Crypto::Registry::randSource.
 *
 * @details
 * - Implements the concept UniformRandomBitGenerator
 * (see https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator).
 * - By default DFL::Crypto::OpenSslUrng is used as random source.
 *
 * Cryptographically secure usage:
 * @snippet Crypto/Sample/Sample.cpp RandomDeviceCryptographicallySecure
 *
 * Cryptographically unsecure usage:
 * @snippet Crypto/Sample/Sample.cpp RandomDeviceCryptographicallyUnsecure
 *
 * Change the internal random source:
 * @snippet Crypto/Test/UnitTest/TestRandomDevice.cpp RandomDeviceInjection
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP RandomDevice
{
public:
    /**
     * @brief Constructs the random number generator.
     */
    RandomDevice() = default;
    /**
     * @brief Type of the value that operator() returns.
     */
    using result_type = unsigned int;
    /**
     * @brief Returns the smallest value that operator() may return. The value
     * is strictly less than max().
     */
    static constexpr result_type(min)();
    /**
     * @brief Returns the largest value that operator() may return. The value is
     * strictly greater than min().
     */
    static constexpr result_type(max)();
    /**
     * @brief Returns a value in the closed interval [min(), max()]. Has
     * amortized constant complexity.
     * @throws whatever @ref DFL::Crypto::Registry::randSource throws.
     */
    result_type operator()() const;

    RandomDevice(const RandomDevice&) = delete;
    RandomDevice& operator=(const RandomDevice&) = delete;
};

// As workaround for conflicts with the windows min/max macros,
// parenthesis are used around min/max

inline constexpr RandomDevice::result_type(RandomDevice::min)()
{
    return (std::numeric_limits<result_type>::min)();
}

inline constexpr RandomDevice::result_type(RandomDevice::max)()
{
    return (std::numeric_limits<result_type>::max)();
}
}
}
