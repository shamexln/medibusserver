#pragma once

#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <type_traits>

namespace DFL
{
namespace Thread
{
namespace Impl
{
#ifdef _WIN64
constexpr std::size_t SizeOfCriticalSection = 40;
constexpr std::size_t AlignOfCriticalSection = 8;
#else
constexpr std::size_t SizeOfCriticalSection = 24;
constexpr std::size_t AlignOfCriticalSection = 4;
#endif

class DFL_THREAD_EXPIMP RecursiveMutexImpl
{
public:
    using Type = std::aligned_storage<SizeOfCriticalSection,
                                      AlignOfCriticalSection>::type;
    DFL_NOT_COPYABLE(RecursiveMutexImpl)
protected:
    RecursiveMutexImpl();
    ~RecursiveMutexImpl();

    void lockImpl();
    bool tryLockImpl();
    void unlockImpl();

private:
    // Instead of using CRITICAL_SECTION we have an array that is
    // large enough to hold all data from CRITICAL_SECTION. This
    // works due to the fact that CRITICAL_SECTION has no
    // constructor and the memory is initialized with
    // InitializeCriticalSectionAndSpinCount() in
    // RecursiveMutexImpl()
    Type m_cs;
};

}
}
}
