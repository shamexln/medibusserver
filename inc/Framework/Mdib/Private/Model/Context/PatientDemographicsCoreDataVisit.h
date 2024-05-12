#pragma once

#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreData.h>
#include <Framework/Mdib/Private/Model/Context/BaseDemographicsVisit.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
/**
 * @brief Visit all members.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMembers(Visitor& vis, const PatientDemographicsCoreData& p)
{
    // visit base members
    vis(static_cast<const BaseDemographics&>(p));

    vis(p.sex());
    vis(p.patientType());
    vis(p.dateOfBirth());
    vis(p.height());
    vis(p.weight());
    vis(p.race());

    // from pm:NeonatalPatientDemographicsCoreData
    vis(p.gestationalAge());
    vis(p.birthLength());
    vis(p.birthWeight());
    vis(p.headCircumference());
    vis(p.mother());
}
}
}
}
