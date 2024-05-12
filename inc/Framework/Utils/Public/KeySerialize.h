#pragma once

#include <Framework/Utils/Public/Key.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Component::Key)

BOOST_CLASS_VERSION(::DFL::Component::Key, 0)

namespace boost
{
namespace serialization
{
template<class Archive>
void save(Archive & ar, const ::DFL::Component::Key& k, const unsigned int /*version*/)
{
    const ::DFL::Component::Key::KindNativeType kindValue(k.kindValue());
    ar & make_nvp("KindValue", kindValue);

    const std::string kindName(k.kindName());
    ar & make_nvp("KindName", kindName);

    const ::DFL::Component::Key::InstanceNativeType instanceValue(k.instanceValue());
    ar & make_nvp("InstanceValue", instanceValue);
}

template<class Archive>
void load(Archive & ar, ::DFL::Component::Key& k, const unsigned int /*version*/)
{
    ::DFL::Component::Key::KindNativeType kindValue{};
    ar & make_nvp("KindValue", kindValue);

    std::string kindName{};
    ar & make_nvp("KindName", kindName);

    ::DFL::Component::Key::InstanceNativeType instanceValue{};
    ar & make_nvp("InstanceValue", instanceValue);

    k = ::DFL::Component::Key(
        ::DFL::Component::Kind(kindValue, kindName.c_str()),
        ::DFL::Component::Instance(instanceValue));
}
}
}
