#pragma once

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/SkillBoostSerializable.h>

namespace DFL
{
namespace Mdib
{
namespace Impl
{
struct XPathExpressionTag;
}

/**
 * @brief Definition of a limited XPath expression to point to specific members.
 * @ingroup Mdib
 */
using XPathExpression = DFL::StrongTypedef<Locale::Utf8, Impl::XPathExpressionTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable, DFL::Skill::BoostSerializable>;

}
}
