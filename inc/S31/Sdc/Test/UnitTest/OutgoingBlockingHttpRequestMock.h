#pragma once

#include <S31/Sdc/Private/Common/Messaging/OutgoingBlockingHttpRequestWithOutcome.h>

namespace S31::Sdc::Test
{

/**
 * @brief Mock for an \ref S31::Sdc::Impl::OutgoingBlockingHttpRequest that can be used to retrieve custom outcome.
 */
template<class T_Result>
class OutgoingBlockingHttpRequestMock: public S31::Sdc::Impl::OutgoingBlockingHttpRequestWithOutcome<T_Result>
{
    public:
        using ResultType = T_Result;
        using OutcomeHandlerPtr = Utils::OutcomeTypes::HandlerPtr<ResultType>;

        OutgoingBlockingHttpRequestMock(const OutcomeHandlerPtr& handler);

        using Utils::OutcomeProvider<T_Result>::setOutcomeResult;
        using Utils::OutcomeProvider<T_Result>::setOutcomeError;

        void processRequest() override;

        std::string jobName() const override;
};

template<class T_Result>
inline OutgoingBlockingHttpRequestMock<T_Result>::OutgoingBlockingHttpRequestMock(const OutcomeHandlerPtr& handler) :
        S31::Sdc::Impl::OutgoingBlockingHttpRequestWithOutcome<T_Result>(
            handler, "http://anyUri", S31::Sdc::Impl::RequiredPeerRoles{DFL::Oids{}})
{
}

template<class T_Result>
inline void OutgoingBlockingHttpRequestMock<T_Result>::processRequest()
{
}

template<class T_Result>
inline std::string OutgoingBlockingHttpRequestMock<T_Result>::jobName() const
{
    return "OutgoingBlockingHttpRequestMock";
}

}
