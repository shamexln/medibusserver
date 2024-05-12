#pragma once

#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/RootCas.h>
#include <S31/S31CoreExImp.h>

#include <boost/asio/ssl/context.hpp>

namespace S31::Sdc::Impl
{

/**
 * @brief Factory for Boost.Asio SSL context with DFL.Crypto input.
 * @details The required data in DFL.Crypto format is typically available
 * from the DFL crypto store.
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP BoostAsioSslContextFactory
{
    public:
        static boost::asio::ssl::context create(
                boost::asio::ssl::context_base::method method,
                const DFL::Crypto::PrivateKey& privateKey,
                const DFL::Crypto::CertificateChain& certificateChain,
                const DFL::Crypto::RootCas& rootCAs);
};

}
