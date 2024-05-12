#pragma once

#include <S31/Sdc/Public/Common/Job.h>
#include <S31/Utils/Public/Outcome.h>

#include <memory>

namespace S31::Sdc::Impl
{

struct WatchdogJobResult
{
};

/**
 * \brief Watch dog job that re-triggers the callback periodically.
 *
 * \ingroup S31SdcClient
 */
class WatchdogJob:
            public Job,
            protected Utils::OutcomeProvider<WatchdogJobResult>
{
    public:
        explicit WatchdogJob(const OutcomeHandlerPtr& handler);

        void execute() override;
        std::string jobName() const override;
};

}
