#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Current charge status of the battery.
 * @ingroup Mdib
 */
enum class ChargeStatus
{
    /// Full Battery. All available active material is in a state such that the charging under the selected conditions produces no significant increase of capacity. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-05-42..
    FullBattery,
    /// Charging Battery. Battery is currently supplied with electric energy from an external circuit. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-05-27.
    ChargingBattery,
    /// Discharging Battery. Battery delivers, to an external electric circuit and under specified conditions, electric energy produced in the cells. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-03-23
    DischargingBattery,
    ///  Discharged Empty Battery. Discharged secondary battery. See also IEC 60050-482 International Electrotechnical Vocabulary, 482-05-31.
    EmptyBattery
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ChargeStatus, (FullBattery)(ChargingBattery)(DischargingBattery)(EmptyBattery))

} /* namespace Mdib */
} /* namespace DFL */
