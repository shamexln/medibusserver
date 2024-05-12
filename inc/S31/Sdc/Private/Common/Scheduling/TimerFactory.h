#pragma once

#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Utils/S31Only/TimerFactory.h>

#include <Framework/Utils/Public/NotNull.h>

namespace S31::Sdc::Impl
{
class TimerFactory : public Utils::TimerFactory
{
public:
    explicit TimerFactory(DFL::NotNull<std::shared_ptr<IScheduling>> scheduling);

    DFL::NotNull<std::unique_ptr<Utils::Timer>>
    createTimer(std::function<void()> timeoutFunc) override;

private:
    DFL::NotNull<std::shared_ptr<IScheduling>> m_scheduling;

};
}  // namespace S31::Sdc::Impl
