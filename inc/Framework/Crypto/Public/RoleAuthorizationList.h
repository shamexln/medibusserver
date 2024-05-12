#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Private/Ral/Type.h>

#include <string>
#include <system_error>

namespace DFL
{
class Oid;
namespace Crypto
{
class Certificates;
/**
 * @brief Holds a string which specifies the roles a specific vendor is allowed
 * to have.
 *
 * In short this type is referred to as RAL and the format of the string has to
 * be:
 * ```
 * <Comment>\n
 * <Fingerprint_1>;<Role_1>,<Role_2>, ...\n
 * <Fingerprint_2>;<Role_3>,<Role_4>, ...\n
 * <Fingerprint_n>;<Role_x>,<Role_y>, ...\n
 * <Signature>\n
 * ```
 *
 * The format of the tags used above is:
 * - \<Comment> String of arbitrary length
 * - \<Fingerprint> Hexadecimal string of length 64
 * - \<Role> String containing an OID in dot notation (see @ref DFL::Oid)
 * - \<Signature> Empty or hexadecimal string of length 512
 *
 * Example string:
 * ```
 * This is a comment\n
 * 6bd2915e982d309d3f8fd7baa501c36ba4c4770c06f5225db846a82b10e9db54;1.3.6.1.5.5.7.3.1,1.3.6.1.5.5.7.3.2,1.2.840.10004.20701.1.1,1.2.840.10004.20701.1.2\n
 * 46e197999cd98ecbec047bb499aa9926a8803baa2aadb566183ad064f902cdbc6c6967bcc1c4fa81a62126fd9ea252e2bdc9713114b1e4571a96754c02ef62c5ae5c4f62080cc671d732cb619802d58150ebccdc67f94424f53ba5f4a79986b81a588f73ac5afb621b75bdf92de275972b86347c9653126d9d111c590015258fd86e1715c26452df16511c044e3a6b45872deace3a9f50e9f43e82dec72a0c86b708bf8309eee23b0b8ae824102207182f02b345c3e53ae98b1ca2f2c9a751c0a23ac89be95725771d6b10cd7536e4c8d073b1ada1f5fb8dc59bd52df2948373b58ed13d0dc034938204c7326c38a76698f8888daec10a1b378c87154e02623d\n
 * ```
 *
 * The vendor is specified by the fingerprint of its CA. To verify the
 * correctness of this list it is signed by an RSA-2048 algorithm. The
 * verification of the signature is done by the valid function, not during
 * construction.
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP RoleAuthorizationList
{
public:
    /**
     * @brief Creates an empty role authorization list.
     *
     * A default constructed role authorization list is always valid.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp DefaultCtor
     */
    RoleAuthorizationList() = default;
    /**
     * @brief Creates a role authorization list from str.
     *
     * @throw std::runtime_error On invalid format of str.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp StrCtor
     */
    explicit RoleAuthorizationList(std::string str);
    /**
     * @brief Returns the string given on construction.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp StrCtor
     */
    const std::string& str() const noexcept;
    /**
     * @brief True if this RAL is empty otherwise false.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp Empty
     */
    bool empty() const noexcept;
    /**
     * @brief
     * Returns true if verification of signature succeeds, otherwise false.
     *
     * An empty role authorization list is always valid.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp Valid
     */
    bool valid() const;
    /**
     * @brief
     * Returns true if role could be found for given certificates,
     * otherwise false.
     * Returns always true if given certificates contain Draeger device root.
     *
     * Iterates over the given certificates and creates a fingerprint from each
     * of them. Then each fingerprint is looked up within the RAL. If a
     * fingerprint is found the according roles are then checked if they contain
     * the given role. Then and only then this function returns true.
     * In case of returning false the provided error code is filled with a value
     * representing the cause of the failure.
     * For details look at @ref DFL::Crypto::Error::Ral.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp Success
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp RoleNotFound
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp FpNotFound
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp DeviceRoot
     *
     * If called on an empty instance, only returns true if given certificates
     * contain Draeger device root. Otherwise false is returned.
     *
     * @snippet Crypto/Test/UnitTest/TestRoleAuthorizationList.cpp EmptyRal
     */
    bool containsRoleFor(const Certificates& certs,
                         const Oid& role,
                         std::error_code& ec) const;
    /**
     * @brief Returns true if other is equal to *this, otherwise false.
     */
    bool equals(const RoleAuthorizationList& other) const noexcept;
    /**
     * @brief Swaps content of other with this.
     */
    void swap(RoleAuthorizationList& other) noexcept;

private:
    std::string m_str{};
    Impl::Ral::Type m_ral{};
};
/**
 * @brief Returns true if a is equal to b, otherwise false.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP bool operator==(const RoleAuthorizationList& a,
                                  const RoleAuthorizationList& b) noexcept;
/**
 * @brief Returns true if a is not equal to b, otherwise false.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP bool operator!=(const RoleAuthorizationList& a,
                                  const RoleAuthorizationList& b) noexcept;
/**
 * @brief Swaps content of a with b.
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void swap(RoleAuthorizationList& a,
                            RoleAuthorizationList& b) noexcept;
}
}
