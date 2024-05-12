#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Type for an URI (Uniform Resource Identifier).
 * @ingroup Mdib
 */
using Uri = DFL::StrongTypedef<std::string, struct UriTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Sequence of \ref Uri.
 * @ingroup Mdib
 */
using Uris = std::vector<Uri>;

} /* namespace Mdib */
} /* namespace DFL */
