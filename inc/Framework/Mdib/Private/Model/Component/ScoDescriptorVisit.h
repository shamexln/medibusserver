/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Component/ScoDescriptor.h>

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
 * @param scoDescriptor @ref DFL::Mdib::ScoDescriptor value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const ScoDescriptor& scoDescriptor)
{
    vis(scoDescriptor.safetyClassification());
    vis(scoDescriptor.type());
    vis(scoDescriptor.productionSpecifications());
    vis(scoDescriptor.extensions());
}
}
}
}
