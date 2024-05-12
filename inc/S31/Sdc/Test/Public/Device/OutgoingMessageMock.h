#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Private/Common/DsoapCommon/WebServiceConstants.h>
#include <S31/Sdc/Private/Common/MessageLayer/GsoapEpr.h>
#include <S31/Sdc/Private/Device/IOutgoingMessage.h>

#include <set>

namespace S31::Sdc::Test
{

/**
 * @ingroup S31SdcDevice
 */
class OutgoingMessageMock: public S31::Sdc::Impl::IOutgoingMessage
{
    public:
        using CallbackType = std::function<void(struct soap*, const S31::Sdc::Impl::GsoapEpr&)>;

        explicit OutgoingMessageMock(int msgId = 0, Impl::SoapActionView soapAction = Impl::SoapActionView{})
            : m_id(msgId)
            , m_soapAction{std::string{soapAction.get()}}
        {
        }

        explicit OutgoingMessageMock(CallbackType callback): m_callback(std::move(callback))
        {
        }

        void addFailingEndpoint(const std::string& endpoint)
        {
            m_failingEndpoints.insert(endpoint);
        }

        int sendMessage(struct soap* soapHandle, const S31::Sdc::Impl::GsoapEpr& endpoint) override
        {
            if (m_callback)
            {
                m_callback(soapHandle, endpoint);
            }
            const std::string address = endpoint.getAddress();
            if (m_failingEndpoints.count(address) > 0)
            {
                S31_STREAM_INFO_LOGGER("Test", "simulate send message failure with id ", m_id, " to endpoint ", address);
                return -1;
            }
            S31_STREAM_INFO_LOGGER("Test", "send message with id ", m_id, " to endpoint ", address);
            return 0;
        }

        std::string messageDescription() const override
        {
            return "OutgoingMessageMock";
        }

        const std::string& soapAction() const override
        {
            return m_soapAction;
        }

    private:
        int m_id = 0;
        std::set<std::string> m_failingEndpoints;
        CallbackType m_callback;
        std::string m_soapAction{Impl::WebServiceConstants::EPISODIC_CONTEXT_REPORT_ACTION};

};

}
