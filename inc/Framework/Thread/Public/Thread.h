#pragma once

#include <Framework/Thread/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>

#include <string>

namespace DFL
{
namespace Thread
{
class Id;
namespace ThisThread
{
/**
 * @brief Blocks the execution of the current thread for the specified duration.
 * @param ms Duration to sleep
 * @throws std::runtime_error Throws in case of numeric conversion error and
 *                            whenever the called OS functions fail.
 * @ingroup Thread
 */
DFL_THREAD_EXPIMP void sleepFor(const Chrono::Milliseconds& ms);
/**
 * @brief Returns the id of this current context.
 *
 * @ingroup Thread
 */
DFL_THREAD_EXPIMP Thread::Id id();
/**
 * @brief Same as calling @ref DFL::Thread::name(const DFL::Thread::Id&)
 * with @ref DFL::Thread::ThisThread::id().
 *
 * @snippet Thread/Test/UnitTest/TestThread.cpp ThreadName
 *
 * @ingroup Thread
 */
DFL_THREAD_EXPIMP std::string name();
}
}
}

#include <Framework/Thread/Private/ThreadImpl.h>

namespace DFL
{
namespace Thread
{
/**
 * @brief Type reqresenting the id of a thread as specified in c++11.
 *
 * Can be stored in containers. Even as key in a std::map.
 *
 * @ingroup Thread
 */
class DFL_THREAD_EXPIMP Id
{
private:
    using IdType = Impl::Id;
    IdType m_id{0};
    Id(IdType nativeId);
    friend Id DFL_THREAD_EXPIMP ThisThread::id();
public:
    /**
     * @brief Represents "not a thread".
     */
    Id() = default;
    /**
     * @brief Returns the os specific natvive value.
     */
    IdType native() const;
};
/**
 * @brief Comparison operators for @ref DFL::Thread::Id.
 * @{
 */
bool DFL_THREAD_EXPIMP operator==(const Id& lhs, const Id& rhs);
bool DFL_THREAD_EXPIMP operator!=(const Id& lhs, const Id& rhs);
bool DFL_THREAD_EXPIMP operator< (const Id& lhs, const Id& rhs);
bool DFL_THREAD_EXPIMP operator> (const Id& lhs, const Id& rhs);
bool DFL_THREAD_EXPIMP operator<=(const Id& lhs, const Id& rhs);
bool DFL_THREAD_EXPIMP operator>=(const Id& lhs, const Id& rhs);
/** @} */
/**
 * @brief Returns the name of the thread corresponding to the given id.
 *
 * Some operating systems e.g. windows do not provide
 * a name for threads. In these cases the id is converted to a string
 * and then returned by this function.
 * @snippet Thread/Test/UnitTest/TestThread.cpp ThreadName
 *
 * @ingroup Thread
 */
DFL_THREAD_EXPIMP std::string name(const Id& id);
}
}
