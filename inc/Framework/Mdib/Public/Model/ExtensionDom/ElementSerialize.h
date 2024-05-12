#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Element.h>
#include <Framework/Utils/Public/QNameSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/AttributeSerialize.h>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Dom::Element)

BOOST_CLASS_VERSION(::DFL::Mdib::Dom::Element, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Dom::Element, boost::serialization::track_never)

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::Dom::Element* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::Dom::Element& in, const unsigned int /*version*/)
{
    ar & make_nvp("QName", in.name());
    ar & make_nvp("Attributes", in.attributes());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::Dom::Element* out, const unsigned int /*version*/)
{
    ::new (out) ::DFL::Mdib::Dom::Element(::DFL::QName());
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::Dom::Element& out, const unsigned int /*version*/)
{
    ::DFL::QName name;
    ar & make_nvp("QName", name);

    ::DFL::Mdib::Dom::Attributes attributes;
    ar & make_nvp("Attributes", attributes);

    out = ::DFL::Mdib::Dom::Element(std::move(name), std::move(attributes));
}

} /* namespace serialization */
} /* namespace boost */
