#pragma once

#include <Framework/Mdib/Public/Model/LocalizedText.h>
#include <Framework/Utils/Public/LanguageTagSerialize.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>
#include <Framework/Mdib/Public/Model/VersionCounterSerialize.h>
#include <vector>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::LocalizedText)

BOOST_CLASS_VERSION(::DFL::Mdib::LocalizedText, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::LocalizedText, boost::serialization::track_never)

namespace boost
{
namespace serialization
{
template<class Archive>
inline void save_construct_data(Archive & ar, const ::DFL::Mdib::LocalizedText* lt, const unsigned int /*version*/)
{
    const std::string& text(lt->text());
    ar & make_nvp("Text", text);

    const boost::optional<DFL::Locale::LanguageTag>& lang(lt->languageTag());
    ar & make_nvp("Lang", lang);

    const std::string& ref(lt->reference().get());
    ar & make_nvp("Ref", ref);

    const boost::optional<DFL::Mdib::VersionCounter>& version(lt->version());
    ar & make_nvp("Version", version);

    const boost::optional<DFL::Mdib::LocalizedTextWidth>& textWidth(lt->textWidth());
    ar & make_nvp("TextWidth", textWidth);

}

template<class Archive>
void save(Archive & /*ar*/, const ::DFL::Mdib::LocalizedText& /*lt*/, const unsigned int /*version*/)
{
}

template<class Archive>
inline void load_construct_data(Archive & ar, ::DFL::Mdib::LocalizedText* out, const unsigned int /*version*/)
{
    // retrieve data from archive required to construct new instance
    std::string text;
    ar & make_nvp("Text", text);

    boost::optional<DFL::Locale::LanguageTag> languageTag;
    ar & make_nvp("Lang", languageTag);

    std::string ref;
    ar & make_nvp("Ref", ref);

    boost::optional<DFL::Mdib::VersionCounter> refVersion;
    ar & make_nvp("Version", refVersion);

    boost::optional<DFL::Mdib::LocalizedTextWidth> textWidth;
    ar & make_nvp("TextWidth", textWidth);

    // invoke inplace constructor to initialize instance of my_class
    ::new (out) ::DFL::Mdib::LocalizedText(DFL::Locale::Utf8(text),
                                           languageTag,
                                           ::DFL::Mdib::LocalizedTextRef(DFL::Locale::Utf8(ref)),
                                           refVersion,
                                           textWidth);
}

template<class Archive>
void load(Archive & /*ar*/, ::DFL::Mdib::LocalizedText& /*out*/, const unsigned int /*version*/)
{
}
}
}
