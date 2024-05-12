#pragma once

#include <S31/Sdc/Private/Client/Endpoint/DpwsEndpoint.h>
#include <S31/Sdc/Private/Common/Messaging/IOutgoingJobQueue.h>
#include <S31/Sdc/Private/Common/Scheduling/IScheduling.h>
#include <S31/Sdc/Private/Discovery/IDpwsDiscoverySubject.h>
#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/S31CoreExImp.h>

#include <set>
#include <string>

namespace S31::Sdc::Impl::Endpoint
{

/**
 * @brief Maximum ResolveMatch messages that shall be processed.
 * @details Typically, a Resolve request results in at most one ResolveMatch message.
 *          However, if an irregular ResolveMatch is received in response to a Resolve request (possibly due to a spoofing attack),
 *          S31 is configured to continue the validation process and wait for other ResolveMatch responses, possibly establishing
 *          the desired connection in spite of the suspicious circumstances. The amount of ResolveMatch messages that are processed
 *          can be limited by MaxResolveMatches in \ref S31::Sdc::Impl::Endpoint::DpwsEndpointImpl "DpwsEndpointImpl".
 * @ingroup S31SdcClient
 */
using MaxResolveMatches = DFL::StrongTypedef<short, struct MaxResolveMatchesTag, DFL::Skill::Streamable>;

/**
 * @brief Default implementation of \ref DpwsEndpoint.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP DpwsEndpointImpl: public DpwsEndpoint
{
    public:
        /**
         * @brief Minimum constructor with default retry counters and delays.
         * @param endpointReference The (fixed) endpoint reference this instance represents.
         * @param supportedUriSchemes Defines case-insensitive URI schemes that are accepted for URLs on connection establishment (e.g., { "https", "http" })
         * @param outgoingJobQueue Job queue to execute outgoing HTTP requests.
         * @param scheduling Scheduling to execute delayed state machine events.
         * @param discoverySubject Used to send and receive Resolve and ResolveMatch messages.
         * @param priorityGroup Used to generate a delay before the first http connection.
         */
        DpwsEndpointImpl(const EndpointReference& endpointReference,
                         std::set<std::string> supportedUriSchemes,
                         std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue> outgoingJobQueue,
                         std::weak_ptr<S31::Sdc::Impl::IScheduling> scheduling,
                         std::weak_ptr<S31::Sdc::Impl::IDpwsDiscoverySubject> discoverySubject,
                         ConnectionPriorityGroup priorityGroup);

        ~DpwsEndpointImpl() override;

        /**
         * @brief Start listening to any validation activities.
         */
        void registerObserver(const std::weak_ptr<DpwsEndpointObserver>& observer) override;

        /**
         * @brief Stop listening to any validation activities.
         */
        void unregisterObserver(const std::weak_ptr<DpwsEndpointObserver>& observer) override;

        /**
         * @brief Starts validation of the DpwsEndpoint.
         */
        void validate() override;

    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
};

}
