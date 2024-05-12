#pragma once

#include <Framework/Thread/Public/LockGuard.h>
#include <Framework/Thread/Public/RecursiveMutex.h>

namespace DFL
{
namespace Thread
{
/**
 * @brief Shortcut which combines the types
 * @ref DFL::Thread::LockGuard and DFL::Thread::RecursiveMutex.
 *
 * @ingroup Thread
 */
using ScopedLock = LockGuard<RecursiveMutex>;
}
}
