#pragma once

namespace S31::Sdc::Impl
{

/**
 * @brief Helper to set Thread name.
 * @ingroup S31SdcCommon
 */
class ThreadName
{
    public:
        /**
         * @brief Sets the name of the current thread to given name for debugging purposes.
         * @param threadName The human readable name of the thread.
         */
        static void setMyThreadName(const char* threadName);
};

}
