#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

namespace S31::Sdc
{

/**
 * @brief To be used to limit the number of Jobs in operations.
 * @ingroup S31SdcCommon
 */
using MaxResultCount = DFL::StrongTypedef<unsigned int, struct MaxResultCountTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Indicate that there is no limit in number of desired jobs.
 * @details The number is just much larger then groups of jobs on real systems.
 * @ingroup S31SdcCommon
 */
const unsigned int UnlimitedResults = 100000;

}
