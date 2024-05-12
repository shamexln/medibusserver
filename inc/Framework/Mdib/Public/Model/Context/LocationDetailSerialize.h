#pragma once

#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>
#include <Framework/Mdib/Public/Model/ExtensionTypeSerialize.h>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>

BOOST_SERIALIZATION_SPLIT_FREE(::DFL::Mdib::LocationDetail)

BOOST_CLASS_VERSION(::DFL::Mdib::LocationDetail, 1)

namespace boost
{
namespace serialization
{
template<class Archive>
void save(Archive & ar, const ::DFL::Mdib::LocationDetail& ld, const unsigned int /*version*/)
{
    const std::string facility(ld.facility());
    ar & make_nvp("Facility", facility);
    const std::string building(ld.building());
    ar & make_nvp("Building", building);
    const std::string floor(ld.floor());
    ar & make_nvp("Floor", floor);
    const std::string pointOfCare(ld.pointOfCare());
    ar & make_nvp("PoC", pointOfCare);
    const std::string room(ld.room());
    ar & make_nvp("Room", room);
    const std::string bed(ld.bed());
    ar & make_nvp("Bed", bed);
    ar & make_nvp("Extensions", ld.extensions());
}

template<class Archive>
void load(Archive & ar, ::DFL::Mdib::LocationDetail& ld, const unsigned int version)
{
    std::string facility;
    ar & make_nvp("Facility", facility);
    std::string building;
    ar & make_nvp("Building", building);
    std::string floor;
    ar & make_nvp("Floor", floor);
    std::string pointOfCare;
    ar & make_nvp("PoC", pointOfCare);
    std::string room;
    ar & make_nvp("Room", room);
    std::string bed;
    ar & make_nvp("Bed", bed);

    DFL::Mdib::ExtensionTypes extensions;
    if (version > 0)
    {
        ar & make_nvp("Extensions", extensions);
    }

    ld = DFL::Mdib::LocationDetail(DFL::Mdib::Facility(DFL::Locale::Utf8(facility)),
                                   DFL::Mdib::Building(DFL::Locale::Utf8(building)),
                                   DFL::Mdib::Floor(DFL::Locale::Utf8(floor)),
                                   DFL::Mdib::PointOfCare(DFL::Locale::Utf8(pointOfCare)),
                                   DFL::Mdib::Room(DFL::Locale::Utf8(room)),
                                   DFL::Mdib::Bed(DFL::Locale::Utf8(bed)),
                                   std::move(extensions));
}
}
}
