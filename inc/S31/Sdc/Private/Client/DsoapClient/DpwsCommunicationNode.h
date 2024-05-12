#pragma once

#include <S31/Safety/Public/Requirement.h>
#include <S31/Sdc/Private/Client/Metadata/IRemoteHostedServiceEndpoint.h>
#include <S31/Sdc/Private/Client/PortTypeExecutors.h>
#include <S31/Sdc/Private/Client/RemoteMdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Private/Client/Report/ReportProcessor.h>
#include <S31/Sdc/Private/Client/SetService/InvocationReportSubject.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Utils/Public/Errors.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>
#include <mutex>

namespace S31::Sdc
{
class RemoteDeviceMdibObserver;
namespace Impl
{
class IHostedServiceMetadata;
class IRemoteHostedServiceEndpoint;

/**
 * @brief   Implementation of \ref Sdc::RemoteDevice to host remote device access data.
 * @ingroup S31SdcClient
 */
class DpwsCommunicationNode: public Sdc::RemoteDevice,
                             public std::enable_shared_from_this<DpwsCommunicationNode>
{
        DFL_NOT_COPYABLE(DpwsCommunicationNode)

    public:
        DpwsCommunicationNode(const Sdc::EndpointReference& endpointReference, // NOLINT(modernize-pass-by-value)
                              Sdc::Impl::PortTypeExecutors portTypeExecutors,
                              const Sdc::DpwsDeviceMetadata& dpwsDeviceMetadata, // NOLINT(modernize-pass-by-value)
                              S31::Nomenclature::Credentials credentials,
                              DFL::NotNull<S31::Sdc::Impl::RemoteMdibAccessSharedPtr> remoteMdibAccess,
                              DFL::NotNull<std::shared_ptr<Sdc::Impl::InvocationReportSubject>> invocationReportSubject,
                              std::shared_ptr<SetService::OperationInvoker> operationInvoker,
                              std::shared_ptr<Sdc::LocalizationClient> localization);

        const S31::Sdc::EndpointReference& endpointReference() const override;
        Sdc::DpwsDeviceMetadata dpwsDeviceMetadata() const override;

        DFL::NotNull<S31::Sdc::MdibAccessSharedPtr> mdibAccess() const override;
        DFL::NotNull<std::shared_ptr<Sdc::Impl::InvocationReportSubject>> invocationReportSubject() const;
        std::shared_ptr<SetService::OperationInvoker> operationInvoker() const override;

        void registerObserver(const std::weak_ptr<Sdc::RemoteDeviceMdibObserver>& observer) override;
        void unregisterObserver(const std::weak_ptr<Sdc::RemoteDeviceMdibObserver>& observer) override;

        Sdc::LocalizationClientPtr localization() const override;

        S31::Nomenclature::Credentials credentials() const override;

        // -- deprecated
        DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> getMdibAccess() const override;

    private:
        const S31::Sdc::EndpointReference m_endpointReference;
        const S31::Sdc::Impl::PortTypeExecutors m_portTypeExecutors;
        const Sdc::DpwsDeviceMetadata m_dpwsDeviceMetadata;
        const S31::Nomenclature::Credentials m_credentials;

        DFL::NotNull<Sdc::Impl::RemoteMdibAccessSharedPtr> m_remoteMdibAccess;
        DFL::NotNull<std::shared_ptr<Sdc::Impl::InvocationReportSubject>> m_invocationReportSubject;
        std::shared_ptr<SetService::OperationInvoker> m_operationInvoker;

        std::mutex m_mutex;
        class MdibChangesBroker;
        std::shared_ptr<MdibChangesBroker> m_mdibChangesBroker;
        std::shared_ptr<Sdc::LocalizationClient> m_localization;
};

}
}
