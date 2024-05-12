#pragma once

#include <string>

namespace S31::Sdc::Impl::Test
{
const std::string RegexIp = "\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}";
const std::string RegexPort = "()([1-9]|[1-5]?[0-9]{2,4}|6[0-5][0-9]{3}|6[1-4][0-9]{3}|65[1-4][0-9]{2}|655[1-2][0-9]|6553[1-5])";
const std::string RegexContext = "context=<\\{[^\\}]+?\\}>";
const std::string RegexDualChannel = "dual channel=<\\{[^\\}]+?\\}>";
const std::string RegexSafetyContext = RegexContext + ";" + RegexDualChannel;

}
