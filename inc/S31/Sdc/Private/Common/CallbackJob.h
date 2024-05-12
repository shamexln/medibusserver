#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <functional>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Job that executes a plain function callback.
 * @details Be aware that the function callback does not point to any invalid references, i.e.,
 *          use a lambda that does capture all variables by value.
 * @ingroup S31SdcCommon
 */
class CallbackJob: public Job
{
    public:
        using CallbackFunction = std::function<void(void)>;

        CallbackJob(const std::string& jobName,
                    CallbackFunction callback) :
                m_jobName(std::string("CallbackJob: ") + jobName),
                m_callback(std::move(callback))
        {
        }

        void execute() override
        {
            m_callback();
        }

        std::string jobName() const override
        {
            return m_jobName;
        }

    private:
        const std::string m_jobName;
        CallbackFunction m_callback;
};

}
