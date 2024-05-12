#pragma once

#include <S31/Nomenclature/Test/Public/CertHelper.h>
#include <S31/Sdc/Private/Common/Http/ConnectionPolicy.h>
#include <S31/Sdc/Private/Common/Http/SslHandshakeBroker.h>

#include <boost/asio/ssl/context.hpp>

#include <gtest/gtest.h>

namespace S31::Sdc::Impl::Test
{
inline boost::asio::ssl::context fakeSslServerContext()
{
    static auto privateKey = S31::Utils::Test::CertHelper::generatePrivateKey("MockServer");
    static auto chain = S31::Utils::Test::CertHelper::leafCertWithAllRolesNoCache("MockServer", privateKey);

    const auto privateKeyPem = DFL::Crypto::Convert::toPem(privateKey);
    const auto chainPem = DFL::Crypto::Convert::toPem(chain);

    auto ctx = boost::asio::ssl::context(boost::asio::ssl::context::tls_server);
    ctx.use_private_key(boost::asio::buffer(privateKeyPem.str()), boost::asio::ssl::context::pem);
    ctx.use_certificate_chain(boost::asio::buffer(chainPem.str()));
    return ctx;
}

inline boost::asio::ssl::context fakeSslClientContext()
{
    auto ctx = boost::asio::ssl::context(boost::asio::ssl::context::tls_client);
    ctx.set_verify_mode(boost::asio::ssl::context::verify_none);

    auto rootCAs = S31::Utils::Test::CertHelper::rootCasWithTestRoots();
    for (const auto& certificate : rootCAs)
    {
        const auto certificatePem = DFL::Crypto::Convert::toPem(certificate);
        ctx.add_certificate_authority(boost::asio::buffer(certificatePem.str()));
    }
    return ctx;
}

class MockHandshakeBroker : public S31::Sdc::Impl::SslHandshakeBroker
{
public:
    MockHandshakeBroker(boost::asio::ssl::stream_base::handshake_type expected)
        : m_expectedHandshakeType{expected}
    {
    }

    void
    add(boost::beast::ssl_stream<boost::asio::ip::tcp::socket>& stream,
        boost::asio::ssl::stream_base::handshake_type           type,
        std::chrono::seconds /* timeout */,
        std::function<void(boost::system::error_code)> completion) override
    {
        EXPECT_EQ(m_expectedHandshakeType, type);
        ++m_callCount;
        stream.async_handshake(type, std::move(completion));
    }

    int callCount() const
    {
        return m_callCount;
    }

    void resetCallCount()
    {
        m_callCount = 0;
    }

private:
    boost::asio::ssl::stream_base::handshake_type m_expectedHandshakeType;
    int                                           m_callCount{0};
};

class MockConnectionPolicy : public S31::Sdc::Impl::ConnectionPolicy
{
public:
    DFL::Crypto::RootCas provideRootCas() const override { return {}; }
    std::optional<DFL::Crypto::PrivateKey> providePrivateKey() const override { return {}; }
    DFL::Crypto::CertificateChain provideCertificateChain() const override { return {}; }
    S31::Nomenclature::WhiteListingState whitelistCheck(const std::string&) const override { return {}; }
    S31::Nomenclature::ProvideRoleAuthorizationListFunction provideRoleAuthorizationListFunction() const override { return {}; }
    std::optional<S31::Utils::Error> verifyPeerCredentials(const S31::Nomenclature::Credentials&) const override { return {}; }
    S31::Sdc::Impl::QualityOfService qualityOfService() const override { return {}; }
    int compressionLevel() const override { return 0; }
    DFL::Chrono::Seconds idleTimeout() const override { return DFL::Chrono::Seconds{1}; }
    std::chrono::seconds connectionTimeout() const override { return std::chrono::seconds{1}; }
    std::chrono::seconds requestTimeout() const override { return std::chrono::seconds{1}; }
    std::size_t maxReceiveSize() const override { return 4096; }
};

}