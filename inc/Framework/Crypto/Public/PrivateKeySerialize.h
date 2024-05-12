#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/PrivateKey.h>
#include <Framework/Crypto/Public/Convert.h>

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Crypto::PrivateKey)

BOOST_CLASS_VERSION(::DFL::Crypto::PrivateKey, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Saves given private key in given archive.
 *
 * @ingroup Crypto
 */
template <class Archive>
void save(Archive& ar, const ::DFL::Crypto::PrivateKey& privateKey, const unsigned int /*version*/)
{
    const ::DFL::Crypto::PemString pem(::DFL::Crypto::Convert::toPem(privateKey));
    ar << make_nvp("Pem", pem);
}
/**
 * @brief Loads given private key from given archive.
 *
 * @ingroup Crypto
 */
template <class Archive>
void load(Archive& ar, ::DFL::Crypto::PrivateKey& privateKey, const unsigned int /*version*/)
{
    ::DFL::Crypto::PemString pem;
    ar & make_nvp("Pem", pem);

    privateKey = ::DFL::Crypto::PrivateKey(pem);
}
}
}
