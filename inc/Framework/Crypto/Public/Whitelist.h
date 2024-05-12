#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <string>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Holds data which identifies valid communication partners.
 * Since the format of the list is defined by the component which
 * uses it only a generic string is stored.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Whitelist
{
public:
    /**
     * @brief Creates an empty list.
     *
     * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp defaultCtor
     */
    Whitelist() = default;
    /**
     * @brief Creates list from given string.
     *
     * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp ctorString
     */
    explicit Whitelist(std::string data) noexcept;
    /**
     * @name Sets/Returns the hold data as string.
     *
     * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp str
     * @{
     */
    const std::string& str() const& noexcept;
    std::string&& str() && noexcept;
    void str(const std::string& data);
    /** @} */
private:
    std::string m_str{};
};
/**
 * @brief True if two lists contain the same data string otherwise false.
 *
 * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp compareOps
 *
 * @ingroup Crypto
 * @{
 */
DFL_CRYPTO_EXPIMP bool operator==(const Whitelist& lhs, const Whitelist& rhs) noexcept;
DFL_CRYPTO_EXPIMP bool operator!=(const Whitelist& lhs, const Whitelist& rhs) noexcept;
/** @} */
}
}
