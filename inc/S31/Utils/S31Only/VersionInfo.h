#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>
#include <S31/Utils/S31Only/VersionInfoHelper.h>

namespace S31::Utils
{

/**
 * @brief Get the version information.
 * @ingroup S31Utils
 */
S31_UTILS_EXPIMP void addVersionInfo(Utils::VersionInfo& versions);
}
