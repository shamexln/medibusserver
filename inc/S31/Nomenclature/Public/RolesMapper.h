#pragma once

#include <Framework/Utils/Public/Oids.h>

#include <string>

namespace S31::Nomenclature
{

/**
 * @brief Helper function to map roles from \ref DFL::Oid format to std::string format.
 * @ingroup S31Nomenclature
 */
std::string mapRoleOidsToString(const DFL::Oids& roles);

}
