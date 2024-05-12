#pragma once

#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <pthread.h>

namespace DFL
{
    namespace Thread
    {
        namespace Impl
        {

            class DFL_THREAD_EXPIMP RecursiveMutexImpl
            {
                DFL_NOT_COPYABLE(RecursiveMutexImpl)
            protected:
                RecursiveMutexImpl();
                ~RecursiveMutexImpl();

                void lockImpl();
                bool tryLockImpl();
                void unlockImpl();

            private:
                pthread_mutex_t m_cs;
            };

        }
    }
}
