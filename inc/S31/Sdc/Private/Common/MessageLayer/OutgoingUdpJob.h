#pragma once

#include <S31/Sdc/Public/Common/Job.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{
class ISoapContextPool;

/**
 * @brief Sends the given UDP data to endpoint when executed.
 * @ingroup S31SdcCommonWebServices
 */
class OutgoingUdpJob: public Job
{
    public:
        OutgoingUdpJob(std::string soapOverUdpUri,
                       std::string udpPayload,
                       std::weak_ptr<ISoapContextPool> soapContextPool);

        void execute() override;

        std::string jobName() const override;

    private:
        std::string m_receiver;
        std::string m_payload;
        std::weak_ptr<ISoapContextPool> m_soapContextPool;

};

}
