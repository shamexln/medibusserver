#pragma once

#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Utils/Public/QNameSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/AttributeSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/NodeSerialize.h>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <Framework/Utils/Public/QName.h>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::ExtensionType)

BOOST_CLASS_VERSION(::DFL::Mdib::ExtensionType, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::ExtensionType, boost::serialization::track_never)

DFL_ENUM_CLASS_SERIALIZATION(::DFL::Mdib::MustUnderstand, ((False,0))((True,1)))

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::ExtensionType* /*in*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::ExtensionType& in, const unsigned int /*version*/)
{
    const auto mustUnderstand = in.mustUnderstand() ? ::DFL::Mdib::MustUnderstand::True : ::DFL::Mdib::MustUnderstand::False;
    ar & make_nvp("MustUnderstand", mustUnderstand);

    ar & make_nvp("NodeTree", in.nodeTree());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::ExtensionType* out, const unsigned int /*version*/)
{
    // initialized a dummy extension
    ::new (out) ::DFL::Mdib::ExtensionType(::DFL::QName(), ::DFL::Mdib::MustUnderstand::False);
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::ExtensionType& out, const unsigned int version)
{
    if (version > 0)
    {
        ::DFL::Mdib::MustUnderstand mustUnderstand{};
        ar & make_nvp("MustUnderstand", mustUnderstand);

        ::DFL::Mdib::Dom::Nodes nodeTree;
        ar & make_nvp("NodeTree", nodeTree);

        out = ::DFL::Mdib::ExtensionType(std::move(nodeTree), mustUnderstand);
    }
    else
    {
        ::DFL::QName name;
        ar & make_nvp("QName", name);

        ::DFL::Mdib::MustUnderstand mustUnderstand{};
        ar & make_nvp("MustUnderstand", mustUnderstand);

        out = ::DFL::Mdib::ExtensionType(std::move(name), mustUnderstand);
    }
}

} /* namespace serialization */
} /* namespace boost */
