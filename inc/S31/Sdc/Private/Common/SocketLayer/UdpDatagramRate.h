#pragma once

#include <Framework/Chrono/Public/SteadyClock.h>

#include <cstddef>
#include <vector>

namespace S31::Sdc::Impl
{

/**
 * \brief Class to calculate UDP datagram rate for DOS detection.
 * \ingroup S31SdcCommonSocket
 */
class UdpDatagramRate
{
    public:
        /**
         * @param limit Max number of UDP datagrams per second
         */
        explicit UdpDatagramRate(std::size_t limit);

        /**
         * @brief Shall be called for each received UDP datagram to calculate the
         * incoming data rate.
         */
        void incomingUdpDatagram();

    private:
        void setDosState(bool dos);
        void dosStarted();
        void dosStopped();

        const std::size_t m_limit;
        std::vector<DFL::Chrono::SteadyClock::TimePoint> m_receiveTimeStamps;
        bool m_dosActive = false;
};

}
