#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>
// do not include any openssl header files in header files of this library
// since openssl is implemented in C, symbol names clash with names in other
// libraries which might be used together with this lib
// forward declare all openssl symbols in the OpenSslFwd header file
// and then include the necessary openssl header files in the according cpp file
#include <cstddef>
#include <memory>
#include <string>
#include <tuple>

namespace DFL
{
class Oids;
namespace Crypto
{
namespace OpenSsl
{
/*
 * Wraps the OPENSSL_Free macro so we can use it as a deleter for unique_ptr
 */
DFL_CRYPTO_EXPIMP void OpenSslFree(void* addr);
DFL_CRYPTO_EXPIMP void stackOfX509Deleter(struct stack_st_X509*);
DFL_CRYPTO_EXPIMP void stackOfX509ExtensionDeleter(
    struct stack_st_X509_EXTENSION*);

using CharPtr = std::unique_ptr<char, decltype(&OpenSslFree)>;
using Asn1TimePtr = std::unique_ptr<::ASN1_TIME, decltype(&::ASN1_TIME_free)>;
using BignumPtr = std::unique_ptr<::BIGNUM, decltype(&::BN_free)>;
using BnGencbPtr = std::unique_ptr<::BN_GENCB, decltype(&::BN_GENCB_free)>;
using EvpCipherContextPtr =
    std::unique_ptr<::EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;
using EvpMdContextPtr =
    std::unique_ptr<::EVP_MD_CTX, decltype(&::EVP_MD_CTX_free)>;

/**
 * @brief A generic structure to hold diverse types of asymmetric keys.
 *
 * @details
 * The asymmetric keys (also known as "key pairs") can be used for diverse
 * operations, like signing, verifying signatures, key derivation, etc.
 *
 * Conceptually, the EVP_PKEY internal key may hold a private key, a public
 * key, or both (a keypair), and along with those, key parameters if the key
 * type requires them.
 * The presence of these components determine what operations can be made;
 * for example, signing normally requires the presence of a private key,
 * and verifying normally requires the presence of a public key.
 */
using EvpPkeyPtr = std::unique_ptr<::EVP_PKEY, decltype(&::EVP_PKEY_free)>;
using EvpPkeyCtxPtr =
    std::unique_ptr<::EVP_PKEY_CTX, decltype(&::EVP_PKEY_CTX_free)>;

using RsaPtr = std::unique_ptr<::RSA, decltype(&::RSA_free)>;
using EcKeyPtr = std::unique_ptr<::EC_KEY, decltype(&::EC_KEY_free)>;
using X509Ptr = std::unique_ptr<::X509, decltype(&::X509_free)>;
#ifndef _WIN32
using X509ExtensionPtr =
    std::unique_ptr<::X509_EXTENSION, decltype(&::X509_EXTENSION_free)>;
using X509NamePtr = std::unique_ptr<::X509_NAME, decltype(&::X509_NAME_free)>;
#else
using X509ExtensionPtr =
    std::unique_ptr<::X509_extension_st, decltype(&::X509_EXTENSION_free)>;
using X509NamePtr =
    std::unique_ptr<::X509_name_st, decltype(&::X509_NAME_free)>;
#endif
using X509ReqPtr = std::unique_ptr<::X509_REQ, decltype(&::X509_REQ_free)>;
using X509StorePtr =
    std::unique_ptr<::X509_STORE, decltype(&::X509_STORE_free)>;
using X509StoreCtxPtr =
    std::unique_ptr<::X509_STORE_CTX, decltype(&::X509_STORE_CTX_free)>;
using X509VerifyParamPtr =
    std::unique_ptr<::X509_VERIFY_PARAM, decltype(&::X509_VERIFY_PARAM_free)>;
using StackOfX509 =
    std::unique_ptr<struct stack_st_X509, decltype(&stackOfX509Deleter)>;
using StackOfX509Extension =
    std::unique_ptr<struct stack_st_X509_EXTENSION,
                    decltype(&stackOfX509ExtensionDeleter)>;
using Asn1ObjectPtr =
    std::unique_ptr<::ASN1_OBJECT, decltype(&::ASN1_OBJECT_free)>;
using BasicConstraintsPtr =
    std::unique_ptr<::BASIC_CONSTRAINTS, decltype(&::BASIC_CONSTRAINTS_free)>;
using Asn1OctetStringPtr =
    std::unique_ptr<::ASN1_OCTET_STRING, decltype(&::ASN1_OCTET_STRING_free)>;
using Asn1BitStringPtr =
    std::unique_ptr<::ASN1_BIT_STRING, decltype(&::ASN1_BIT_STRING_free)>;
using AuthorityKeyIdPtr =
    std::unique_ptr<::AUTHORITY_KEYID, decltype(&::AUTHORITY_KEYID_free)>;
using ExtendedKeyUsagePtr =
    std::unique_ptr<::EXTENDED_KEY_USAGE, decltype(&::EXTENDED_KEY_USAGE_free)>;
/**
 * @brief Leak free OpenSSL \c BIO pointer.
 * @details It uses \c BIO_free_all to free up an entire BIO chain,
 * it does not halt if an error occurs freeing up an individual BIO in the
 * chain. https://www.openssl.org/docs/man1.0.2/crypto/BIO_set.html
 *
 * Chain support is required, since chains of PEM strings will also be read with
 * this type.
 */
using BioPtr = std::unique_ptr<::BIO, decltype(&::BIO_free_all)>;
using EcdsaSigPtr = std::unique_ptr<::ECDSA_SIG, decltype(&::ECDSA_SIG_free)>;

DFL_CRYPTO_EXPIMP CharPtr CharNullptr() noexcept;
DFL_CRYPTO_EXPIMP EvpCipherContextPtr EvpCipherContextNew();
DFL_CRYPTO_EXPIMP EvpCipherContextPtr EvpCipherContextNullptr() noexcept;
DFL_CRYPTO_EXPIMP EvpMdContextPtr EvpMdContextNew();
DFL_CRYPTO_EXPIMP EvpMdContextPtr EvpMdContextNullptr() noexcept;
DFL_CRYPTO_EXPIMP X509ReqPtr X509ReqNullptr() noexcept;
DFL_CRYPTO_EXPIMP X509ReqPtr X509ReqNew();
DFL_CRYPTO_EXPIMP X509ReqPtr X509ReqDup(const ::X509_REQ* req);
DFL_CRYPTO_EXPIMP X509ReqPtr
PemReadBioX509Req(::BIO* bp,
                  ::X509_REQ** x,
                  int (*cb)(char*, int, int, void*),
                  void* u);

// the following works around name clashes with windows headers,
// see:
// https://github.com/openssl/openssl/blob/master/include/openssl/ossl_typ.h#L66-L73
#ifndef _WIN32
DFL_CRYPTO_EXPIMP ::X509_NAME* X509ReqGetSubjectName(const ::X509_REQ* req);
DFL_CRYPTO_EXPIMP ::X509_NAME* X509GetSubjectName(const ::X509* x);
DFL_CRYPTO_EXPIMP ::X509_NAME* X509GetIssuerName(const ::X509* x);
DFL_CRYPTO_EXPIMP std::string X509NameOneline(const ::X509_NAME* name);
DFL_CRYPTO_EXPIMP std::string strByNid(const ::X509_NAME* name, int nid);
#else
DFL_CRYPTO_EXPIMP ::X509_name_st* X509ReqGetSubjectName(const ::X509_REQ* req);
DFL_CRYPTO_EXPIMP ::X509_name_st* X509GetSubjectName(const ::X509* x);
DFL_CRYPTO_EXPIMP ::X509_name_st* X509GetIssuerName(const ::X509* x);
DFL_CRYPTO_EXPIMP std::string X509NameOneline(const ::X509_name_st* name);
DFL_CRYPTO_EXPIMP std::string strByNid(const ::X509_name_st* name, int nid);
#endif

DFL_CRYPTO_EXPIMP BioPtr BioNullptr() noexcept;
DFL_CRYPTO_EXPIMP BioPtr BioNew();
DFL_CRYPTO_EXPIMP BnGencbPtr BnGencbNew();
DFL_CRYPTO_EXPIMP StackOfX509 StackOfX509New();
DFL_CRYPTO_EXPIMP StackOfX509Extension StackOfX509ExtensionNew();
DFL_CRYPTO_EXPIMP BioPtr BioNewMemBuf(const void* buffer, int length);
DFL_CRYPTO_EXPIMP Asn1TimePtr Asn1TimeNew();
DFL_CRYPTO_EXPIMP X509StoreCtxPtr X509StoreCtxNew();
DFL_CRYPTO_EXPIMP X509StorePtr X509StoreNew();
DFL_CRYPTO_EXPIMP X509VerifyParamPtr X509VerifyParamNew();
DFL_CRYPTO_EXPIMP EcdsaSigPtr EcdsaSigNew();
DFL_CRYPTO_EXPIMP EcdsaSigPtr EcdsaSigNullptr() noexcept;
DFL_CRYPTO_EXPIMP int EcdsaSigSet0(::ECDSA_SIG* sig, BignumPtr r, BignumPtr s);
DFL_CRYPTO_EXPIMP int I2dEcdsaSig(const ::ECDSA_SIG* sig, unsigned char** pp);
DFL_CRYPTO_EXPIMP EcdsaSigPtr D2iEcdsaSig(const unsigned char** data,
                                          size_t size);
DFL_CRYPTO_EXPIMP BignumPtr EcdsaSigGet0R(const ECDSA_SIG* sig);
DFL_CRYPTO_EXPIMP BignumPtr EcdsaSigGet0S(const ECDSA_SIG* sig);
DFL_CRYPTO_EXPIMP std::tuple<BignumPtr, BignumPtr> EcPointGetAffineCoordinates(
    const EC_GROUP* group,
    const EC_POINT* ecPoint);
DFL_CRYPTO_EXPIMP RsaPtr RsaNullptr() noexcept;
DFL_CRYPTO_EXPIMP RsaPtr RsaNew();
DFL_CRYPTO_EXPIMP RsaPtr
PemReadBioRsaPrivateKey(::BIO* bio,
                        ::RSA** rsa,
                        int (*cb)(char*, int, int, void*),
                        void* u);
DFL_CRYPTO_EXPIMP RsaPtr
PemReadBioRsaPublicKey(::BIO* bio,
                       ::RSA** rsa,
                       int (*cb)(char*, int, int, void*),
                       void* u);
DFL_CRYPTO_EXPIMP RsaPtr RsaPrivateKeyDup(const ::RSA* rsa);
DFL_CRYPTO_EXPIMP RsaPtr RsaPublicKeyDup(const ::RSA* rsa);
DFL_CRYPTO_EXPIMP EcKeyPtr EvpPkeyGet1EcKey(const ::EVP_PKEY* pkey);
DFL_CRYPTO_EXPIMP X509Ptr X509Nullptr() noexcept;
DFL_CRYPTO_EXPIMP X509Ptr X509New();
DFL_CRYPTO_EXPIMP X509Ptr X509Dup(const ::X509* x509);
DFL_CRYPTO_EXPIMP X509Ptr X509PtrFromRawPtr(::X509* x509) noexcept;
DFL_CRYPTO_EXPIMP X509NamePtr X509NameNew();
DFL_CRYPTO_EXPIMP X509Ptr PemReadBioX509(::BIO* bp,
                                         ::X509** x,
                                         int (*cb)(char*, int, int, void*),
                                         void* u);
/**
 * @brief Wrapper for \c d2i_X509().
 * @details The first parameter is omitted due to the fact that it is
 * "strongly discouraged".
 * @param in Data that should be decoded. If the call is successful *in is
 *           incremented to the byte following the parsed data.
 * @param len Number of byte that should be decoded.
 */
DFL_CRYPTO_EXPIMP X509Ptr D2iX509(const unsigned char** in, long len);

DFL_CRYPTO_EXPIMP X509Ptr SslGetPeerCertificate(const SSL* ssl);
DFL_CRYPTO_EXPIMP BignumPtr BnNullptr() noexcept;
DFL_CRYPTO_EXPIMP BignumPtr BnOwner(BIGNUM* bnPtr) noexcept;
DFL_CRYPTO_EXPIMP BignumPtr BnBin2Bn(const unsigned char* data, size_t size);
DFL_CRYPTO_EXPIMP BignumPtr BnDup(const BIGNUM* bn);
DFL_CRYPTO_EXPIMP int BnCmp(const BIGNUM* a, const BIGNUM* b);
DFL_CRYPTO_EXPIMP size_t BnNumBytes(const BIGNUM* bn);
DFL_CRYPTO_EXPIMP void BnBn2BinPad(const BIGNUM* bn,
                                   unsigned char* data,
                                   size_t size);
DFL_CRYPTO_EXPIMP CharPtr BnBn2Dec(const BIGNUM* bn);
DFL_CRYPTO_EXPIMP EvpPkeyPtr EvpPkeyNullptr() noexcept;
DFL_CRYPTO_EXPIMP EvpPkeyPtr EvpPkeyNew();
DFL_CRYPTO_EXPIMP EvpPkeyPtr
PemReadBioPrivateKey(::BIO* bp,
                     ::EVP_PKEY** x,
                     int (*cb)(char*, int, int, void*),
                     void* u);
DFL_CRYPTO_EXPIMP EvpPkeyPtr
PemReadBioPublicKey(::BIO* bp,
                    ::EVP_PKEY** x,
                    int (*cb)(char*, int, int, void*),
                    void* u);
DFL_CRYPTO_EXPIMP bool PemWriteBioPrivateKey(BIO* bp,
                                             EVP_PKEY* x,
                                             const EVP_CIPHER* enc,
                                             unsigned char* kstr,
                                             int klen,
                                             int (*cb)(char*, int, int, void*),
                                             void* u);
DFL_CRYPTO_EXPIMP bool PemWriteBioPublicKey(::BIO* bp, ::EVP_PKEY* x);
DFL_CRYPTO_EXPIMP EvpPkeyPtr D2iAutoPrivateKey(const unsigned char** in,
                                               long len);
DFL_CRYPTO_EXPIMP EvpPkeyPtr D2iPubkey(const unsigned char** in, long len);
DFL_CRYPTO_EXPIMP EvpPkeyPtr D2iPublicKey(int type,
                                          const unsigned char** in,
                                          long len);
DFL_CRYPTO_EXPIMP int EvpPkeySet1Rsa(::EVP_PKEY* pkey, ::RSA* key);
DFL_CRYPTO_EXPIMP EvpPkeyPtr X509GetPubkey(const ::X509* x509);
DFL_CRYPTO_EXPIMP EvpPkeyPtr X509ReqGetPubkey(const ::X509_REQ* req);
DFL_CRYPTO_EXPIMP EvpPkeyPtr generateRsaKey(int keySize,
                                            unsigned long exponent);
DFL_CRYPTO_EXPIMP EvpPkeyPtr generateEcKey(int nidOfNamedCurve);
DFL_CRYPTO_EXPIMP EvpPkeyPtr createEcPublicKey(const char* curve,
                                               const unsigned char* xData,
                                               size_t xSize,
                                               const unsigned char* yData,
                                               size_t ySize);
DFL_CRYPTO_EXPIMP EvpPkeyPtr createEcPublicKey(const char* curve,
                                               const BIGNUM* x,
                                               const BIGNUM* y);
DFL_CRYPTO_EXPIMP EvpPkeyPtr EvpPkeyNewRawPrivateKey(int type,
                                                     ::ENGINE* e,
                                                     const unsigned char* priv,
                                                     size_t len);
DFL_CRYPTO_EXPIMP EvpPkeyCtxPtr EvpPkeyCtxNew(EVP_PKEY* pkey);
DFL_CRYPTO_EXPIMP int EvpPkeyDeriveInit(EVP_PKEY_CTX* ctx);
DFL_CRYPTO_EXPIMP int EvpPkeyDeriveSetPeer(EVP_PKEY_CTX* ctx, EVP_PKEY* peer);
DFL_CRYPTO_EXPIMP int EvpPkeyDerive(EVP_PKEY_CTX* ctx,
                                    unsigned char* key,
                                    size_t* keylen);
DFL_CRYPTO_EXPIMP int pkcs5PbKdf2Hmac(const char* pass,
                                      int passlen,
                                      const unsigned char* salt,
                                      int saltlen,
                                      int iter,
                                      const EVP_MD* digest,
                                      int keylen,
                                      unsigned char* out);

/**
 * @brief Provide the reason OpenSSL error string only.
 * @details
 * To retrieve the complete OpenSSL error string use
 * \ref DFL::Crypto::OpenSsl::getError() instead.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::string getErrorReason();

/**
 * @brief Provide the complete OpenSSL error string.
 * @details
 * The error string format will be
 * \c error:[error code]:[library name]:[function name]:[reason string]
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP std::string getError();

DFL_CRYPTO_EXPIMP std::string convertOctetStringToHex(
    const ASN1_OCTET_STRING* octetString);
DFL_CRYPTO_EXPIMP std::string X509GetSubjectCommonName(const ::X509* cert);
DFL_CRYPTO_EXPIMP std::string X509GetAuthorityKeyId(const ::X509* cert);
DFL_CRYPTO_EXPIMP std::string X509GetSubjectKeyId(const ::X509* cert);
DFL_CRYPTO_EXPIMP bool X509GetCriticalExtCA(const ::X509* cert);

/**
 * @brief Checks if the certificate has a Basic Constraints extension marked as
 * critical.
 * @details
 * Background: Recurity Labs recommends to add the basicConstraints extension to
 * all certificates, set or clear the CA flag according to the certificate's
 * purpose, and mark the extension critical.
 *
 * According to RFC 5280 section 4.2.1.9:
 * > Conforming CAs MUST include this extension in all CA certificates that
 * > contain public keys used to validate digital signatures on certificates and
 * > MUST mark the extension as critical in such certificates.
 */
DFL_CRYPTO_EXPIMP bool hasCriticalBasicConstraintsExtension(const ::X509* cert);
DFL_CRYPTO_EXPIMP bool hasCriticalKeyUsageExtension(const ::X509* cert);

DFL_CRYPTO_EXPIMP Asn1ObjectPtr SkAsn1ObjectValue(EXTENDED_KEY_USAGE* eku,
                                                  int position);
DFL_CRYPTO_EXPIMP void X509ReqAddExtension(::X509_REQ* req,
                                           int nid,
                                           const char* value);
DFL_CRYPTO_EXPIMP DFL::Oids X509ReqGetExtendedKeyUsageOids(
    const ::X509_REQ* req);
DFL_CRYPTO_EXPIMP DFL::Oids X509GetExtendedKeyUsageOids(const ::X509* x509);
DFL_CRYPTO_EXPIMP bool hasKeyUsageDigitalSignature(const ::X509* x509);
DFL_CRYPTO_EXPIMP bool hasKeyUsageCertificateSign(const ::X509* x509);
DFL_CRYPTO_EXPIMP bool hasKeyUsageCrlSign(const ::X509* x509);
DFL_CRYPTO_EXPIMP X509ExtensionPtr X509v3ExtConfNid(X509V3_CTX* ctx,
                                                    int ext_nid,
                                                    const char* value);
DFL_CRYPTO_EXPIMP bool X509Digest(const ::X509* x509,
                                  const EVP_MD* md,
                                  unsigned char* buffer,
                                  unsigned int* len);

/**
 * @brief Provides the key length in bits.
 * @details
 * Typical values for RSA keys are 2048 and EC keys 256.
 */
DFL_CRYPTO_EXPIMP std::size_t keyLengthInBits(const ::EVP_PKEY* key);

/**
 * @brief Provides the OpenSSL version string.
 * @details
 * The text variant of the version number and the release date. For example,
 * "OpenSSL 1.1.1l  24 Aug 2021"
 */
DFL_CRYPTO_EXPIMP const char* version();

/**
 * @brief Deallocates resources associated with the current thread.
 * @details
 * Typically this function will be called automatically by the library when the
 * thread exits. This should only be called directly if resources should be
 * freed at an earlier time, or under the circumstances described in the NOTES
 * section on
 * https://www.openssl.org/docs/man1.1.1/man3/OPENSSL_thread_stop.html
 */
DFL_CRYPTO_EXPIMP void threadStop() noexcept;

/**
 * @brief Sets the version of the X509 certificate to V3.
 * @ingroup Crypto
 */
DFL_CRYPTO_EXPIMP void X509SetVerionToV3(::X509& x509Cert);
}
}
}
