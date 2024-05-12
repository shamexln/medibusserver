#pragma once

#include <Framework/Log/Private/ExpImp.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/SystemClock.h>

#include <string>

namespace DFL
{
namespace Log
{
namespace Impl
{
DFL_LOG_EXPIMP Chrono::Minutes offsetUtcToLocal(
    Chrono::SystemClock::TimePoint tp);

struct DFL_LOG_EXPIMP Offset
{
    Offset() = default;
    explicit Offset(::DFL::Chrono::Minutes offset);

    bool m_isNegative{};
    ::DFL::Chrono::Hours m_hours{};
    ::DFL::Chrono::Minutes m_minutes{};
};

DFL_LOG_EXPIMP std::string toIso8601(const Offset& offset);
}
}
}
