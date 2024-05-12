#pragma once

#include <S31/Sdc/Private/Device/DsoapDevice/ILocalEventing.h>
#include <S31/Sdc/Private/Device/SetService/SetOperationStateMachine.h>
#include <S31/SetService/Public/Device/ClientInformation.h>
#include <S31/SetService/Public/Device/DeviceTransaction.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>

namespace S31::Sdc::Impl
{

/**
 * @brief DSOAP implementation of the \ref SetService::DeviceTransaction.
 * @ingroup S31SdcDevice
 */
class DsoapDeviceTransaction: public SetService::DeviceTransaction
{
    public:
        DsoapDeviceTransaction(SetService::TransactionId transactionId,
                               DFL::Mdib::Handle operationHandle,
                               DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::ILocalEventing>> eventing,
                               DFL::NotNull<DFL::Mdib::LatestMdibSharedPtr> latestMdib,
                               Safety::Context safetyContext,
                               Safety::DualChannel dualChannel,
                               const SetService::InvocationSource& invocationSource, // NOLINT(modernize-pass-by-value)
                               const SetService::ClientInformation& clientInfo, // NOLINT(modernize-pass-by-value)
                               DFL::Mdib::ExtensionTypes serviceExtensions);

        SetService::TransactionId transactionId() const override;

        void sendInvocationReport(const SetService::InvocationReport& invocationReport) override;

        void sendInvocationReport(const DFL::Mdib::MdibVersion& mdibVersion, const SetService::InvocationReport& invocationReport) override;

        const SetService::InvocationSource& invocationSource() const override;

        Safety::Context safetyContext() const override;

        Safety::DualChannel dualChannel() const override;

        SetService::ClientInformation clientInformation() const override;

        const DFL::Mdib::ExtensionTypes& serviceExtensions() const override;

    private:
        SetService::TransactionId m_transactionId;
        DFL::Mdib::Handle m_operationHandle;
        DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::ILocalEventing>> m_eventing;
        DFL::NotNull<DFL::Mdib::LatestMdibSharedPtr> m_latestMdib;
        Safety::Context m_safetyContext;
        Safety::DualChannel m_dualChannel;
        std::vector<SetService::InvocationReport> m_invocationReports;
        Sdc::Impl::SetOperationStateMachine m_invocationStateMachine;
        SetService::InvocationSource m_invocationSource;
        SetService::ClientInformation m_clientInformation;
        DFL::Mdib::ExtensionTypes m_serviceExtensions;
};

}
