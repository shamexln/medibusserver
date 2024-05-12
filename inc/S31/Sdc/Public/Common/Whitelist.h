#pragma once

#include <S31/Nomenclature/Public/Whitelist.h>

#include <Framework/Config/Public/Attributes.h>

DFL_HEADER_DEPRECATED("Use S31/Nomenclature/Public/Whitelist.h instead")

namespace S31::Sdc
{

/**
 * @brief Encapsulates the whitelist used in \ref S31::CoreConfiguration "S31 core configuration".
 * @details Also provides additional functionality to check whether a peer is whitelisted.
 * @ingroup S31SdcCommon
 */
using Whitelist = S31::Nomenclature::Whitelist;

}
