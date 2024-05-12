#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Oid.h>
#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct RoleTag;
}
/**
 * @brief A role OID to identify a set of functionality.
 * @ingroup Mdib
 */
using Role = DFL::StrongTypedef<Oid, Impl::RoleTag, Skill::TotallyOrdered, Skill::Streamable>;

/**
 * @brief A sequence of \ref DFL::Mdib::Role "roles".
 * @ingroup Mdib
 */
using Roles = std::vector<Role>;

/**
 * \brief Representing Draeger Metric Provider role.
 *
 * \ingroup Mdib
 */
static const auto MetricProvider = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.1.1"}}};

/**
 * \brief Representing Draeger Metric Consumer role.
 *
 * \ingroup Mdib
 */
static const auto MetricConsumer = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.2.1"}}};

/**
 * \brief Representing Draeger Alert Provider role.
 *
 * \ingroup Mdib
 */
static const auto AlertProvider = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.3.1"}}};

/**
 * \brief Representing Draeger Alert Consumer role.
 *
 * \ingroup Mdib
 */
static const auto AlertConsumer = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.4.1"}}};

/**
 * \brief Representing Draeger Operation Provider role.
 *
 * \ingroup Mdib
 */
static const auto OperationProvider = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.5.1"}}};

/**
 * \brief Representing Draeger Operation Consumer role.
 *
 * \ingroup Mdib
 */
static const auto OperationConsumer = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.6.1"}}};

/**
 * \brief Representing Draeger Alert Consumer role intended for use in a distributed alarm system.
 *
 * \ingroup Mdib
 */
static const auto DistributedAlarmSystemConsumer = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.7.1"}}};

/**
 * \brief Representing Localizing Provider role.
 * \details This is for now a private role, it will not be visible on the network (to other peers).
 * \ingroup Mdib
 */
static const auto LocalizingProvider = Role{Oid{Oid::DotNotation{"1.3.6.1.4.1.3592.2.23.12.1"}}};


}
}
