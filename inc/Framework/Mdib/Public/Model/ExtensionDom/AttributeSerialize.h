#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Attribute.h>
#include <Framework/Utils/Public/QNameSerialize.h>
#include <Framework/Utils/Public/Utf8Serialize.h>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Dom::Attribute)

BOOST_CLASS_VERSION(::DFL::Mdib::Dom::Attribute, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Dom::Attribute, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::Dom::Attribute* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::Dom::Attribute& in, const unsigned int /*version*/)
{
    ar & make_nvp("QName", in.name());
    ar & make_nvp("Value", in.value());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::Dom::Attribute* out, const unsigned int /*version*/)
{
    ::new (out) ::DFL::Mdib::Dom::Attribute(::DFL::QName(), ::DFL::Locale::Utf8());
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::Dom::Attribute& out, const unsigned int /*version*/)
{
    ::DFL::QName name;
    ar & make_nvp("QName", name);

    ::DFL::Locale::Utf8 value;
    ar & make_nvp("Value", value);

    out = ::DFL::Mdib::Dom::Attribute(std::move(name), std::move(value));
}

} /* namespace serialization */
} /* namespace boost */
