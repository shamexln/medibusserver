#pragma once

#include <exception>
#include <type_traits>
#include <utility>

namespace DFL::Scope::Impl
{
template <class ExitFunc>
class ScopeBase
{
protected:
    explicit ScopeBase(ExitFunc f);
    ScopeBase(ScopeBase&& other) noexcept(
        std::is_nothrow_move_constructible_v<ExitFunc>);
    void release() noexcept;
    ExitFunc m_func;
    bool m_call{true};
    int m_excptCount{std::uncaught_exceptions()};
};

template <class ExitFunc>
inline ScopeBase<ExitFunc>::ScopeBase(ExitFunc f)
    : m_func{std::move(f)}
{
}

template <class ExitFunc>
inline ScopeBase<ExitFunc>::ScopeBase(ScopeBase&& other) noexcept(
    std::is_nothrow_move_constructible_v<ExitFunc>)
    : m_func{std::move(other.m_func)}
    , m_call{other.m_call}
    , m_excptCount{other.m_excptCount}
{
    other.release();
}

template <class ExitFunc>
inline void ScopeBase<ExitFunc>::release() noexcept
{
    m_call = false;
}
}
