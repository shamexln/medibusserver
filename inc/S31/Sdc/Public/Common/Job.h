#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Base/S31Only/Exception.h>
#include <S31/Log/Public/Logger.h>

#include <string>
#include <memory>

namespace S31::Sdc
{

/**
 * @brief Interface for %S31 jobs that have to be executed asynchronously from the \ref S31::Sdc::IDispatcher (%S31 main loop).
 *
 * @ingroup S31SdcCommon
 */
class S31_CORE_EXPIMP Job
{
    public:
        virtual ~Job() noexcept = default;

        /**
         * @brief Called to execute the job with a reference to itself.
         * @details This method may be overridden to support lifetime extension of a job for asynchronous completion. By
         * default it calls @ref execute() without reference to self.
         */
        virtual void execute(const std::shared_ptr<Job>& self);

        /**
         * @brief Job name is used for debugging/logging purposes only.
         */
        [[nodiscard]] virtual std::string jobName() const = 0;

    protected:
        /**
         * @brief Called to execute the job without a reference to itself.
         */
        virtual void execute();

};

inline void Job::execute(const std::shared_ptr<Job>&)
{
    // Default implementation is to execute the job without a self reference.
    // I.e. no lifetime extension for asynchronous callback is required.
    execute();
}

inline void Job::execute()
{
    // Derived class must implement either `execute(const std::shared_ptr<Job>&)` (if e.g. lifetime extension for
    // asynchronous callback is required), or this method.

    S31_STREAM_ERROR_LOGGER("Sdc", jobName(), " is missing execute implementation.");
    S31_THROW_EXCEPTION(S31::InternalResourceMissing, jobName() << " is missing execute implementation.");
}
}
