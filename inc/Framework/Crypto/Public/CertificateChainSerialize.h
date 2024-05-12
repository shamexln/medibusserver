#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/CertificateChain.h>
#include <Framework/Crypto/Public/Convert.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Crypto::CertificateChain)

BOOST_CLASS_VERSION(::DFL::Crypto::CertificateChain, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Saves given chain in given archive.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp serialize
 * @ingroup Crypto
 */
template <class Archive>
void save(Archive& ar, const ::DFL::Crypto::CertificateChain& chain, const unsigned int /*version*/)
{
    const ::DFL::Crypto::PemString pem(::DFL::Crypto::Convert::toPem(chain));

    ar << make_nvp("Pem", pem);
}
/**
 * @brief Loads given chain from given archive.
 *
 * @snippet Crypto/Test/UnitTest/TestCertificateChain.cpp serialize
 * @ingroup Crypto
 */
template <class Archive>
void load(Archive& ar, ::DFL::Crypto::CertificateChain& chain, const unsigned int /*version*/)
{
    ::DFL::Crypto::PemString pem;

    ar & make_nvp("Pem", pem);

    chain = ::DFL::Crypto::CertificateChain(pem);
}
}
}
