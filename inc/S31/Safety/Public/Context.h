#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Utf8.h>

#include <map>

namespace S31::Safety
{

/**
 * @brief A unique identifier over all safety contexts.
 * @ingroup S31Safety
 */
using ContextId = DFL::StrongTypedef<DFL::Locale::Utf8, struct ContextIdTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable> ;

/**
 * @brief Strong typedef for a safety context value.
 * @ingroup S31Safety
 */
using ContextValue = DFL::StrongTypedef<DFL::Locale::Utf8, struct ContextTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief A map with safety context information (indexed by their \ref ContextId).
 * @ingroup S31Safety
 */
using Context = std::map<ContextId, ContextValue>;


}
