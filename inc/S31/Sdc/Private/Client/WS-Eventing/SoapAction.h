#pragma once

#include <string_view>
#include <vector>

namespace S31::Sdc::Impl
{
using SoapAction  = std::string_view;
using SoapActions = std::vector<SoapAction>;

std::string join(const SoapActions& actions);
}
