#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Utils/S31Only/VersionInfoHelper.h>

namespace S31::Sdc
{

/**
 * @brief Get the version information.
 * @ingroup S31SdcCommon
 */
S31_CORE_EXPIMP void addVersionInfo(Utils::VersionInfo& versions);
}
