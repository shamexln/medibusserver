#pragma once

namespace DFL
{
namespace Thread
{
/**
 * @brief
 * [BasicLockable](https://en.cppreference.com/w/cpp/named_req/BasicLockable)
 * type which does nothing.
 *
 * @details
 * This class can be used in contexts that require a BasicLockable type but are
 * known to *not* require exclusive blocking semantics e.g. in single threaded
 * environments or where the blocking is provided by other means.
 *
 * @ingroup Thread
 */
class NoLock
{
public:
    /**
     * @brief Does nothing.
     */
    void lock() const noexcept
    {
    }
    /**
     * @brief Does nothing.
     */
    void unlock() const noexcept
    {
    }
};
}
}
