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
class RalChecker;

/**
 * @brief RAL checker job - runs 1 time every hour.
 *
 * @ingroup S31SdcCommon
 */
class RalCheckerJob: public Job
{
    public:
    RalCheckerJob(const DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>>& dispatcher, DFL::NotNull<std::shared_ptr<RalChecker>> ralChecker);
        void execute() override;
        std::string jobName() const override;

    private:
        std::weak_ptr<AsioDispatch::Dispatcher> m_dispatcher;
        DFL::NotNull<std::shared_ptr<RalChecker>> m_ralChecker;
};

}
