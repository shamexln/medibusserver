#pragma once

#include <S31/Sdc/Private/Common/Scheduling/ISslHandshakeSemaphore.h>

#include <Framework/Thread/Public/Semaphore.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Implements a semaphore to limit the amount of concurrent SSL handshakes.
 * @ingroup S31SdcCommonScheduling
 */
class SslHandshakeSemaphore: public ISslHandshakeSemaphore
{
    public:
        /**
         * @brief Constructs a semaphore with initial maximum count of allowed concurrent SSL handshakes.
         */
        explicit SslHandshakeSemaphore(unsigned int maxCount);

        std::unique_ptr<ISemaphoreGuard> sslHandshakeGuard() override;

    private:
        DFL::NotNull<std::shared_ptr<DFL::Thread::Semaphore>> m_semaphore;
};

}
