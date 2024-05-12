#pragma once

#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequest.h>
#include <S31/Utils/Public/Outcome.h>
#include <S31/S31CoreExImp.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Handle the error that occured while working with the soap context.
 * @details E.g. log the processing error.
 * @ingroup S31SdcCommonScheduling
 */
S31_CORE_EXPIMP void handleError(const soap* soap, const Utils::Error& error);

/**
 * @brief Base class template for SDC related jobs (i.e. HTPP/S request-response) that provide an @ref S31::Utils::Outcome.
 * @ingroup S31SdcCommonScheduling
 */
template <typename OutcomeResult>
class OutgoingBlockingHttpRequestWithOutcome:
        public OutgoingBlockingHttpRequest,
        protected Utils::OutcomeProvider<OutcomeResult>
{
    public:
        using OutcomeType = typename Utils::OutcomeProvider<OutcomeResult>::OutcomeType;

    protected:
        OutgoingBlockingHttpRequestWithOutcome(
                const typename Utils::OutcomeProvider<OutcomeResult>::OutcomeHandlerPtr& handler,
                const std::string& peerTransportAddress,
                RequiredPeerRoles requiredPeerRoles)
            : OutgoingBlockingHttpRequest(peerTransportAddress, std::move(requiredPeerRoles))
            , Utils::OutcomeProvider<OutcomeResult>(handler)
        {}

        OutgoingBlockingHttpRequestWithOutcome(
                const typename Utils::OutcomeProvider<OutcomeResult>::OutcomeHandlerPtr& handler,
                const S31::Sdc::Impl::GsoapEpr& epr,
                RequiredPeerRoles requiredPeerRoles)
            : OutgoingBlockingHttpRequest(epr, std::move(requiredPeerRoles))
            , Utils::OutcomeProvider<OutcomeResult>(handler)
        {}

        using Utils::OutcomeProvider<OutcomeResult>::currentError;

        void postProcessRequest() final
        {
            if (const auto error = currentError())
            {
                handleError(soapPtr(), *error);
            }
        }
};

}
