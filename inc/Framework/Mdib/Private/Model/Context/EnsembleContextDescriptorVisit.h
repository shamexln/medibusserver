/**************************************************************************************
 *
 * DO NOT EDIT THIS FILE MANUALLY
 * THIS FILE IS GENERATED BY
 * modules\S32\Tools\MdibBuilders\RunGenerator.cmd
 *
 **************************************************************************************/

#pragma once

#include <Framework/Mdib/Public/Model/Context/EnsembleContextDescriptor.h>

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
 * @param ensembleContextDescriptor @ref DFL::Mdib::EnsembleContextDescriptor value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const EnsembleContextDescriptor& ensembleContextDescriptor)
{
    vis(ensembleContextDescriptor.safetyClassification());
    vis(ensembleContextDescriptor.type());
    vis(ensembleContextDescriptor.extensions());
}
}
}
}