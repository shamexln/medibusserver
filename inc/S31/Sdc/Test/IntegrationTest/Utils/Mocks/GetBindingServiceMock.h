#pragma once

#include <S31/Sdc/Private/Common/DsoapCommon/WebServiceConstants.h>
#include <S31/Sdc/Private/Common/Messaging/SoapHeaderUtils.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapGetServiceBindingService.h>

namespace S31::Sdc::Impl::Test
{

/**
 * Simulate a binding service which is able to parse messages.
 */
class GetBindingServiceMock: public GetServiceBindingService
{
    public:
        int GetMdState(_msg__GetMdState*, _msg__GetMdStateResponse& response) override
        {
            response.MdState = std::make_shared<pm__MdState>();
            return SOAP_OK;
        }

        int GetContextStates(_msg__GetContextStates* /*request*/, _msg__GetContextStatesResponse& response) override
        {
            return SoapHeaderUtils::prepareReply(response.soap, WebServiceConstants::GET_CONTEXT_STATE_RESPONSE_ACTION);
        }

        int SetString(_msg__SetString*, _msg__SetStringResponse& response) override
        {
            response.InvocationInfo = std::make_shared<msg__InvocationInfo>();
            response.InvocationInfo->InvocationState = msg__InvocationState::Wait;
            return SOAP_OK;
        }

        int OperationInvokedReport(_msg__OperationInvokedReport* report) override
        {
            memset(report->soap->buf, 'a', sizeof(report->soap->buf));
            return soap_send_empty_response(report->soap, 202);
        }
};

}
