/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Component/BatteryDescriptor.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Calls the visitor for each member.
 *
 * @param vis visitor
 * @param batteryDescriptor @ref DFL::Mdib::BatteryDescriptor value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const BatteryDescriptor& batteryDescriptor)
{
    vis(batteryDescriptor.safetyClassification());
    vis(batteryDescriptor.type());
    vis(batteryDescriptor.productionSpecifications());
    vis(batteryDescriptor.capacityFullCharge());
    vis(batteryDescriptor.capacitySpecified());
    vis(batteryDescriptor.voltageSpecified());
    vis(batteryDescriptor.extensions());
}
}
}
}