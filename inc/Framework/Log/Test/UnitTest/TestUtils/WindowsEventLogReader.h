#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)

#include <string>

namespace DFLTest
{
namespace Log
{
struct WindowsEventLogMessage
{
    unsigned long eventId{};
    int eventType{};
    int category{};
    std::string text{};
};

bool operator==(const WindowsEventLogMessage& lhs,
                const WindowsEventLogMessage& rhs) noexcept;
bool operator!=(const WindowsEventLogMessage& lhs,
                const WindowsEventLogMessage& rhs) noexcept;

WindowsEventLogMessage readLastMessageFromWindowsEventLogSource(
    const std::string& eventSourceName);
}
}

#endif
