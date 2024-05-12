#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct CodeIdTag;
}
/**
 * @brief Strong typedef of a BICEPS CodeIdentifier.
 * @details The minimum length of the CodeIdentifier is 1 character.
 *
 * @ingroup Mdib
 */
using CodeId = DFL::StrongTypedef<DFL::Locale::Utf8, Impl::CodeIdTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

}
}
