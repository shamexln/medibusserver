#pragma once

#include <S31/Safety/Public/DualChannel.h>

#include <Framework/Utils/Public/Sha1.h>
#include <Framework/Utils/Public/Sha1Io.h>
#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::Safety
{

/**
 * @brief String typedef for dual channel SHA1 hash.
 * @ingroup S31Safety
 */
using DualChannelHash = DFL::StrongTypedef<DFL::Sha1, struct DualChannelHashTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;

/**
 * @brief Container for multiples dual channel hashes.
 * @ingroup S31Safety
 */
using DualChannelHashes = std::map<DualChannelId, DualChannelHash>;

}
