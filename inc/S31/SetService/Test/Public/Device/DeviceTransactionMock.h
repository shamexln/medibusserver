#pragma once

#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>
#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Common/TransactionId.h>
#include <S31/SetService/Public/Device/ClientInformation.h>
#include <S31/SetService/Public/Device/DeviceTransaction.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibFactory.h>
#include <Framework/Utils/Public/NotNull.h>

#include <vector>

namespace S31::SetService::Test
{

/**
 * @brief Mock class to fetch invocation reports that have been sent by a device transaction.
 * @ingroup S31SetServiceDevice
 */
class DeviceTransactionMock: public DeviceTransaction
{
    public:
        explicit DeviceTransactionMock(TransactionId transactionId);

        DeviceTransactionMock(TransactionId transactionId,
                              const Safety::Context& safetyContext,
                              const Safety::DualChannel& dualChannel,
                              const SetService::ClientInformation& clientInfo,
                              const DFL::Mdib::ExtensionTypes& serviceExtensions);

        TransactionId transactionId() const override;

        void sendInvocationReport(const InvocationReport& invocationReport) override;

        void sendInvocationReport(const DFL::Mdib::MdibVersion& mdibVersion, const InvocationReport& invocationReport) override;

        const InvocationSource& invocationSource() const override;

        const std::vector<InvocationReport>& sentInvocationReports() const;

        Safety::Context safetyContext() const override;

        Safety::DualChannel dualChannel() const override;

        SetService::ClientInformation clientInformation() const override;

        const DFL::Mdib::ExtensionTypes& serviceExtensions() const override;

        boost::optional<DFL::Mdib::MdibVersion> lastReportMdibVersion() const;

    private:
        TransactionId m_transactionId;
        Safety::Context m_safetyContext;
        Safety::DualChannel m_dualChannel;
        std::vector<InvocationReport> m_invocationReports;
        InvocationSource m_invocationSource;
        SetService::ClientInformation m_clientInformation;
        boost::optional<DFL::Mdib::MdibVersion> m_mdibVersion;
        DFL::Mdib::ExtensionTypes m_serviceExtensions;
};

inline DeviceTransactionMock::DeviceTransactionMock(TransactionId transactionId) :
        m_transactionId(transactionId),
        m_invocationSource(InvocationSource(DFL::Mdib::Root(DFL::Mdib::Uri("mock-root")), DFL::Mdib::Extension(DFL::Locale::Utf8("mock-extension")))),
        m_clientInformation()
{
}

inline DeviceTransactionMock::DeviceTransactionMock(TransactionId transactionId,
                                                    const Safety::Context& safetyContext,
                                                    const Safety::DualChannel& dualChannel,
                                                    const SetService::ClientInformation& clientInfo,
                                                    const DFL::Mdib::ExtensionTypes& serviceExtensions) :
        m_transactionId(transactionId),
        m_safetyContext(safetyContext),
        m_dualChannel(dualChannel),
        m_invocationSource(InvocationSource(DFL::Mdib::Root(DFL::Mdib::Uri("mock-root")), DFL::Mdib::Extension(DFL::Locale::Utf8("mock-extension")))),
        m_clientInformation(clientInfo),
        m_serviceExtensions(serviceExtensions)
{
}

inline TransactionId DeviceTransactionMock::transactionId() const
{
    return m_transactionId;
}

inline void DeviceTransactionMock::sendInvocationReport(const InvocationReport& invocationReport)
{
    m_invocationReports.push_back(invocationReport);
}

inline void DeviceTransactionMock::sendInvocationReport(const DFL::Mdib::MdibVersion& mdibVersion, const InvocationReport& invocationReport)
{
    m_invocationReports.push_back(invocationReport);
    m_mdibVersion = mdibVersion;
}

inline const InvocationSource& DeviceTransactionMock::invocationSource() const
{
    return m_invocationSource;
}

inline const std::vector<InvocationReport>& DeviceTransactionMock::sentInvocationReports() const
{
    return m_invocationReports;
}

inline Safety::Context DeviceTransactionMock::safetyContext() const
{
    return m_safetyContext;
}

inline Safety::DualChannel DeviceTransactionMock::dualChannel() const
{
    return m_dualChannel;
}

inline SetService::ClientInformation DeviceTransactionMock::clientInformation() const
{
    return m_clientInformation;
}

inline const DFL::Mdib::ExtensionTypes& DeviceTransactionMock::serviceExtensions() const
{
    return m_serviceExtensions;
}

inline boost::optional<DFL::Mdib::MdibVersion> DeviceTransactionMock::lastReportMdibVersion() const
{
    return m_mdibVersion;
}

}
