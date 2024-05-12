#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>

#include <cstddef>
#include <string>

namespace DFL::Crypto
{
class AttributeTypeAndValue;
class Certificate;
class CertificateChain;
class Csr;
class DerFormat;
class DistinguishedName;
class PemString;
class PrivateKey;
class PublicKey;
class BigNumber;

namespace MessageDigest::Signature
{
class EcdsaSig;
}

namespace Convert
{
/**
 * @brief Convert given certificate to PEM string.
 *
 * @details Returns an empty PEM if certificate handle is null.
 *
 * @throw std::runtime_error if PEM could not be created from handle.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp certificate
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPem(const Certificate& certificate);
/**
 * @brief Convert given chain to PEM string.
 *
 * @throw whatever format stream operator of certificate throws.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp certificateChain
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPem(const CertificateChain& chain);
/**
 * @brief Convert given csr to PEM string.
 *
 * @details Returns an empty PEM if csr handle is null.
 *
 * @throw std::runtime_error if PEM could not be created from handle.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp csr
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPem(const Csr& csr);
/**
 * @brief Convert given private key to PEM string.
 *
 * @details
 * Returns an empty PEM if private key handle is null.
 * The returned PEM is in PKCS #8 format.
 *
 * @throw std::runtime_error if PEM could not be created from handle.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp privateKey
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPem(const PrivateKey& privateKey);
/**
 * @brief Convert given public key to PEM string.
 *
 * @details
 * Returns an empty PEM if public key handle is null.
 * The returned PEM is in PKCS #8 format.
 *
 * @throw std::runtime_error if PEM could not be created from handle.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp publicKey
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPem(const PublicKey& publicKey);
/**
 * @brief Convert given private key to PEM string in PKCS #8 format.
 *
 * @details Returns an empty PEM if private key handle is null.
 *
 * @throw std::runtime_error if PEM could not be created from handle.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp privateKeyPkcs8
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPemPkcs8(const PrivateKey& privateKey);
/**
 * @brief Convert given public key to PEM string in PKCS #8 format.
 *
 * @details Returns an empty PEM if public key handle is null.
 *
 * @throw std::runtime_error if PEM could not be created from handle.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp publicKeyPkcs8
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP PemString toPemPkcs8(const PublicKey& publicKey);
/**
 * @brief Convert given attribute to RFC 4514 compatible string.
 * @details
 * See [RFC 4514](https://www.ietf.org/rfc/rfc4514.txt).
 * String shall be identical to X509_NAME_print_ex with XN_FLAG_RFC2253.
 *
 * @throw std::runtime_error if string could not be created.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp AttributeTypeAndValue
 */
DFL_CRYPTO_EXPIMP std::string toRfc4514(const AttributeTypeAndValue& attr);
/**
 * @brief Convert given distinguished name to RFC 4514 compatible string.
 * @details
 * See [RFC 4514](https://www.ietf.org/rfc/rfc4514.txt).
 * String shall be identical to X509_NAME_print_ex with XN_FLAG_RFC2253.
 *
 * @throw std::runtime_error if string could not be created.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp DistinguishedName
 *
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::string toRfc4514(const DistinguishedName& dn);
/**
 * @brief Create a DER encoded representation of given ecdsaSig.
 *
 * @throw std::runtime_error in case of an error.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp ecdsaSig
 */
DFL_CRYPTO_EXPIMP DerFormat
toDer(const MessageDigest::Signature::EcdsaSig& ecdsaSig);
/**
 * @brief Converts bignumber into bytes.
 *
 * @throw std::runtime_error in case of an error.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp bignumbytes
 */
DFL_CRYPTO_EXPIMP Encoding::Bytes toBytes(const BigNumber& bn);
/**
 * @brief Converts bignumber into bytes with padding.
 *
 * If the bignumber has less bytes than given size the returned bytes are
 * padded with zeros at the front. If the bignumber has more bytes than the
 * given size an exception is thrown.
 *
 * @throw std::runtime_error in case of an error.
 *
 * @snippet Crypto/Test/UnitTest/TestCryptoConvert.cpp bignumbytespad
 */
DFL_CRYPTO_EXPIMP Encoding::Bytes toBytesWithPad(const BigNumber& bn,
                                                 std::size_t s);
}
}
