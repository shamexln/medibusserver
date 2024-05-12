#pragma once

#include <Framework/Mdib/Public/Model/Context/BaseDemographics.h>

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
 * @param baseDemographics @ref DFL::Mdib::BaseDemographics value to visit
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const BaseDemographics& baseDemographics)
{
    vis(baseDemographics.givenName());
    vis(baseDemographics.middleName());
    vis(baseDemographics.familyName());
    vis(baseDemographics.birthName());
    vis(baseDemographics.title());
    vis(baseDemographics.extensions());
}
}
}
}
