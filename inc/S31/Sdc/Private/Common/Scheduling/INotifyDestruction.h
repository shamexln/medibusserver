#pragma once

namespace S31::Sdc::Impl
{

/**
 * @brief Interface to notify as destruction.
 *
 * @ingroup S31SdcCommonScheduling
 */
class INotifyDestruction
{
    public:
        virtual ~INotifyDestruction() noexcept = default;

        /**
         * Shall be called if an object is destroyed.
         */
        virtual void destructorRunning() = 0;
};

}
