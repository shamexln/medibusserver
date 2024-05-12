#pragma once

#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <semLib.h>

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
    SEM_ID m_binarySemaphore;
};

}
}
}
