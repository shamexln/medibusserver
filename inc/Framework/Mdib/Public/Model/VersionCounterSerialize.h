#pragma once

#include <Framework/Mdib/Public/Model/VersionCounter.h>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/optional.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(DFL::Mdib::VersionCounter)

BOOST_CLASS_VERSION(DFL::Mdib::VersionCounter, 0)

BOOST_CLASS_TRACKING(::DFL::Mdib::VersionCounter, boost::serialization::track_never)

namespace boost
{
    namespace serialization
    {
        template <class Archive>
        void save(Archive& ar, const DFL::Mdib::VersionCounter& version, const unsigned int /*version*/)
        {
            const uint64_t ver = version.get();
            ar << make_nvp("VersionCounter", ver);
        }

        template <class Archive>
        void load(Archive& ar, DFL::Mdib::VersionCounter& version, const unsigned int /*version*/)
        {
            uint64_t ver = 0;
            ar >> make_nvp("VersionCounter", ver);
            version = DFL::Mdib::VersionCounter(ver);
        }
    }
}
