#pragma once

#include <Framework/Utils/Public/Uri.h>

#include <string>
#include <vector>

namespace S31::Sdc::Impl
{
/**
 * @brief Takes the white-space separated list of URIs and converts it a vector of URIs.
 * @details
 * Invalid URIs are skipped from the list.
 * @ingroup S31SdcCommon
 */
std::vector<DFL::Net::Uri> toUriSequence(const std::string& uriList);
}
