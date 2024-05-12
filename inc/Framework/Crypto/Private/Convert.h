#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/AttributeTypeAndValue.h>
#include <Framework/Crypto/Public/OpenSslFwd.h>

#include <Framework/Encoding/Public/Bytes.h>

#include <cstddef>
#include <vector>

namespace DFL
{
namespace Crypto
{
class Certificate;
class DistinguishedName;
class PemString;

namespace Impl
{
namespace Convert
{
using Attributes = std::vector<AttributeTypeAndValue>;

DFL_CRYPTO_EXPIMP Attributes attributes(const DistinguishedName& dn);
DFL_CRYPTO_EXPIMP DistinguishedName
toDistinguishedName(const X509_name_st* name);
DFL_CRYPTO_EXPIMP void toX509Name(const AttributeTypeAndValue& attr,
                                  X509_name_st* name);
DFL_CRYPTO_EXPIMP void toX509Name(const Attributes& attrs, X509_name_st* name);
DFL_CRYPTO_EXPIMP std::vector<Certificate> toCertificates(const PemString& pem);
DFL_CRYPTO_EXPIMP PemString toPrivateKeyPemPkcs8(const ::EVP_PKEY* pkey);
DFL_CRYPTO_EXPIMP PemString toPublicKeyPemPkcs8(const ::EVP_PKEY* pkey);
DFL_CRYPTO_EXPIMP Encoding::Bytes toBytes(const BIGNUM* bn);
DFL_CRYPTO_EXPIMP Encoding::Bytes toBytesWithPad(const BIGNUM* bn,
                                                 std::size_t s);
}
}
}
}
