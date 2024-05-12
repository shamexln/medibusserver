#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)

#include <Framework/Log/Private/ExpImp.h>

#include <Framework/Config/Public/WindowsProxy.h>

#include <functional>
#include <memory>
#include <string>
#include <type_traits>

namespace DFL
{
namespace Log
{
namespace Impl
{
namespace Windows
{
class DFL_LOG_EXPIMP EventLogApi
{
public:
    using ReportEventFunc = std::function<
        BOOL(HANDLE, WORD, WORD, DWORD, PSID, WORD, DWORD, LPCSTR*, LPVOID)>;
    using RegisterEventSourceFunc = std::function<HANDLE(LPCSTR, LPCSTR)>;
    using DeregisterEventSourceFunc = std::function<BOOL(HANDLE)>;

    static ReportEventFunc s_reportEvent;
    static RegisterEventSourceFunc s_registerEventSource;
    static DeregisterEventSourceFunc s_deregisterEventSource;

    static void reset();
};

class DFL_LOG_EXPIMP EventLog
{
public:
    using Handle = HANDLE;
    using HandlePtr =
        std::shared_ptr<typename std::remove_pointer<Handle>::type>;

    EventLog() = default;
    explicit EventLog(const std::string& srcName);

    Handle handle() const noexcept;
    bool equals(const EventLog& other) const noexcept;
    void write(LPCSTR text, WORD eventType, DWORD eventId, WORD category) const;

    void swap(EventLog& other) noexcept;

private:
    HandlePtr m_handlePtr{};
};
DFL_LOG_EXPIMP bool operator==(const EventLog& a, const EventLog& b) noexcept;
DFL_LOG_EXPIMP bool operator!=(const EventLog& a, const EventLog& b) noexcept;

DFL_LOG_EXPIMP void swap(EventLog& a, EventLog& b) noexcept;
}
}
}
}
#endif
