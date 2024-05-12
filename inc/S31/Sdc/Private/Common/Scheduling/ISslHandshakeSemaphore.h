#pragma once

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * Interface to hide the semaphore for limiting the amount of concurrent SSL handshakes.
 * @ingroup S31SdcCommonScheduling
 */
class ISslHandshakeSemaphore
{
    public:
        virtual ~ISslHandshakeSemaphore() = default;

        /**
         * @brief Instance should be hold as long as the SSL handshake proceeds.
         * @ingroup S31SdcCommonScheduling
         */
        class ISemaphoreGuard
        {
            public:
                virtual ~ISemaphoreGuard() = default;
        };

        /**
         * Blocks until the next SSL handshake is allowed.
         */
        virtual std::unique_ptr<ISemaphoreGuard> sslHandshakeGuard() = 0;
};

}
