#pragma once

#include <S31/Sdc/Private/Client/DpwsSubscriptionOnRemoteDeviceObserver.h>
#include <S31/Sdc/Private/Client/Report/ReportProcessor.h>
#include <S31/Sdc/Private/Client/SetService/InvocationReportSubject.h>
#include <S31/Sdc/Private/Client/WS-Eventing/SoapAction.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Utils/Public/Errors.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc::Impl
{

/**
 * @brief Offers functionality to start and stop subscription monitors of all connected remote devices.
 * @ingroup S31SdcClient
 */
class DpwsSubscriptionManager
{
    public:
        virtual ~DpwsSubscriptionManager() noexcept = default;

        /**
         * @brief Starts monitoring of a remote device.
         */
        virtual void startMonitoringRemoteDevice(
                const S31::Sdc::EndpointReference&                     remoteDeviceEpr,
                S31::Sdc::Impl::Endpoint::Executor                     getServiceExecutor,
                S31::Sdc::Impl::Endpoint::Executor                     mdibUpdateExecutor,
                boost::optional<S31::Sdc::Impl::Endpoint::Executor>    setServiceExecutor,
                std::weak_ptr<S31::Sdc::Impl::Report::ReportProcessor> reportProcessor,
                std::weak_ptr<Sdc::Impl::InvocationReportSubject>      invocationReportSubject,
                Utils::WeakErrorHandler                                errorHandler,
                std::weak_ptr<DpwsSubscriptionOnRemoteDeviceObserver>  subscriptionObserver,
                const SoapActions&                                     mdibChangeReports) = 0;

        /**
         * @brief Stops monitoring of a remote device.
         * @details Unsubscribes all running subscriptions asynchronously.
         */
        virtual void stopMonitoringRemoteDevice(const S31::Sdc::EndpointReference& remoteDeviceEpr) = 0;

        /**
         * @brief Stops monitoring of all remote devices.
         */
        virtual void stopMonitoring() = 0;
};

}
