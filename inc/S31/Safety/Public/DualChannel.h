#pragma once

#include <S31/Safety/Public/DualChannelComparator.h>

#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Utf8Io.h>

#include <map>

namespace S31::Safety
{

/**
 * @brief A unique identifier over all dual channels.
 * @ingroup S31Safety
 */
using DualChannelId = DFL::StrongTypedef<DFL::Locale::Utf8, struct DualChannelIdTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief A map with dual channel information (indexed by their \ref DualChannelId).
 * @ingroup S31Safety
 */
using DualChannel = std::map<DualChannelId, DFL::NotNull<std::shared_ptr<DualChannelComparator>>>;

}
