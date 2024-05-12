#pragma once

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <semLib.h>

namespace DFL
{
namespace Thread
{
namespace Impl
{

class RecursiveMutexImpl
{
DFL_NOT_COPYABLE(RecursiveMutexImpl)

protected:
    RecursiveMutexImpl();
    ~RecursiveMutexImpl();

    void lockImpl();
    bool tryLockImpl();
    void unlockImpl();

private:
    SEM_ID m_semId{semMCreate(SEM_INVERSION_SAFE | SEM_Q_PRIORITY)};
};

}
}
}
