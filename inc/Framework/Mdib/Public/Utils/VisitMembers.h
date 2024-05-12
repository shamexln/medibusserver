#pragma once

#include <Framework/Mdib/Private/Utils/VisitMembers.h>

namespace DFL
{
namespace Mdib
{
/**
 * @brief Shortcut function to visit one specific member type.
 * @param function Handler function to be called for each member of given TypeToVisit.
 * @param container Type that contains the members to visit.
 * @ingroup Mdib
 */
template <class TypeToVisit, class Container>
void visitTypeInMembers(const std::function<void(const TypeToVisit&)>& function, const Container& container)
{
    Impl::TypeVisitor<TypeToVisit> visitor(function);
    visitMembers(visitor, container);
}
}
}
