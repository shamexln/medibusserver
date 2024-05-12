#pragma once

#include <S31/Utils/Public/UniquePtrVector.h>

namespace S31::Sdc
{
class Job;

/**
 * @brief Multiple Job pointers
 * @ingroup S31SdcCommon
 */
using JobPtrs = Utils::UniquePtrVector<Job>;

}
