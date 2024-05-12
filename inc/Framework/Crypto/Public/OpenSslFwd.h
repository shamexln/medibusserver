#pragma once

struct BASIC_CONSTRAINTS_st;
struct ECDSA_SIG_st;
struct X509_VERIFY_PARAM_st;
struct X509_crl_st;
struct X509_extension_st;
struct X509_name_st;
struct X509_req_st;
struct asn1_object_st;
struct asn1_string_st;
struct bignum;
struct bio_st;
struct ec_group_st;
struct ec_key_st;
struct ec_point_st;
struct engine_st;
struct evp_cipher_ctx_st;
struct evp_cipher_st;
struct evp_md_ctx_st;
struct evp_md_st;
struct evp_pkey_st;
struct rand_meth_st;
struct rsa_st;
struct ssl_st;
struct stack_st_ASN1_OBJECT;
struct stack_st_X509;
struct stack_st_X509_EXTENSION;
struct v3_ext_ctx;
struct x509_st;
struct x509_store_ctx_st;
struct x509_store_st;

// the following names cause name clashes with windows headers,
// thus they are not defined in OpenSSL:
// https://github.com/openssl/openssl/blob/master/include/openssl/ossl_typ.h#L66-L73
// therefore for Win32 this definition is omitted
#ifndef _WIN32
using X509_EXTENSION = struct X509_extension_st;
using X509_NAME = struct X509_name_st;
#endif

using ASN1_BIT_STRING = struct asn1_string_st;
using ASN1_OBJECT = struct asn1_object_st;
using ASN1_OCTET_STRING = struct asn1_string_st;
using ASN1_TIME = struct asn1_string_st;
using AUTHORITY_KEYID = struct AUTHORITY_KEYID_st;
using BASIC_CONSTRAINTS = struct BASIC_CONSTRAINTS_st;
using BIGNUM = struct bignum_st;
using BIO = struct bio_st;
using BN_GENCB = struct bn_gencb_st;
using ECDSA_SIG = struct ECDSA_SIG_st;
using EC_GROUP = struct ec_group_st;
using EC_KEY = struct ec_key_st;
using EC_POINT = struct ec_point_st;
using ENGINE = struct engine_st;
using EVP_CIPHER = struct evp_cipher_st;
using EVP_CIPHER_CTX = struct evp_cipher_ctx_st;
using EVP_MD = struct evp_md_st;
using EVP_MD_CTX = struct evp_md_ctx_st;
using EVP_PKEY = struct evp_pkey_st;
using EVP_PKEY_CTX = struct evp_pkey_ctx_st;
using EXTENDED_KEY_USAGE = struct stack_st_ASN1_OBJECT;
using RSA = struct rsa_st;
using SSL = struct ssl_st;
using X509 = struct x509_st;
using X509V3_CTX = struct v3_ext_ctx;
using X509_CRL = struct X509_crl_st;
using X509_REQ = struct X509_req_st;
using X509_STORE = struct x509_store_st;
using X509_STORE_CTX = struct x509_store_ctx_st;
using X509_VERIFY_PARAM = struct X509_VERIFY_PARAM_st;

extern "C" void ASN1_BIT_STRING_free(ASN1_BIT_STRING*);
extern "C" void ASN1_OBJECT_free(ASN1_OBJECT*);
extern "C" void ASN1_OCTET_STRING_free(ASN1_OCTET_STRING*);
extern "C" void ASN1_TIME_free(ASN1_TIME*);
extern "C" void AUTHORITY_KEYID_free(AUTHORITY_KEYID*);
extern "C" void BASIC_CONSTRAINTS_free(BASIC_CONSTRAINTS*);
extern "C" void BIO_free_all(BIO*);
extern "C" void BN_GENCB_free(BN_GENCB*);
extern "C" void BN_free(BIGNUM*);
extern "C" void ECDSA_SIG_free(ECDSA_SIG*);
extern "C" void EC_KEY_free(EC_KEY*);
extern "C" void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX*);
extern "C" void EVP_MD_CTX_free(EVP_MD_CTX*);
extern "C" void EVP_PKEY_CTX_free(EVP_PKEY_CTX*);
extern "C" void EVP_PKEY_free(EVP_PKEY*);
extern "C" void EXTENDED_KEY_USAGE_free(EXTENDED_KEY_USAGE*);
extern "C" void RSA_free(RSA*);
extern "C" void X509_EXTENSION_free(struct X509_extension_st*);
extern "C" void X509_NAME_free(struct X509_name_st*);
extern "C" void X509_REQ_free(X509_REQ*);
extern "C" void X509_STORE_CTX_free(X509_STORE_CTX*);
extern "C" void X509_STORE_free(X509_STORE*);
extern "C" void X509_VERIFY_PARAM_free(X509_VERIFY_PARAM*);
extern "C" void X509_free(X509*);
