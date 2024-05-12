#pragma once

#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <semaphore.h>

namespace DFL
{
    namespace Thread
    {
        namespace Impl
        {

            class DFL_THREAD_EXPIMP SemaphoreImpl
            {
                DFL_NOT_COPYABLE(SemaphoreImpl)
            protected:
                explicit SemaphoreImpl(unsigned int count);
                ~SemaphoreImpl();

                void acquireImpl();
                bool tryAcquireForImpl(const Chrono::Milliseconds& timeoutDuration);
                void releaseImpl();

            private:
                sem_t m_sem;

                SemaphoreImpl();
            };

        }
    }
}
