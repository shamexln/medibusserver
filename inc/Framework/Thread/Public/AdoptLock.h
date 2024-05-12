#pragma once

/**
 * @ingroup Thread
 * @{
 */
namespace DFL
{
namespace Thread
{
/**
 * @brief Tag type to specify the locking strategy.
 */
struct AdoptLock
{
};

/**
 * @brief Instance of tag type to be used as parameter for constructing e.g.
 * @ref DFL::Thread::LockGuard or @ref DFL::Thread::SemGuard.
 */
const AdoptLock adoptLock;
}
}
/** @} */
