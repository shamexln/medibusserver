#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Mdib/Private/HasExtensions.h>

#include <utility>

namespace DFL {
namespace Mdib {

/**
 * @brief Type safe container for \ref LocationDetail constructor.
 * @details The facility is also known as the hospital name.
 * @ingroup Mdib
 */
class Facility
{
    public:
        /**
         * @param facility Facility name
         */
        explicit Facility(Locale::Utf8 facility) :
                m_facility(std::move(facility))
        {
        }

        /**
         * returns facility name
         */
        operator std::string() const
        {
            return m_facility;
        }

        /**
         * returns facility name
         */
        operator Locale::Utf8() const
        {
            return m_facility;
        }
    private:
        Locale::Utf8 m_facility;
};

/**
 * @brief Type safe container for \ref LocationDetail constructor.
 * @ingroup Mdib
 */
class Building
{
    public:
        /**
         * @param building building name
         */
        explicit Building(Locale::Utf8 building) :
                m_building(std::move(building))
        {
        }
        /**
         * returns the building name
         */
        operator std::string() const
        {
            return m_building;
        }
        /**
         * returns the building name
         */
        operator Locale::Utf8() const
        {
            return m_building;
        }
    private:
        Locale::Utf8 m_building;
};

/**
 * @brief Type safe container for \ref LocationDetail constructor.
 * @ingroup Mdib
 */
class Floor
{
    public:
        /**
         * @param floorName name of the floor
         */
        explicit Floor(Locale::Utf8 floorName) :
                m_floor(std::move(floorName))
        {
        }
        /**
         * returns the floor name
         */
        operator std::string() const
        {
            return m_floor;
        }
        /**
         * returns the floor name
         */
        operator Locale::Utf8() const
        {
            return m_floor;
        }
    private:
        Locale::Utf8 m_floor;
};

/**
 * @brief Type safe container for \ref LocationDetail constructor.
 * @details A point of care (PoC) is also known as a care unit (CU).
 * @ingroup Mdib
 */
class PointOfCare
{
    public:
        /**
         * @param pointOfCare name of the point of care (also known as care unit)
         */
        explicit PointOfCare(Locale::Utf8 pointOfCare) :
                m_pointOfCare(std::move(pointOfCare))
        {
        }
        /**
         * returns the point of care name
         */
        operator std::string() const
        {
            return m_pointOfCare;
        }
        /**
         * returns the point of care name
         */
        operator Locale::Utf8() const
        {
            return m_pointOfCare;
        }
    private:
        Locale::Utf8 m_pointOfCare;
};

/**
 * @brief Type safe container for \ref LocationDetail constructor.
 * @ingroup Mdib
 */
class Room
{
    public:
        /**
         * @param room room name
         */
        explicit Room(Locale::Utf8 room) :
                m_room(std::move(room))
        {
        }

        /**
         * returns the room name
         */
        operator std::string() const
        {
            return m_room;
        }
        /**
         * returns the room name
         */
        operator Locale::Utf8() const
        {
            return m_room;
        }
    private:
        Locale::Utf8 m_room;
};

/**
 * @brief Type safe container for \ref LocationDetail constructor.
 * @ingroup Mdib
 */
class Bed
{
    public:
        /**
         * @param bed bed name
         */
        explicit Bed(Locale::Utf8 bed) :
                m_bed(std::move(bed))
        {
        }

        /**
         * returns the bed name
         */
        operator std::string() const
        {
            return m_bed;
        }
        /**
         * returns the bed name
         */
        operator Locale::Utf8() const
        {
            return m_bed;
        }
    private:
        Locale::Utf8 m_bed;
};

/**
 * @brief Contains detailed information about a location in contrast to identifiers for identification purposes.
 *
 * @details The definition of this class is derived from the HL7 standard for patient locations.
 * It contains the six fields to specify the location of the patient within the hospital (facility).
 *
 * They are listed in <a href="http://www.ihe.net/uploadedFiles/Documents/PCD/IHE_PCD_TF_Vol2.pdf">IHE PCD TF volume 2</a> Appendix C7.
 * From the 6-tuple within Dr&auml;ger only \ref Facility (hospital), \ref PointOfCare (care unit), and \ref Bed are typically used.
 * All fields are encoded in UTF-8 for unicode support.
 *
 * @ingroup Mdib
 */
class LocationDetail: public Impl::HasExtensions
{
public:

    /**
     * @brief Empty instance.
     *
     * All member strings are empty.
     */
    LocationDetail() = default;

    /**
     * Constructor with bed information only.
     * @param bed The bed name.
     */
    explicit LocationDetail(const Bed& bed);

    /**
     * Constructor with facility (hospital) information only.
     * @param facility The facility (hospital) name.
     */
    explicit LocationDetail(const Facility& facility);

    /**
     * Constructor for currently mandatory Dr&auml;ger fields.
     * @param facility The facility (hospital) name.
     * @param poc The point of care (care unit) name.
     * @param bed The bed name.
     */
    LocationDetail(const Facility& facility, const PointOfCare& poc, const Bed& bed);


