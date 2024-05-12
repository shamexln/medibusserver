#pragma once

#include <string>

namespace S31::Nomenclature::Impl
{
std::string sanitizeToPrintableAscii(const std::string& unsecureInput);
}
