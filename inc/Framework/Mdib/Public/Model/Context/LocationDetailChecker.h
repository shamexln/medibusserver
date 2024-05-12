#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{
/*!
 * \brief
 * Checks, if a given location/locationDetail has valid content
 *
 * \ingroup Mdib
 */
namespace LocationDetailChecker
{

/**
 * Result of various check functions
 *
 * \ingroup Mdib
 */
enum class Status
{
    CheckOk,
    FieldEmpty,
    FieldTooLong,
    FieldHasIllegalCharacter
};
DFL_ENUM_CLASS_STREAM_OPERATOR(Status, (CheckOk)(FieldEmpty)(FieldTooLong)(FieldHasIllegalCharacter))

/**
 * Check that PointOfCare field ...
 * - is not empty (mandatory field)
 * - has max. 7 characters
 * - has only valid characters (A-Za-z0-9-._~)
 * @param str The field string
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkPointOfCare(const std::string& str);


/**
 * Check that Facility field ...
 * - is not empty (mandatory field)
 * - has max. 7 characters
 * - has only valid characters (A-Za-z0-9-._~)
 * @param str The field string
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkFacility(const std::string& str);

/**
 * Check that Bed field ...
 * - is not empty (mandatory field)
 * - has max. 7 characters
 * - has only valid characters (A-Za-z0-9-._~)
 * @param str The field string
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkBed(const std::string& str);

/**
 * Check that Building field ...
 * - has max. 7 characters
 * - has only valid characters (A-Za-z0-9-._~)
 * @param str The field string
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkBuilding(const std::string& str);

/**
 * Check that Floor field ...
 * - has max. 7 characters
 * - has only valid characters (A-Za-z0-9-._~)
 * @param str The field string
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkFloor(const std::string& str);

/**
 * Check that Room field ...
 * - has max. 7 characters
 * - has only valid characters (A-Za-z0-9-._~)
 * @param str The field string
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkRoom(const std::string& str);

/**
 * Check that all fields in locationDetail are valid using the check-functions above
 * @param locationDetail The location detail
 * @return Status::CheckOk or the status what is wrong
 *
 * \ingroup Mdib
 */
DFL_MDIB_EXPIMP Status checkLocationDetail(const DFL::Mdib::LocationDetail& locationDetail);

}
}
}
