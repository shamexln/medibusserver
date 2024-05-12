#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>
#include <Framework/Utils/Public/Utf8.h>

#include <vector>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct AllowedStringValueTag;
}

/**
 * @brief A value that is allowed to be passed to \ref SetStringOperationState "set string operation" call.
 * @ingroup Mdib
 */
using AllowedStringValue = DFL::StrongTypedef<Locale::Utf8, Impl::AllowedStringValueTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

/**
 * @brief A sequence of \ref AllowedStringValue "allowed values".
 * @ingroup Mdib
 */
using AllowedStringValues = std::vector<AllowedStringValue>;

}
}
