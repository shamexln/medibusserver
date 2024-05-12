#pragma once

#include <Framework/Chrono/Private/BasicDateTime.h>
#include <Framework/Config/Public/Attributes.h>

DFL_HEADER_DEPRECATED("use ZonedTime from ZonedTime.h instead")

namespace DFL
{
namespace Chrono
{
/**
 * @brief DEPRECATED
 *
 * @deprecated Please use @ref DFL::Chrono::ZonedTime instead.
 *
 * @ingroup Chrono
 */
using LocalDateTime DFL_ATTRIBUTE_DEPRECATED(
    "use DFL::Chrono::ZonedTime instead") = Impl::LocalDateTime;
}
}
