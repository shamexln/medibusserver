#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Whitelist.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

#include <string>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Crypto::Whitelist)

BOOST_CLASS_VERSION(::DFL::Crypto::Whitelist, 0)

namespace boost
{
namespace serialization
{
/**
 * @brief Saves given list in given archive.
 *
 * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp serialize
 *
 * @ingroup Crypto
 */
template <class Archive>
void save(Archive& ar, const ::DFL::Crypto::Whitelist& list, const unsigned int /*version*/)
{
    ar << make_nvp("String", list.str());
}
/**
 * @brief Loads given list from given archive.
 *
 * @snippet Crypto/Test/UnitTest/TestWhitelist.cpp serialize
 *
 * @ingroup Crypto
 */
template <class Archive>
void load(Archive& ar, ::DFL::Crypto::Whitelist& list, const unsigned int /*version*/)
{
    std::string data;

    ar & make_nvp("String", data);

    list.str(data);
}
}
}
