#pragma once

#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>
#include <Framework/Utils/Public/QName.h>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::QName)

BOOST_CLASS_VERSION(::DFL::QName, 0)

BOOST_CLASS_TRACKING(::DFL::QName, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
void save(Archive & ar, const ::DFL::QName& in, const unsigned int /*version*/)
{
    const std::pair<std::string, std::string> namespacePrefixPair = [&] {
        if (!in.namespaceUri().get().empty())
        {
            return std::make_pair(in.namespaceUri().get(), in.prefix().get());
        }
        return std::make_pair(std::string{}, std::string{});
    }();

    ar & make_nvp("Namespace", namespacePrefixPair.first);
    ar & make_nvp("Prefix", namespacePrefixPair.second);
    ar & make_nvp("LocalName", in.localName());
}

template<class Archive>
void load(Archive & ar, ::DFL::QName& out, const unsigned int /*version*/)
{
    ::DFL::NamespaceUri ns{std::string()};
    ar & make_nvp("Namespace", ns.get());
    ::DFL::NamePrefix prefix{std::string()};
    ar & make_nvp("Prefix", prefix.get());
    std::string localName;
    ar & make_nvp("LocalName", localName);

    out = ::DFL::QName(
            std::move(ns),
            std::move(prefix),
            std::move(localName)
            );
}

} /* namespace serialization */
} /* namespace boost */
