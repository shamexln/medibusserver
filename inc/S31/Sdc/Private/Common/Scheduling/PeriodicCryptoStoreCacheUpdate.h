#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <Framework/Chrono/Public/Duration.h>

#include <memory>

namespace S31::AsioDispatch
{
class Dispatcher;
}

namespace S31::Sdc::Impl
{

class PeriodicCryptoStoreCacheUpdate : public S31::Sdc::Job
{
public:
    PeriodicCryptoStoreCacheUpdate(std::weak_ptr<S31::AsioDispatch::Dispatcher> dispatcher, DFL::Chrono::Seconds updateInterval);

    void execute() override;

    std::string jobName() const override;

private:
    std::weak_ptr<AsioDispatch::Dispatcher> m_dispatcher;
    DFL::Chrono::Seconds       m_updateInterval;
};
}  // namespace S31::Sdc::Impl
