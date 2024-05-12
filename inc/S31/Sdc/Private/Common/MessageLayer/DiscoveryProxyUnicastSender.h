#pragma once

#include <S31/Sdc/Private/Common/MessageLayer/IOutgoingSender.h>
#include <S31/Sdc/Private/Common/MessageLayer/OutgoingUnicastMessageJob.h>
#include <S31/Utils/Public/Outcome.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
class CoreConfiguration;

namespace Sdc::Impl
{
class IScheduling;
class IOutgoingJobQueue;

/**
 * @brief Send WS-Discovery one-way messages as Http requests to a Discovery Proxy.
 * @details This class creates an @ref S31::Sdc::Impl::OutgoingUnicastMessageJob to transport
 * a WS-Discovery one-way message (hello or bye) provided to its @ref S31::Sdc::Impl::IOutgoingSender
 * interface. This class also provides retry scheduling, if a message fails to be delivered with
 * a non-fatal error.
 * @ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP DiscoveryProxyUnicastSender
    : public IOutgoingSender,
      public Utils::OutcomeConsumer<DiscoveryProxyUnicastSender, OutgoingUnicastMessageResult>,
      public std::enable_shared_from_this<DiscoveryProxyUnicastSender>
{
    public:
        DiscoveryProxyUnicastSender(
                DFL::NotNull<std::shared_ptr<IScheduling>>       scheduling,
                DFL::NotNull<std::shared_ptr<IOutgoingJobQueue>> jobQueue,
                DFL::NotNull<std::shared_ptr<CoreConfiguration>> configuration);

        /**
         * @brief Schedule an Http request to be sent after a delay.
         */
        void sendMessage(const CreateRequestBody& soapMessage, DFL::Chrono::Milliseconds delay) override;

        /**
         * @brief Send an Http request to the @ref S31::Sdc::Impl::IOutgoingJobQueue for delivery.
         */
        void sendMessage(const CreateRequestBody& soapMessage) override;

        /**
         * @brief Definition of retransmission delays used for retry scheduling.
         */
        static const std::array<DFL::Chrono::Seconds, 3> RetransmissionDelays;

    private:
        std::mutex m_mutex;
        HandlerPtr m_outgoingUnicastSenderHandler;
        std::weak_ptr<IScheduling> m_scheduling;
        std::weak_ptr<IOutgoingJobQueue> m_jobQueue;
        std::weak_ptr<S31::CoreConfiguration> m_configuration;

        HandlerPtr createOutgoingUnicastHandler();
};

}
}
