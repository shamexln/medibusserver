#pragma once

#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Config/Public/WindowsProxy.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <string>

namespace DFL
{
namespace Thread
{
namespace Impl
{

class DFL_THREAD_EXPIMP AutoResetEventImpl
{
DFL_NOT_COPYABLE(AutoResetEventImpl)

public:
    explicit AutoResetEventImpl(bool initiallyBlocking);
    ~AutoResetEventImpl();

    void waitImpl();
    bool tryWaitForImpl(const Chrono::Milliseconds& timeoutDuration);
    void setImpl();

private:
    using WaitResult = enum
    {
        Error, Acquired, Timeout
    };

    WaitResult waitForEvent(DWORD timeout, std::string& errorMessage);

    HANDLE m_event;
};

}
}
}
