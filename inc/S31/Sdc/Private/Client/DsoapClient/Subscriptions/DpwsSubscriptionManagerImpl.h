#pragma once

#include <S31/Sdc/Private/Client/DsoapClient/Jobs/WatchdogJob.h>
#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionManager.h>
#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionMonitor.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/S31CoreExImp.h>

#include <list>
#include <map>
#include <memory>
#include <mutex>

namespace S31::AsioDispatch
{
class Dispatcher;
}

namespace S31::Sdc::Impl
{
class ISoapContextPool;
class IEventingClient;

/**
 * @brief Default implementation of \ref DpwsSubscriptionManager.
 *
 * Manages the @ref DpwsSubscriptionMonitor "DpwsSubscriptionMonitors" (one for each remote device).
 *
 * The monitors are created with @ref startMonitoringRemoteDevice() and destroyed with
 * @ref stopMonitoringRemoteDevice().
 *
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP DpwsSubscriptionManagerImpl:
        public DpwsSubscriptionManager,
        public Utils::OutcomeConsumer<DpwsSubscriptionManagerImpl, WatchdogJobResult>,
        public std::enable_shared_from_this<DpwsSubscriptionManagerImpl>

{
    public:
        DpwsSubscriptionManagerImpl(DFL::NotNull<std::shared_ptr<Sdc::Impl::IEventingClient>> eventing,
                                    const DFL::NotNull<std::shared_ptr<AsioDispatch::Dispatcher>>& dispatcher,
                                    DFL::Chrono::Milliseconds timeOutDuration);

        void startMonitoringRemoteDevice(
                const S31::Sdc::EndpointReference&                     remoteDeviceEpr,
                S31::Sdc::Impl::Endpoint::Executor                     getServiceExecutor,
                S31::Sdc::Impl::Endpoint::Executor                     mdibUpdateExecutor,
                boost::optional<S31::Sdc::Impl::Endpoint::Executor>    setServiceExecutor,
                std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> reportProcessor,
                std::weak_ptr<Sdc::Impl::InvocationReportSubject>      invocationReportSubject,
                Utils::WeakErrorHandler                                errorHandler,
                std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver>  subscriptionObserver,
                const SoapActions&                                     mdibChangeReports) override;

        void stopMonitoringRemoteDevice(const S31::Sdc::EndpointReference& remoteDeviceEpr) override;

        void stopMonitoring() override;

    private:
        void initWatchdogJob();
        void startWatchdogJob();
        void cleanupUnsubscribingMonitors();
        void checkAllSubscriptions();

        DFL::NotNull<std::shared_ptr<Sdc::Impl::IEventingClient>> m_eventingClient;
        std::weak_ptr<AsioDispatch::Dispatcher> m_dispatcher;

        std::mutex m_monitorMutex;
        std::map<std::string, DFL::NotNull<std::shared_ptr<DpwsSubscriptionMonitor>>> m_activeMonitors;
        std::list<DFL::NotNull<std::shared_ptr<DpwsSubscriptionMonitor>>> m_unsubscribingMonitors;
        HandlerPtr m_watchdogHandler;
        DFL::Chrono::Milliseconds m_timeOutDuration;
};

}
