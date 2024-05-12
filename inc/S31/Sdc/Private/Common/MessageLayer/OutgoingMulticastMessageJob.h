#pragma once

#include <S31/Sdc/Private/Common/Http/CreateRequestBody.h>
#include <S31/Sdc/Public/Common/Job.h>

#include <memory>

namespace S31::Sdc::Impl
{
class IUdpSocketAccess;
class NetworkInterfaceFilter;

/**
 * @brief Outgoing WS-Discovery multicast message.
 * @ingroup S31SdcCommonWebServices
 */
class OutgoingMulticastMessageJob: public Job
{
    public:
        OutgoingMulticastMessageJob(S31::Sdc::Impl::CreateRequestBody soapMessageCreate,
                                    std::weak_ptr<IUdpSocketAccess> udpSocketAccess,
                                    std::weak_ptr<NetworkInterfaceFilter> networkInterfaceFilter);

        void execute() override;

        std::string jobName() const override;

    private:
        std::weak_ptr<IUdpSocketAccess> m_udpSocketAccess;
        std::weak_ptr<NetworkInterfaceFilter> m_networkInterfaceFilter;
        S31::Sdc::Impl::CreateRequestBody m_soapMessageCreate;
};

}
