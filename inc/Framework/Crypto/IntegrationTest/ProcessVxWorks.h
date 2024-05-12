#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Filesystem/Private/Protected/Path.h>

#include <string>
#include <vector>

#include <rtpLib.h>

namespace DFL
{
namespace Process
{
namespace Impl
{
class ProcessImpl
{
public:
    ProcessImpl() = default;

    ProcessImpl(const ProcessImpl&) = delete;
    ProcessImpl& operator=(const ProcessImpl&) = delete;

    ProcessImpl(ProcessImpl&&) = default;
    ProcessImpl& operator=(ProcessImpl&&) = default;

    ProcessImpl(Filesystem::Path path, std::vector<std::string> args);

    void waitImpl();
    bool wait_forImpl(DFL::Chrono::Microseconds waitTime);
    void terminateImpl() const noexcept;

private:
    RTP_ID m_pid{RTP_ID_ERROR};
    Filesystem::Path m_path{};
    std::vector<std::string> m_args{};
};
}
}
}
