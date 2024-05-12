#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IOutgoingUdpResponder.h>

#include <memory>

namespace S31::Sdc::Impl
{
class IScheduling;
class ISoapContextPool;

/**
 * @brief Send given data to UDP endpoint.
 * @ingroup S31SdcCommonWebServices
 */
class OutgoingUdpResponder: public IOutgoingUdpResponder
{
    public:
        OutgoingUdpResponder(std::weak_ptr<IScheduling> scheduling,
                             std::weak_ptr<ISoapContextPool> soapContextPool);
        void sendUdpMessage(const std::string& soapOverUdpUri, const std::string& udpPayload) override;
        void sendUdpMessage(const std::string& soapOverUdpUri, const std::string& udpPayload, DFL::Chrono::Milliseconds delay) override;

    private:
        std::weak_ptr<IScheduling> m_scheduling;
        std::weak_ptr<ISoapContextPool> m_soapContextPool;
};

}
