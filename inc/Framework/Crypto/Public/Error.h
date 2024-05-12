#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <system_error>

namespace DFL
{
namespace Crypto
{
namespace Error
{
/**
 * @brief RAL error values
 *
 * @ingroup Crypto
 */
enum class Ral
{
    /** No error occured. */
    Success = 0, // 0 is considered success when using std::error_code
    /** The RAL did not include the given role. */
    RoleNotFound,
    /** The RAL did not include any fingerprint from the give certificates. */
    FingerprintNotFound,
    /** An unknown error occured. */
    Unknown
};
/**
 * @brief Creates an std::error_code from the given error value.
 *
 * This function is only available to implement the customization point
 * provided by std::error_code. Clients can just construct
 * an std::error_code like this:
 *
 * @code
 * std::error_code ec = Ral::Success;
 * @endcode
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::error_code make_error_code(Ral e);
}
}
}
namespace std
{
/**
 * @brief Tells std::error_code that RAL error values are acceptable for
 * constructing std::error_codes.
 *
 * @ingroup Crypto
 */
template <>
struct is_error_code_enum<::DFL::Crypto::Error::Ral> : true_type
{
};
}
