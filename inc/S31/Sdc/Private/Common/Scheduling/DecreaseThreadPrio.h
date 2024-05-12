#pragma once

#include <Framework/Config/Public/Config.h>

#ifdef DFL_CONFIG_OS_VXWORKS
#include <taskLib.h>
#include <optional>
#endif

namespace S31::Sdc::Impl
{
/**
 * @brief During lifetime the own thread prio is decreased by one.
 * @details
 * In the destructor the old thread priority is restored.
 * Right now it is only available for VxWorks. It is unclear if this is ever needed for other toolchains.
 */
class DecreaseThreadPrio
{
public:
    [[maybe_unused]] DecreaseThreadPrio();
    DecreaseThreadPrio(const DecreaseThreadPrio& rhs) = delete;
    DecreaseThreadPrio& operator=(const DecreaseThreadPrio& rhs) = delete;
    ~DecreaseThreadPrio();

private:
#ifdef DFL_CONFIG_OS_VXWORKS
    const TASK_ID m_taskId;
    std::optional<int> m_initialPriority{};
#endif
};
}
