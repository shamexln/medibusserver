#pragma once

#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/DsoapCommon/SoapViewTypes.h>
#include <S31/Sdc/Private/Device/IOutgoingMessage.h>
#include <S31/Sdc/Private/Device/WS-Eventing/WsEventingTypes.h>

#include <memory>
#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{

/**
 * @brief Encapsulates an outgoing oneway HTTP message.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP OneWayMessage : public IOutgoingMessage
{
public:
    OneWayMessage(SoapActionView soapAction, std::string soapMessageBody);
    int sendMessage(struct soap* soapHandle, const S31::Sdc::Impl::GsoapEpr& endpoint) final;

    const std::string& soapMessageBody() const noexcept;

    const std::string& soapAction() const override;

    std::string messageDescription() const override;

    void completionTracker(std::shared_ptr<void> tracker);

    /**
     * @brief Send a one-way message over a gSOAP soap context and provides the gSOAP error code.
     */
    static int sendOneWayMessage(
            struct soap*                    soapHandle,
            const S31::Sdc::Impl::GsoapEpr& endpoint,
            SoapActionNtView                soapAction,
            SoapMessageBodyView             soapMessageBody);

private:
    const std::string m_soapAction;
    const std::string m_soapMessageBody;

    std::shared_ptr<void> m_completionTracker;
};

}  // namespace S31::Sdc::Impl
