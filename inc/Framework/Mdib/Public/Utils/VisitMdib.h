#pragma once

#include <Framework/Mdib/Private/Utils/VisitMdibImpl.h>
#include <Framework/Mdib/Public/Utils/EntityLists.h>
#include <Framework/Mdib/Public/Utils/Entities.h>
#include <Framework/Mdib/Private/Utils/VisitMembers.h>
#include <Framework/Mdib/Public/Model/Alert/AlertCondition.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignal.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertCondition.h>
#include <Framework/Mdib/Public/Model/Component/Battery.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Component/Clock.h>
#include <Framework/Mdib/Public/Model/Component/Mds.h>
#include <Framework/Mdib/Public/Model/Component/Sco.h>
#include <Framework/Mdib/Public/Model/Component/SystemContext.h>
#include <Framework/Mdib/Public/Model/Component/Vmd.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContext.h>
#include <Framework/Mdib/Public/Model/Context/EnsembleContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/LocationContext.h>
#include <Framework/Mdib/Public/Model/Context/LocationContextIndicator.h>
#include <Framework/Mdib/Public/Model/Context/PatientContext.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextIndicator.h>
#include <Framework/Mdib/Public/Model/Metric/DistributionSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/EnumStringMetric.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetric.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetric.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Visit function to visit all state members in the MDIB containment tree.
 * @details
 * In case the visitor is only interested in one member type (e.g., LocalizedTexts),
 * it is recommended to use the corresponding \ref DFL::Mdib::visitTypeInStates() function.
 * @param vis The visitor function with overloads for all kind of MDIB state data members.
 * @param mdib The MDIB instance to visit.
 * @ingroup Mdib
 */
template <class Visitor>
void visitStates(Visitor& vis, const Mdib& mdib)
{
    Impl::MdibEntityStateVisitor<Visitor> visitor(vis, mdib);
    Entities<DFL_MDIB_ENTITY_COMPONENTS,DFL_MDIB_ENTITY_ALERTS,DFL_MDIB_ENTITY_METRICS,
             DFL_MDIB_ENTITY_OPERATIONS,DFL_MDIB_ENTITY_CONTEXT_STATES>::applyVisitor(visitor);
}

/**
 * @brief Visit function to visit all state members in the MDIB change set.
 * @details
 * In case the visitor is only interested in one member type (e.g., LocalizedTexts),
 * it is recommended to use the corresponding \ref DFL::Mdib::visitTypeInStates() function.
 * @param vis The visitor function with overloads for all kind of state data members.
 * @param changes The MDIB change set to visit.
 * @ingroup Mdib
 */
template <class Visitor>
void visitStates(Visitor& vis, const MdibChangeSet& changes)
{
    Impl::ChangeSetEntityStateVisitor<Visitor> visitor(vis, changes);
    Entities<DFL_MDIB_ENTITY_COMPONENTS,DFL_MDIB_ENTITY_ALERTS,DFL_MDIB_ENTITY_METRICS,
             DFL_MDIB_ENTITY_OPERATIONS,DFL_MDIB_ENTITY_CONTEXT_STATES>::applyVisitor(visitor);
}

/**
 * @brief Visit function to visit all descriptor members in the MDIB containment tree.
 * @details
 * In case the visitor is only interested in one member type (e.g., LocalizedTexts),
 * it is recommended to use the corresponding \ref DFL::Mdib::visitTypeInDescriptors() function.
 * @param vis The visitor function with overloads for all kind of MDIB descriptor data members.
 * @param mdib The MDIB instance to visit.
 * @ingroup Mdib
 */
template <class Visitor>
void visitDescriptors(Visitor& vis, const Mdib& mdib)
{
    Impl::MdibEntityDescriptorVisitor<Visitor> visitor(vis, mdib);
    Entities<DFL_MDIB_ENTITY_COMPONENTS,DFL_MDIB_ENTITY_ALERTS,DFL_MDIB_ENTITY_METRICS,
             DFL_MDIB_ENTITY_OPERATIONS,DFL_MDIB_ENTITY_CONTEXT_INDICATORS>::applyVisitor(visitor);
}

/**
 * @brief Visit function to visit all descriptor members in the MDIB change set.
 * @details
 * In case the visitor is only interested in one member type (e.g., LocalizedTexts),
 * it is recommended to use the corresponding \ref DFL::Mdib::visitTypeInDescriptors() function.
 * @param vis The visitor function with overloads for all kind of descriptor data members.
 * @param changes The MDIB change set to visit.
 * @ingroup Mdib
 */
