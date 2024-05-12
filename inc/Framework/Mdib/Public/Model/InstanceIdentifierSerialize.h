#pragma once

#include <Framework/Mdib/Public/Model/CodedValueSerialize.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/LocalizedTextSerialize.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::InstanceIdentifier)

BOOST_CLASS_VERSION(::DFL::Mdib::InstanceIdentifier, 1)

BOOST_CLASS_TRACKING(::DFL::Mdib::InstanceIdentifier, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
template<class Archive>
inline void save_construct_data(Archive & /*ar*/, const ::DFL::Mdib::InstanceIdentifier* /*ii*/, const unsigned int /*version*/)
{
}

template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::InstanceIdentifier& ii, const unsigned int /*version*/)
{
    const std::string& root(ii.root().get().get());
    ar & make_nvp("Root", root);
    const std::string& extension(ii.extension().get());
    ar & make_nvp("Extension", extension);
    const DFL::Mdib::LocalizedTexts& identifierNames(ii.identifierNames());
    ar & make_nvp("Name", identifierNames);

    // Boost serialization has a problem with boost::optional
    // convert boost::optional<T> in std::vector<T>
    const boost::optional<::DFL::Mdib::CodedValue>& type(ii.type());
    const DFL::Mdib::CodedValue dummy(DFL::Mdib::CodingSystem(DFL::Mdib::CodingSystemId(DFL::Mdib::Uri("dummy system"))), DFL::Mdib::CodeId(DFL::Locale::Utf8("dummy code")));
    const std::vector<::DFL::Mdib::CodedValue> typeV(type ? 1u : 0u, type ? *type : dummy);
    ar & make_nvp("Type", typeV);

    ar & make_nvp("Extensions", ii.extensions());
}

template<class Archive>
inline void load_construct_data(Archive & /*ar*/, ::DFL::Mdib::InstanceIdentifier* ii, const unsigned int /*version*/)
{
    // invoke inplace constructor with dummy data
    ::new(ii)::DFL::Mdib::InstanceIdentifier(DFL::Mdib::Root(DFL::Mdib::Uri("dummy")), DFL::Mdib::Extension(DFL::Locale::Utf8("dummy")));
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::InstanceIdentifier& ii, const unsigned int version)
{
    std::string root;
    ar & make_nvp("Root", root);
    std::string extension;
    ar & make_nvp("Extension", extension);

    DFL::Mdib::LocalizedTexts identifierNames;
    ar & make_nvp("Name", identifierNames);

    std::vector<::DFL::Mdib::CodedValue> type;
    ar & make_nvp("Type", type);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    boost::optional<DFL::Mdib::CodedValue> identifierType;
    if (!type.empty())
    {
        identifierType = type.front();
    }

    ii = ::DFL::Mdib::InstanceIdentifier(DFL::Mdib::Root(DFL::Mdib::Uri(DFL::Locale::Utf8(root))),
                                         DFL::Mdib::Extension(DFL::Locale::Utf8(extension)),
                                         identifierType,
                                         std::move(extensions));

    for (const auto& identifierName : identifierNames)
    {
        ii.addIdentifierName(identifierName);
    }
}
}
}
