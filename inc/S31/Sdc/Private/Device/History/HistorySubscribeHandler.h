#pragma once

#include <S31/History/Public/Service.h>
#include <S31/Sdc/Private/Device/History/HistorySubscription.h>
#include <S31/Sdc/Private/Device/WS-Eventing/WSEventingHandler.h>

#include <map>
#include <memory>
#include <mutex>
#include <string>

namespace S31::Sdc::Impl
{
class HistorySubscribeHandler : public SubscribeHandler,
                                public std::enable_shared_from_this<HistorySubscribeHandler>,
                                public NotificationResultHandler
{
public:
    explicit HistorySubscribeHandler(std::weak_ptr<History::RequestInterface> weakHistoryService)
        : m_weakHistoryService{std::move(weakHistoryService)}
    {
    }

    void setHandler(const DFL::NotNull<std::shared_ptr<WSEventingHandler>>& handler)
    {
        m_eventingHandler = handler.get();
    }

    // SubscribeHandler
    Result subscribe(const RequestView& request) override;

    void subscriptionEnded(const EndData& endData) override;

    // NotificationResultHandler
    void notificationSucceeded(SubscriptionIdView subscriptionId) override;

    void notificationFailed(SubscriptionIdView subscriptionId, Reason reason, std::string_view detailMessage) override;

private:
    void sendHistoricReport(std::string_view subscriptionId);
    void noMoreReportsToSend(std::string_view subscriptionId);

    std::weak_ptr<History::RequestInterface> m_weakHistoryService;
    std::weak_ptr<WSEventingHandler>         m_eventingHandler;

    mutable std::mutex m_mutex;
    using SubscriptionId = std::string;
    std::map<SubscriptionId, DFL::NotNull<std::shared_ptr<HistorySubscription>>, std::less<>> m_subscriptions;
};
}  // namespace S31::Sdc::Impl
