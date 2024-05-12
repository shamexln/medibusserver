#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <functional>
#include <type_traits>

namespace S31::Sdc
{

/**
 * @brief Makes a function that takes ownership of the given job and executes the job if called.
 * @ingroup S31SdcCommon
 */
template <typename JobClass>
inline std::function<void(void)> executionFunction(DFL::NotNull<std::unique_ptr<JobClass>>&& job)
{
    static_assert(
            std::is_base_of_v<Job, JobClass>,
            "Class JobClass is not derived from S31::Sdc::Job");

    const std::shared_ptr<JobClass> sharedJob = std::move(job.get());
    auto func = [sharedJob]()
    {
        sharedJob->Job::execute(sharedJob);
    };
    return func;
}

}