template <class Visitor>
void visitDescriptors(Visitor& vis, const MdibChangeSet& changes)
{
    Impl::ChangeSetEntityDescriptorVisitor<Visitor> visitor(vis, changes);
    Entities<DFL_MDIB_ENTITY_COMPONENTS,DFL_MDIB_ENTITY_ALERTS,DFL_MDIB_ENTITY_METRICS,
             DFL_MDIB_ENTITY_OPERATIONS,DFL_MDIB_ENTITY_CONTEXT_INDICATORS>::applyVisitor(visitor);
}

/**
 * @brief Visit function to visit all (state and descriptor) members in the MDIB containment tree.
 * @details
 * In case the visitor is only interested in one member type (e.g., LocalizedTexts),
 * it is recommended to use the corresponding \ref DFL::Mdib::visitTypeInMdib() function.
 * @param vis The visitor function with overloads for all kind of MDIB data members.
 * @param mdib The MDIB instance to visit.
 * @ingroup Mdib
 */
template <class Visitor>
void visitMdib(Visitor& vis, const Mdib& mdib)
{
    visitDescriptors(vis, mdib);
    visitStates(vis, mdib);
}

/**
 * @brief Visit function to visit all (state and descriptor) members in the MDIB change set.
 * @details
 * In case the visitor is only interested in one member type (e.g., LocalizedTexts),
 * it is recommended to use the corresponding \ref DFL::Mdib::visitTypeInChangeSet() function.
 * @param vis The visitor function with overloads for all kind of state and descriptor data members.
 * @param changes The MDIB change set to visit.
 * @ingroup Mdib
 */
template <class Visitor>
void visitChangeSet(Visitor& vis, const MdibChangeSet& changes)
{
    visitDescriptors(vis, changes);
    visitStates(vis, changes);
}


/**
 * @brief Shortcut function to visit one specific type in the state part of an MDIB instance.
 * @tparam TypeToVisit Typically a member type like \ref DFL::Mdib::LocalizedTexts.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param mdib The MDIB instance from which the states should be visited.
 * @ingroup Mdib
 */
template <class TypeToVisit>
void visitTypeInStates(const std::function<void(const TypeToVisit&)>& function, const Mdib& mdib)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitStates(visitor, mdib);
}

/**
 * @brief Shortcut function to visit one specific type in the state parts of an MDIB change set.
 * @tparam TypeToVisit Typically a member type like \ref DFL::Mdib::LocalizedTexts.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param changes The MDIB change set from which the states should be visited.
 * @ingroup Mdib
 */
template <class TypeToVisit>
void visitTypeInStates(const std::function<void(const TypeToVisit&)>& function, const MdibChangeSet& changes)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitStates(visitor, changes);
}

/**
 * @brief Shortcut function to visit one specific type in the descriptor part of an MDIB instance.
 * @tparam TypeToVisit Typically a member type like \ref DFL::Mdib::LocalizedTexts.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param mdib The MDIB instance from which the descriptors should be visited.
 * @ingroup Mdib
 */
template <class TypeToVisit>
void visitTypeInDescriptors(const std::function<void(const TypeToVisit&)>& function, const Mdib& mdib)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitDescriptors(visitor, mdib);
}

/**
 * @brief Shortcut function to visit one specific type in the descriptor parts of an MDIB change set.
 * @tparam TypeToVisit Typically a member type like \ref DFL::Mdib::LocalizedTexts.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param changes The MDIB change set from which the descriptors should be visited.
 * @ingroup Mdib
 */
template <class TypeToVisit>
void visitTypeInDescriptors(const std::function<void(const TypeToVisit&)>& function, const MdibChangeSet& changes)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitDescriptors(visitor, changes);
}

/**
 * @brief Shortcut function to visit one specific type in the state and descriptor part of an MDIB instance.
 * @tparam TypeToVisit Typically a member type like \ref DFL::Mdib::LocalizedTexts.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param mdib The MDIB instance from which the states and descriptors should be visited.
 * @ingroup Mdib
 */
template <class TypeToVisit>
void visitTypeInMdib(const std::function<void(const TypeToVisit&)>& function, const Mdib& mdib)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitDescriptors(visitor, mdib);
    visitStates(visitor, mdib);
}

/**
 * @brief Shortcut function to visit one specific type in the state and descriptor parts of an MDIB change set.
 * @tparam TypeToVisit Typically a member type like \ref DFL::Mdib::LocalizedTexts.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param changes The MDIB change set from which the states and descriptors should be visited.
 * @ingroup Mdib
 */
template <class TypeToVisit>
void visitTypeInChangeSet(const std::function<void(const TypeToVisit&)>& function, const MdibChangeSet& changes)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitChangeSet(visitor, changes);
}
}
}
