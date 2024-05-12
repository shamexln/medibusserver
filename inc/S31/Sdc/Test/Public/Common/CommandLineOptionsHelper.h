#pragma once

#include <S31/Sdc/S31Only/CommandLineOptions.h>

namespace S31::Test
{

inline bool isIgnoreReturnCodeSet(const S31::CommandLineOptions& options)
{
    return options.getSystemProperty("S31Test.IgnoreReturnCode") == "1";
}

}
