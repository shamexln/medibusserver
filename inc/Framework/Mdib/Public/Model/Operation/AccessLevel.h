#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Defines a user group to whom access to an operation is granted.
 * @ingroup Mdib
 */
enum class AccessLevel
{
    /// Individuals or entity accountable to the responsible organization that configure clinical relevant settings of a medical device.
    ClinicalSuperUser,
    /// Any person interacting with (i.e. operating or handling) the medical device.
    User,
    /// RO = Responsible Organization. Access is restricted to a responsible organization (i.e., an entity that is accountable for the use and maintenance of a medical device).
    ResponsibleOrganization,
    /// Access is restricted to service personnel (i.e., individuals or entity accountable to the responsible organization that install, assemble, maintain, or repair a medical device).
    ServicePersonnel,
    /// Access is restricted by other means (e.g., an extension).
    Other
};
DFL_ENUM_CLASS_STREAM_OPERATOR(AccessLevel, (ClinicalSuperUser)(User)(ResponsibleOrganization)(ServicePersonnel)(Other))

} /* namespace Mdib */
} /* namespace DFL */