    /**
     * Constructor for all fields.
     * @param facility The facility (hospital) name.
     * @param building The building name.
     * @param floor The floor name.
     * @param poc The point of care (care unit) name.
     * @param room The room name.
     * @param bed The bed name.
     * @param extensions \ref DFL::Mdib::ExtensionType "Extensions" of any kind
     */
    LocationDetail(const Facility& facility, const Building& building, const Floor& floor,
                   const PointOfCare& poc, const Room& room, const Bed& bed, ExtensionTypes extensions = ExtensionTypes{ });

    /**
     * @return the bed name
     */
    std::string bed() const;

    /**
     * @return the building name
     */
    std::string building() const;

    /**
     * @return facility (hospital) name
     */
    std::string facility() const;

    /**
     * @return floor name
     */
    std::string floor() const;

    /**
     * @return point of care (also known as care unit) name
     */
    std::string pointOfCare() const;

    /**
     * @return room name
     */
    std::string room() const;

    /**
     * @brief Compares members pairwise.
     * @param rhs Other instance to compare with.
     * @return \c true in case all member are equal
     */
    bool operator==(const LocationDetail& rhs) const;

    /**
     * @brief Compares members pairwise.
     * @param rhs Other instance to compare with.
     * @return \c false in case any member element differs.
     */
    bool operator!=(const LocationDetail& rhs) const;

private:
    Locale::Utf8 m_facility;
    Locale::Utf8 m_building;
    Locale::Utf8 m_floor;
    Locale::Utf8 m_poc;
    Locale::Utf8 m_room;
    Locale::Utf8 m_bed;
};


/**
 * @brief Checks validity of \ref DFL::Mdib::LocationDetail.
 * @details
 * For Dr&auml;ger devices only the following requirements are given for location details
 *
 * - OSF1812:<br>
 *   An SDC Provider shall provide non-empty and non-zero values for the attributes<br>
 *   LocationContextState/LocationDetail/PoC,<br>
 *   LocationContextState/LocationDetail/Facility and<br>
 *   LocationContextState/LocationDetail/Bed.<br>
 *   aPJ Comment: Draeger products only
 * - Other fields may be empty (OSF1813)
 * @ingroup Mdib
 */
bool validDraegerLocationDetail(const DFL::Mdib::LocationDetail& locationDetail);

inline bool validDraegerLocationDetail(const DFL::Mdib::LocationDetail& locationDetail)
{
    return !locationDetail.pointOfCare().empty()
            && !locationDetail.facility().empty()
            && !locationDetail.bed().empty();
}

inline LocationDetail::LocationDetail(const Bed& bedName) :
        m_facility(),
        m_building(),
        m_floor(),
        m_poc(),
        m_room(),
        m_bed(bedName.operator Locale::Utf8())
{
}

inline LocationDetail::LocationDetail(const Facility& facilityName) :
        m_facility(facilityName.operator Locale::Utf8()),
        m_building(),
        m_floor(),
        m_poc(),
        m_room(),
        m_bed()
{
}

inline LocationDetail::LocationDetail(const Facility& facilityName, const PointOfCare& poc, const Bed& bedName) :
        m_facility(facilityName.operator Locale::Utf8()),
        m_building(),
        m_floor(),
        m_poc(poc.operator Locale::Utf8()),
        m_room(),
        m_bed(bedName.operator Locale::Utf8())
{
}

inline LocationDetail::LocationDetail(const Facility& facilityName, const Building& buildingName,
        const Floor& floorName, const PointOfCare& poc, const Room& roomName, const Bed& bedName, ExtensionTypes extensions) :
        Impl::HasExtensions(std::move(extensions)),
        m_facility(facilityName.operator Locale::Utf8()),
        m_building(buildingName.operator Locale::Utf8()),
        m_floor(floorName.operator Locale::Utf8()),
        m_poc(poc.operator Locale::Utf8()),
        m_room(roomName.operator Locale::Utf8()),
        m_bed(bedName.operator Locale::Utf8())
{
}

inline std::string LocationDetail::bed() const
{
    return m_bed;
}

inline std::string LocationDetail::building() const
{
    return m_building;
}

inline std::string LocationDetail::facility() const
{
    return m_facility;
}

inline std::string LocationDetail::floor() const
{
    return m_floor;
}

inline std::string LocationDetail::pointOfCare() const
{
    return m_poc;
}

inline std::string LocationDetail::room() const
{
    return m_room;
}

inline bool LocationDetail::operator ==(const LocationDetail& rhs) const
{
    if (this == &rhs)
    {
        return true;
    }
    return m_poc == rhs.m_poc
        && m_room == rhs.m_room
        && m_bed == rhs.m_bed
        && m_facility == rhs.m_facility
        && m_building == rhs.m_building
        && m_floor == rhs.m_floor
        && extensions() == rhs.extensions();
}

inline bool LocationDetail::operator!=(const LocationDetail& rhs) const
{
    return !(*this == rhs);
}

}
}
