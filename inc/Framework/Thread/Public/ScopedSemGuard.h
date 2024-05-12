#pragma once

#include <Framework/Thread/Public/SemGuard.h>
#include <Framework/Thread/Public/Semaphore.h>

namespace DFL
{
namespace Thread
{
/**
 * @brief Shortcut which combines the types
 * @ref DFL::Thread::SemGuard and @ref DFL::Thread::Semaphore.
 *
 * @ingroup Thread
 */
using ScopedSemGuard = SemGuard<Semaphore>;

}
}
