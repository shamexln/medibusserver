#pragma once

#include <Framework/Mdib/Public/Model/ExtensionDom/Node.h>
#include <Framework/Mdib/Public/Model/ExtensionDom/ElementSerialize.h>
#include <Framework/Utils/Public/Utf8Serialize.h>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::Dom::Node)

BOOST_CLASS_VERSION(::DFL::Mdib::Dom::Node, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::Dom::Node, boost::serialization::track_never)

DFL_ENUM_CLASS_SERIALIZATION(::DFL::Mdib::Dom::Node::ContentType, ((Element,0))((Text,1)))

namespace boost
{
namespace serialization
{

template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::Dom::Node* /*in*/, const unsigned int /*version*/)
{

}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::Dom::Node& in, const unsigned int /*version*/)
{
    auto depth = in.depth().get();
    ar & make_nvp("Depth", depth);

    auto nodeType = in.contentType();
    ar & make_nvp("ContentType", nodeType);

    switch (nodeType)
    {
        case ::DFL::Mdib::Dom::Node::ContentType::Element:
            ar & make_nvp("Element", in.element());
            break;
        case ::DFL::Mdib::Dom::Node::ContentType::Text:
            ar & make_nvp("Text", in.text());
            break;
        default:
            break;
    }
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::Dom::Node* out, const unsigned int /*version*/)
{
    ::new (out) ::DFL::Mdib::Dom::Node(::DFL::Mdib::Dom::NodeDepth(0), ::DFL::Locale::Utf8());
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::Dom::Node& out, const unsigned int /*version*/)
{
    ::DFL::Mdib::Dom::NodeDepth depth(0);
    ar & make_nvp("Depth", depth.get());

    ::DFL::Mdib::Dom::Node::ContentType nodeType{};
    ar & make_nvp("ContentType", nodeType);

    switch (nodeType)
    {
        case ::DFL::Mdib::Dom::Node::ContentType::Element:
            {
                ::DFL::Mdib::Dom::Element element{::DFL::QName() };
                ar & make_nvp("Element", element);
                out = ::DFL::Mdib::Dom::Node(depth, std::move(element));
            }
            break;

        case ::DFL::Mdib::Dom::Node::ContentType::Text:
            {
                ::DFL::Locale::Utf8 text;
                ar & make_nvp("Text", text);
                out = ::DFL::Mdib::Dom::Node(depth, std::move(text));
            }
            break;

        default:
            break;
    }
}

}
}
