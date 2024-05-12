#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IOutgoingSender.h>

#include <memory>

namespace S31::Sdc::Impl
{
class IScheduling;
class IUdpSocketAccess;
class NetworkInterfaceFilter;

/**
 * @brief Stores corresponding jobs in job queue.
 * @details For each outgoing multicast message a job for sending the message and
 * an additional retransmission job is scheduled as well.
 * @ingroup S31SdcCommonWebServices
 */
class OutgoingMulticastSender: public IOutgoingSender
{
    public:
        OutgoingMulticastSender(std::weak_ptr<IScheduling> scheduling,
                                std::weak_ptr<IUdpSocketAccess> udpSocketAccess,
                                std::weak_ptr<NetworkInterfaceFilter> networkInterfaceFilter);

        void sendMessage(const CreateRequestBody& soapMessage) override;
        void sendMessage(const CreateRequestBody& soapMessage, DFL::Chrono::Milliseconds initialDelay) override;

    private:
        std::weak_ptr<IScheduling> m_scheduling;
        std::weak_ptr<IUdpSocketAccess> m_udpSocketAccess;
        std::weak_ptr<NetworkInterfaceFilter> m_networkInterfaceFilter;
};

}
