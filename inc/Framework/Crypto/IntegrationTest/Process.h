#pragma once

#include <Framework/Config/Public/Config.h>

#if defined(DFL_CONFIG_OS_VXWORKS)
#include <Framework/Crypto/IntegrationTest/ProcessVxWorks.h>
#else
#include <Framework/Crypto/IntegrationTest/ProcessBoost.h>
#endif

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Filesystem/Private/Protected/Path.h>

#include <string>
#include <vector>

namespace DFL
{
namespace Process
{
class Process : private Impl::ProcessImpl
{
public:
    ~Process() noexcept;

    Process() = default;

    Process(const Process&) = delete;
    Process& operator=(const Process&) = delete;

    Process(Process&&) = default;
    Process& operator=(Process&&) = default;

    Process(Filesystem::Path path, std::vector<std::string> args);

    void wait();
    bool wait_for(DFL::Chrono::Microseconds waitTime);
    void terminate() noexcept;
};
}
}
