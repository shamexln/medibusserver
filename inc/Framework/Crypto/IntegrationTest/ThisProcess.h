#pragma once

#include <Framework/Crypto/IntegrationTest/Process.h>

#include <Framework/Filesystem/Private/Protected/Filesystem.h>

#include <string>
#include <vector>

namespace DFLTest
{
namespace ThisProcess
{
DFL::Process::Process spawn(std::vector<std::string> args);

inline DFL::Process::Process spawn(std::vector<std::string> args)
{
    for (auto& a : args)
    {
        a.insert(0, "--");
    }
    return DFL::Process::Process{DFL::Filesystem::V2::currentExeFolder() /
                                     "DFL_Crypto_Integration_Test",
                                 args};
}
}
}
