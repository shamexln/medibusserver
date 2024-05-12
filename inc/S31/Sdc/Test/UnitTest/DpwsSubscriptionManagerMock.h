#pragma once

#include <S31/Sdc/Private/Client/DpwsSubscriptionOnRemoteDeviceObserver.h>
#include <S31/Sdc/Private/Client/DsoapClient/Subscriptions/DpwsSubscriptionManager.h>

namespace S31::Sdc::Test
{
using S31::Sdc::Impl::DpwsSubscriptionOnRemoteDeviceObserver;

/**
 * @brief Mock implementation of \ref S31::Sdc::Impl::DpwsSubscriptionManager.
 */
class DpwsSubscriptionManagerMock: public S31::Sdc::Impl::DpwsSubscriptionManager
{
    public:
        struct RemoteDevice
        {
            S31::Sdc::EndpointReference                           remoteDeviceEpr;
            Utils::WeakErrorHandler                               errorHandler;
            std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver> subscriptionObserver;
            Impl::SoapActions                                     mdibChangeReports;
        };

        void startMonitoringRemoteDevice(
                const S31::Sdc::EndpointReference&                     remoteDeviceEpr,
                S31::Sdc::Impl::Endpoint::Executor                     getServiceExecutor,
                S31::Sdc::Impl::Endpoint::Executor                     mdibUpdateExecutor,
                boost::optional<S31::Sdc::Impl::Endpoint::Executor>    setServiceExecutor,
                std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> reportProcessor,
                std::weak_ptr<Sdc::Impl::InvocationReportSubject>      invocationReportSubject,
                Utils::WeakErrorHandler                                errorHandler,
                std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver>  subscriptionObserver,
                const Impl::SoapActions&                               mdibChangeReports) override;

        void stopMonitoringRemoteDevice(const S31::Sdc::EndpointReference& remoteDeviceEpr) override;

        void stopMonitoring() override;

        std::vector<RemoteDevice>& startMonitoringMdibOfNodeCalls();

        std::vector<S31::Sdc::EndpointReference>& stopMonitoringMdibOfNodeCalls();

        std::shared_ptr<S31::Sdc::Impl::Report::ReportProcessor> reportProcessor() const
        {
            return m_reportProcessor.lock();
        }

    private:
        std::vector<RemoteDevice> m_startMonitoringMdibOfNodeCalls;
        std::vector<S31::Sdc::EndpointReference> m_stopMonitoringMdibOfNodeCalls;
        std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> m_reportProcessor;
};

inline void DpwsSubscriptionManagerMock::startMonitoringRemoteDevice(
        const S31::Sdc::EndpointReference& remoteDeviceEpr,
        S31::Sdc::Impl::Endpoint::Executor,
        S31::Sdc::Impl::Endpoint::Executor,
        boost::optional<S31::Sdc::Impl::Endpoint::Executor>,
        std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> reportProcessor,
        std::weak_ptr<Sdc::Impl::InvocationReportSubject>,
        Utils::WeakErrorHandler                               errorHandler,
        std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver> subscriptionObserver,
        const Impl::SoapActions&                              mdibChangeReports)
{
    m_reportProcessor = reportProcessor;
    m_startMonitoringMdibOfNodeCalls.push_back(
            {remoteDeviceEpr, std::move(errorHandler), std::move(subscriptionObserver), mdibChangeReports});
}

inline void DpwsSubscriptionManagerMock::stopMonitoringRemoteDevice(const S31::Sdc::EndpointReference& remoteDeviceEpr)
{
    m_stopMonitoringMdibOfNodeCalls.push_back(remoteDeviceEpr);
}

inline void DpwsSubscriptionManagerMock::stopMonitoring()
{
}

inline std::vector<DpwsSubscriptionManagerMock::RemoteDevice>& DpwsSubscriptionManagerMock::startMonitoringMdibOfNodeCalls()
{
    return m_startMonitoringMdibOfNodeCalls;
}

inline std::vector<S31::Sdc::EndpointReference>& DpwsSubscriptionManagerMock::stopMonitoringMdibOfNodeCalls()
{
    return m_stopMonitoringMdibOfNodeCalls;
}

}
