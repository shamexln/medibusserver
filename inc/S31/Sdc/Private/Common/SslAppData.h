#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Crypto/Public/OpenSslFwd.h>

namespace S31::Sdc::Impl::SslAppData
{
/**
 * @brief Augment ssl context with pointer to soap context
 * @details openSSL allows for augmenting the ssl context with additional user data.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP void registerSoapContext(SSL* ssl, struct soap* soap);

/**
 * @brief Retrieve ssl context from certificate store
 * @details During verification, only the certificate store is available. However, from this the corresponding ssl context can be retrieved.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP SSL* retrieveSslContext(X509_STORE_CTX* store);
/**
 * @brief Retrieve soap context from ssl context
 * @return pointer to soap context
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP struct soap* retrieveSoapContext(SSL* ssl);

}
