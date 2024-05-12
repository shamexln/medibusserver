#pragma once

#include <S31/Utils/Public/BoostThread.h>

#include <boost/thread/thread.hpp>

#include <functional>

namespace S31::Sdc::Impl
{

/**
 * @brief Wraps a boost thread so that it can be used in the @ref ThreadPool as a replacement for std::thread.
 * @details This thread uses a custom stack size (needed for VxWorks).
 * @ingroup S31SdcCommon
 */
class PoolThread : public boost::thread
{
    public:
        PoolThread() = default;

        using Func = std::function<void()>;

        explicit PoolThread(Func &&func):
            boost::thread(boost::thread(BoostThread::defaultThreadAttributes(), std::move(func)))
        {}

        PoolThread(PoolThread&&) = default;
};

}
