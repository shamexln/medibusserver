#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::AsioDispatch
{
class Dispatcher;
}

namespace S31::Sdc::Impl
{
class SslCertChecker;

/**
 * @brief SSL certificate checker job run once a day.
 *
 * @ingroup S31SdcCommon
 */
class SslCertCheckerJob: public Job
{
public:
    SslCertCheckerJob(const DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>>& dispatcher, DFL::NotNull<std::shared_ptr<SslCertChecker>> certChecker);

    void execute() override;
    std::string jobName() const override;

private:
    std::weak_ptr<AsioDispatch::Dispatcher> m_dispatcher;
    DFL::NotNull<std::shared_ptr<SslCertChecker>> m_certChecker;
};

}
