#pragma once

#include <Framework/Chrono/Private/ExpImp.h>

namespace DFL
{
namespace Chrono
{
namespace Impl
{
class DFL_CHRONO_EXPIMP StopwatchState
{
public:
    void onStart() noexcept;
    void onStop() noexcept;
    bool running() const noexcept;

private:
    bool m_running{false};
};
}
}
}
