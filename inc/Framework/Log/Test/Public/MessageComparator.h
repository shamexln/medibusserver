#pragma once

#include <Framework/Log/Public/Message.h>

#include <Framework/Config/Public/Attributes.h>

namespace DFL
{
namespace Log
{
namespace Test
{
/**
 * @brief DEPRECATED use @ref DFL::Log::MessageComparator
 *
 * @deprecated use @ref DFL::Log::MessageComparator
 *
 * @ingroup Log
 */
using MessageComparator DFL_ATTRIBUTE_DEPRECATED(
    "use ::DFL::Log::MessageComparator") = ::DFL::Log::MessageComparator;
}
}
}
