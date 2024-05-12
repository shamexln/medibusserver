#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <utility>

namespace S31::Sdc::Impl
{

class JobMock: public S31::Sdc::Job
{
    public:
        explicit JobMock(std::string name) :
                m_name(std::move(name))
        {
        }

        void execute() override
        {
        }

        std::string jobName() const override
        {
            return m_name;
        }
    private:
        std::string m_name;

};

}
