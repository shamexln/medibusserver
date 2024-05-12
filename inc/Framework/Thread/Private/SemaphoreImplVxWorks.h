#pragma once

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Utils/Public/CompilerGenerated.h>

#include <semLib.h>

namespace DFL
{
    namespace Thread
    {
        namespace Impl
        {

            class SemaphoreImpl
            {
                DFL_NOT_COPYABLE(SemaphoreImpl)
            protected:
                explicit SemaphoreImpl(unsigned int initialCount);
                ~SemaphoreImpl();

                void acquireImpl();
                bool tryAcquireForImpl(const Chrono::Milliseconds& timeoutDuration);
                void releaseImpl();

            private:
                SEM_ID m_semId;
            };

        }
    }
}
