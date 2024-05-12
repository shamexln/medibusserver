#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <limits>

namespace DFL
{
namespace Crypto
{
/**
 * @brief A uniformly-distributed random bit generator (URBG) that uses
 * OpenSSL RAND_bytes as random source.
 *
 * @details Implements the concept UniformRandomBitGenerator (see
 * https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator).
 *
 * @snippet Crypto/Test/UnitTest/TestOpenSslUrng.cpp RollDice
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP OpenSslUrng
{
public:
    OpenSslUrng() = default;
    OpenSslUrng(const OpenSslUrng&) = delete;
    OpenSslUrng& operator=(const OpenSslUrng&) = delete;
    /**
     * @brief Type of the value that operator() returns.
     */
    using result_type = unsigned int;
    /**
     * @brief Returns the smallest value that operator() may return.
     *
     * The value is strictly less than max().
     */
    static constexpr result_type(min)();
    /**
     * @brief Returns the largest value that operator() may return.
     *
     * The value is strictly greater than min().
     */
    static constexpr result_type(max)();
    /**
     * @brief Returns a value in the closed interval [min(), max()].
     *
     * Has amortized constant complexity.
     *
     * @throws std::runtime_error if RAND_bytes fails.
     */
    result_type operator()() const;
};

// As workaround for conflicts with the windows min/max macros,
// parenthesis are used around min/max
inline constexpr OpenSslUrng::result_type(OpenSslUrng::min)()
{
    return (std::numeric_limits<result_type>::min)();
}

inline constexpr OpenSslUrng::result_type(OpenSslUrng::max)()
{
    return (std::numeric_limits<result_type>::max)();
}
}
}
