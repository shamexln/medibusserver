#pragma once

#include <Framework/Utils/Private/Scope.h>

#include <exception>
#include <type_traits>
#include <utility>

namespace DFL::Scope
{
/**
 * @brief Wraps a function and invokes it on exiting the scope normally.
 *
 * A @c ScopeSuccess may be either active, i.e. calls its exit function on
 * destruction, or inactive, i.e. does nothing on destruction. A @c ScopeSuccess
 * is active after constructed from an exit function.
 *
 * A @c ScopeSuccess can become inactive by calling @c release()
 * on it either manually or automatically (by the move constructor). An inactive
 * @c ScopeSuccess may also be obtained by initializing with another inactive
 * @c ScopeSuccess. Once a @c ScopeSuccess is inactive, it cannot become active
 * again.
 *
 * A @c ScopeSuccess effectively holds an @c ExitFunc and a bool flag indicating
 * if it is active, along with a counter of uncaught exceptions used for
 * detecting whether the destructor is called during stack unwinding.
 *
 * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeSuccessOnSuccess
 *
 * @tparam ExitFunc Type of the exit function.
 *
 * @ingroup Utils
 */
template <class ExitFunc>
class [[maybe_unused]] ScopeSuccess : private Impl::ScopeBase<ExitFunc>
{
public:
    /**
     * @brief Creates a @c ScopeSuccess from a function.
     *
     * Initializes the exit function with given function.
     * Initializes the counter of uncaught exceptions with @c
     * std::uncaught_exceptions().
     * The constructed @c ScopeSuccess is active.
     */
    explicit ScopeSuccess(ExitFunc f)
        : Impl::ScopeBase<ExitFunc>{std::move(f)}
    {
    }
    /**
     * @brief Creates a @c ScopeSuccess from another @c ScopeSuccess.
     *
     * Initializes the stored @c ExitFunc with the one in other, and
     * initializes the counter of uncaught exceptions with the one in other.
     * The constructed @c ScopeSuccess is active if and only if other is active
     * before the construction. After successful move construction,
     * @c other.release() is called and other becomes inactive.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeSuccessMoveOnSuccess
     *
     * @throws Throws any exception thrown by move ctor of @c ExitFunc.
     */
    ScopeSuccess(ScopeSuccess&& other) noexcept(
        std::is_nothrow_move_constructible_v<ExitFunc>)
        : Impl::ScopeBase<ExitFunc>{std::move(other)}
    {
    }
    /**
     * @brief Calls the exit function if the result of
     * @c std::uncaught_exceptions() is less than or equal to
     * the counter of uncaught exceptions and the @c ScopeSuccess is active.
     *
     * Whether the destructor is called on stack unwinding
     * can be detected by the comparison of the result of
     * std::uncaught_exceptions() and the counter of uncaught exceptions
     * in the @c ScopeSuccess. This class is permitted to throw.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeSuccessExceptionNeutral
     *
     * @throws Throws any exception thrown by calling the exit function.
     */
    // NOLINTNEXTLINE(bugprone-exception-escape)
    ~ScopeSuccess() noexcept(noexcept(std::declval<ExitFunc&>()()))
    {
        if (!Impl::ScopeBase<ExitFunc>::m_call) return;
        if (std::uncaught_exceptions() <=
            Impl::ScopeBase<ExitFunc>::m_excptCount)
        {
            Impl::ScopeBase<ExitFunc>::m_func();
        }
    }
    /**
     * @brief Makes the @c ScopeSuccess inactive.
     *
     * Once inactive, it cannot become active again, and will not call its exit
     * function on destruction. @c release() may be either manually called or
     * automatically called by its move ctor.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeSuccessRelease
     */
    void release() noexcept
    {
        Impl::ScopeBase<ExitFunc>::release();
    }
};
/**
 * @brief Wraps a function and invokes it on exiting the scope through an
 * exception.
 *
 * A @c ScopeFail may be either active, i.e. calls its exit function on
 * destruction, or inactive, i.e. does nothing on destruction. A @c ScopeFail is
 * active after constructed from an exit function.
 *
 * A @c ScopeFail can become inactive by calling @c release() on it either
 * manually or automatically (by the move constructor). An inactive @c ScopeFail
 * may also be obtained by initializing with another inactive @c ScopeFail. Once
 * a @c ScopeFail is inactive, it cannot become active again.
 *
 * A @c ScopeFail effectively holds an @c ExitFunc and a bool flag indicating if
 * it is active, along with a counter of uncaught exceptions used for detecting
 * whether the destructor is called during stack unwinding.
 *
 * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeFailOnFailure
 *
 * @tparam ExitFunc Type of the exit function.
 *
 * @ingroup Utils
 */
template <class ExitFunc>
class [[maybe_unused]] ScopeFail : private Impl::ScopeBase<ExitFunc>
{
public:
    /**
     * @brief Creates a @c ScopeFail from a function.
     *
     * Initializes the exit function with given function.
     * Initializes the counter of uncaught exceptions with @c
     * std::uncaught_exceptions().
     * The constructed @c ScopeFail is active.
     */
    explicit ScopeFail(ExitFunc f)
        : Impl::ScopeBase<ExitFunc>{std::move(f)}
    {
    }
    /**
     * @brief Creates a @c ScopeFail from another @c ScopeFail.
     *
     * Initializes the stored @c ExitFunc with the one in other, and
     * initializes the counter of uncaught exceptions with the one in other.
     * The constructed @c ScopeFail is active if and only if other is active
     * before the construction. After successful move construction,
     * @c other.release() is called and other becomes inactive.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeFailMoveOnFailure
     *
     * @throws Throws any exception thrown by move ctor of @c ExitFunc.
     */
    ScopeFail(ScopeFail&& other) noexcept(
        std::is_nothrow_move_constructible_v<ExitFunc>)
        : Impl::ScopeBase<ExitFunc>{std::move(other)}
    {
    }
    /**
     * @brief Calls the exit function if the result of
     * @c std::uncaught_exceptions() is greater than
     * the counter of uncaught exceptions and the @c ScopeFail is active.
     *
     * Whether the destructor is called on stack unwinding
     * can be detected by the comparison of the result of
     * std::uncaught_exceptions() and the counter of uncaught exceptions
     * in the @c ScopeFail.
     * If the exit function throws its exception is swallowed.
     * This is a major difference to @c std::scope_fail from C++23.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeFailExceptionIsSwallowed
     */
    ~ScopeFail() noexcept
    {
        if (!Impl::ScopeBase<ExitFunc>::m_call) return;
        if (std::uncaught_exceptions() >
            Impl::ScopeBase<ExitFunc>::m_excptCount)
        {
            try
            {
                Impl::ScopeBase<ExitFunc>::m_func();
            }
            catch (...)
            {
            }
        }
    }
    /**
     * @brief Makes the @c ScopeFail inactive.
     *
     * Once inactive, it cannot become active again, and will not call its exit
     * function on destruction. @c release() may be either manually called or
     * automatically called by its move ctor.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeFailRelease
     */
    void release() noexcept
    {
        Impl::ScopeBase<ExitFunc>::release();
    }
};
/**
 * @brief Wraps a function and invokes it on exiting the scope.
 *
 * A @c ScopeExit may be either active, i.e. calls its exit function on
 * destruction, or inactive, i.e. does nothing on destruction. A @c ScopeExit is
 * active after constructed from an exit function.
 *
 * A @c ScopeExit can become inactive by calling @c release() on it either
 * manually or automatically (by the move constructor). An inactive @c ScopeExit
 * may also be obtained by initializing with another inactive @c ScopeExit. Once
 * a @c ScopeExit is inactive, it cannot become active again.
 *
 * A @c ScopeExit effectively holds an @c ExitFunc and a bool flag indicating if
 * it is active.
 *
 * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeExitOnSuccess
 *
 * @tparam ExitFunc Type of the exit function.
 *
 * @ingroup Utils
 */
template <class ExitFunc>
class [[maybe_unused]] ScopeExit : private Impl::ScopeBase<ExitFunc>
{
public:
    /**
     * @brief Creates a @c ScopeExit from a function.
     *
     * Initializes the exit function with given function.
     * The constructed @c ScopeExit is active.
     */
    explicit ScopeExit(ExitFunc f)
        : Impl::ScopeBase<ExitFunc>{std::move(f)}
    {
    }
    /**
     * @brief Creates a @c ScopeExit from another @c ScopeExit.
     *
     * Initializes the stored @c ExitFunc with the one in other.
     * The constructed @c ScopeExit is active if and only if other is active
     * before the construction. After successful move construction,
     * @c other.release() is called and other becomes inactive.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeExitMoveOnSuccess
     *
     * @throws Throws any exception thrown by move ctor of @c ExitFunc.
     */
    ScopeExit(ScopeExit&& other) noexcept(
        std::is_nothrow_move_constructible_v<ExitFunc>)
        : Impl::ScopeBase<ExitFunc>{std::move(other)}
    {
    }
    /**
     * @brief Calls the exit function if @c ScopeExit is active otherwise not.
     *
     * If the exit function throws its exception is swallowed.
     * This is a major difference to @c std::scope_exit from C++23.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeExitOnFailExceptSwallowed
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeExitOnSuccExceptSwallowed
     *
     * @throws Throws any exception thrown by calling the exit function.
     */
    ~ScopeExit() noexcept
    {
        if (!Impl::ScopeBase<ExitFunc>::m_call) return;
        try
        {
            Impl::ScopeBase<ExitFunc>::m_func();
        }
        catch (...)
        {
        }
    }
    /**
     * @brief Makes the @c ScopeExit inactive.
     *
     * Once inactive, it cannot become active again, and will not call its exit
     * function on destruction. @c release() may be either manually called or
     * automatically called by its move ctor.
     *
     * @snippet Utils/Test/UnitTest/TestScope.cpp ScopeExitRelease
     */
    void release() noexcept
    {
        Impl::ScopeBase<ExitFunc>::release();
    }
};
}
