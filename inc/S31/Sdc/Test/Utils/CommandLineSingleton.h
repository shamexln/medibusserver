#pragma once

#include <S31/Sdc/S31Only/CommandLineOptions.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

namespace S31::Test
{

class S31_CORE_IT_UTIL_EXPIMP CommandLineSingleton
{
    public:
        static void setup(int argc, const char * const argv[]);
        static void addOptions(const CommandLineOptions& options);
        static CommandLineOptions get();
};

}
