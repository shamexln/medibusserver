#pragma once

#include <Framework/Config/Public/Attributes.h>

#include <functional>
#include <utility>

namespace DFL
{
/**
 * @brief Executes given code when enclosing scope exits.
 *
 * @details
 * This functionality is extremely useful in two cases:
 * - cleaning up resources (RAII)
 * - rollback actions (strong-exception guarantee)
 *
 * @par
 * [RAII](https://en.cppreference.com/w/cpp/language/raii) (Resource Acquisition
 * Is Initialization) is a powerful idiom in c++. It allows for binding resource
 * acquisition and release to construction and destruction of a variable that
 * holds the resource. Example of such types are
 * [std::unique_ptr](https://en.cppreference.com/w/cpp/memory/unique_ptr) and
 * @ref DFL::Thread::LockGuard. But sometimes writing such types leads to very
 * specific classes with no reuse at all. This is where this class can be used.
 *
 * @par
 * It also can be used to keep a rollback action which is executed in case of a
 * failure to satisfy the [strong-exception
 * guarantee](https://en.wikipedia.org/wiki/Exception_safety). This class is
 * inspired by the
 * [scope-guard](https://tour.dlang.org/tour/en/gems/scope-guards) feature from
 * the [d-language](https://dlang.org). @c scope(failure) could be implemented
 * with the help of the c++17 function
 * [std::uncaught_exceptions](https://en.cppreference.com/w/cpp/error/uncaught_exception).
 * See rationale for that function
 * [here](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4152.pdf).
 *
 * @deprecated Use @ref DFL::Scope::ScopeExit instead.
 *
 * @ingroup Utils
 */
class DFL_ATTRIBUTE_DEPRECATED("use DFL::Scope::ScopeExit instead") ScopeExit
{
public:
    /**
     * @brief Keeps given function and delays call of it till destruction of
     * this object.
     *
     * @snippet Utils/Test/UnitTest/TestScopeExit.cpp Functions
     * @snippet Utils/Test/UnitTest/TestScopeExit.cpp Ctor
     */
    explicit ScopeExit(std::function<void()> f);
    /**
     * @brief Moves exit code from @c other to @c this and tells @c other to not
     * call its exit code anymore.
     *
     * @snippet Utils/Test/UnitTest/TestScopeExit.cpp MoveCtor
     */
    ScopeExit(ScopeExit&& other) noexcept;
    /**
     * @brief Dismisses execution of given code on exit of enclosing scope.
     *
     * This can be used to dismiss execution of a rollback action when the
     * enclosing scope has not been left early e.g. by a thrown exception. This
     * make code conform to the strong-exception guarantee.
     *
     * @snippet Utils/Test/UnitTest/TestScopeExit.cpp ScopeSuccess
     */
    void dismiss() noexcept;
    /**
     * @brief Executes given code if @ref DFL::ScopeExit::dismiss has not been
     * called.
     */
    ~ScopeExit() noexcept;

private:
    std::function<void()> m_func{};
    bool m_call{};
};
}

namespace DFL
{
inline ScopeExit::ScopeExit(std::function<void()> f)
    : m_func{std::move(f)}
    , m_call{true}
{}

inline ScopeExit::ScopeExit(ScopeExit&& other) noexcept
    : m_func{std::move(other.m_func)}
    , m_call{other.m_call}
{
    other.m_call = false;
}

inline void ScopeExit::dismiss() noexcept
{
    m_call = false;
}

inline ScopeExit::~ScopeExit() noexcept
{
    if (!m_call) return;
    try
    {
        m_func();
    }
    catch (...)
    {
    }
}
}
