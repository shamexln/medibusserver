#pragma once

#include <S31/History/Public/Service.h>
#include <S31/Sdc/Private/Device/History/HistorySubscribeHandler.h>
#include <S31/Sdc/Private/Device/IHostedServicePlugin.h>
#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingHandler.h>

#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>
#include <string>

namespace S31::Sdc::Impl
{
class HttpClient;
class IOutgoingJobQueue;

/**
 * @brief WS-Eventing device plug-in for history service.
 * @ingroup S31SdcDevice
 */
class HistoryEventingPlugin : public IHostedServicePlugin
{
public:
    HistoryEventingPlugin(
            std::weak_ptr<History::RequestInterface> historyService, std::weak_ptr<HttpClient> httpClient);

    // IHostedServicePlugin
    int dispatch(struct soap* soapHandle) override;

    std::string pluginName() const override;

private:
    DFL::NotNull<std::shared_ptr<HistorySubscribeHandler>> m_subscribeHandler;
    DFL::NotNull<std::shared_ptr<WSEventingHandler>>       m_eventingHandler;
};
}  // namespace S31::Sdc::Impl
