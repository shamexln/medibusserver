/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Alert/AlertConditionDescriptor.h>

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
 * @param alertConditionDescriptor @ref DFL::Mdib::AlertConditionDescriptor value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const AlertConditionDescriptor& alertConditionDescriptor)
{
    vis(alertConditionDescriptor.safetyClassification());
    vis(alertConditionDescriptor.type());
    vis(alertConditionDescriptor.kind());
    vis(alertConditionDescriptor.priority());
    vis(alertConditionDescriptor.defaultConditionGenerationDelay());
    vis(alertConditionDescriptor.canEscalate());
    vis(alertConditionDescriptor.canDeescalate());
    vis(alertConditionDescriptor.sources());
    vis(alertConditionDescriptor.causeInfos());
    vis(alertConditionDescriptor.extensions());
}
}
}
}