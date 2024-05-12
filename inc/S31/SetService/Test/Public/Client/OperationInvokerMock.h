#pragma once

#include <S31/SetService/Public/Client/ClientTransaction.h>
#include <S31/SetService/Public/Client/OperationInvoker.h>
#include <S31/SetService/Test/Public/Client/ClientTransactionMock.h>

#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>

#include <memory>
#include <string>
#include <vector>

namespace S31::SetService::Test
{

/**
 * @brief Mock implementation of \ref OperationInvoker
 * @ingroup S31SetService
 */
class OperationInvokerMock: public OperationInvoker
{
    public:
        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& handle,
                                                                const Arguments& arguments) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& handle,
                                                                const Arguments& arguments) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                                                const DFL::Locale::Utf8& requestedStringValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                                                const DFL::Locale::Utf8& requestedStringValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& handle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& handle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& handle,
                                                                const SetService::ProposedContextStates& proposedContextState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertStates& proposedAlertStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertStates& proposedAlertStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle,
                                                                const SetService::ProposedMetricStates& states) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle,
                                                                const SetService::ProposedMetricStates& states) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& handle,
                                                                const Arguments& arguments,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& handle,
                                                                const Arguments& arguments,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                                                const DFL::Locale::Utf8& requestedStringValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                                                const DFL::Locale::Utf8& requestedStringValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& handle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& handle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue,
                                                                const Safety::Information& safetyInformation) override;

       DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& handle,
                                                                const SetService::ProposedContextStates& proposedContextState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle,
                                                                const SetService::ProposedMetricStates& states,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle,
                                                                const SetService::ProposedMetricStates& states,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& handle,
                                                                const Arguments& arguments,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& handle,
                                                                const Arguments& arguments,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                                                const DFL::Locale::Utf8& requestedStringValue,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                                                const DFL::Locale::Utf8& requestedStringValue,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& handle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& handle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

       DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& handle,
                                                                const SetService::ProposedContextStates& proposedContextState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle,
                                                                const SetService::ProposedMetricStates& states,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle,
                                                                const SetService::ProposedMetricStates& states,
                                                                const Safety::Information& safetyInformation,
                                                                const DFL::Mdib::ExtensionTypes& extensions) override;


        std::vector<std::pair<std::string, DFL::Locale::Utf8>> invokeSetStringList();

        void clearInvokeSetStringList();

        int mdsActivateInvokeCounter() const noexcept;

        void resetMdsActivateInvokeCounter() noexcept;
    private:
        std::vector<std::pair<std::string, DFL::Locale::Utf8>> m_invokeSetStringList;
        int m_mdsActivateInvokeCounter{0};
};

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsActivateOperationHandle& /*handle*/,
                                                                                     const SetService::Arguments& /*arguments*/)
{
    m_mdsActivateInvokeCounter++;
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdActivateOperationHandle& /*handle*/,
                                                                                     const SetService::Arguments& /*arguments*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                                                                     const DFL::Locale::Utf8& requestedStringValue)
{
    m_invokeSetStringList.emplace_back(handle.string(), requestedStringValue);
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>(InvocationState::Finished, ClientInvocationReports()));
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                                                                     const DFL::Locale::Utf8& requestedStringValue)
{
    m_invokeSetStringList.emplace_back(handle.string(), requestedStringValue);
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>(InvocationState::Finished, ClientInvocationReports()));
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetValueOperationHandle& /*handle*/,
                                                                                     const DFL::Mdib::Decimal& /*requestedNumericValue*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetValueOperationHandle& /*handle*/,
                                                                                     const DFL::Mdib::Decimal& /*requestedNumericValue*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedContextStates& /*proposedPatientContextState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertStates& /*proposedAlertStates*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertStates& /*proposedAlertStates*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSystemState& /*proposedAlertSystemState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSystemState& /*proposedAlertSystemState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertConditionState& /*proposedAlertConditionState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertConditionState& /*proposedAlertConditionState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedLimitAlertConditionState& /*proposedLimitAlertConditionState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedLimitAlertConditionState& /*proposedLimitAlertConditionState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}
inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSignalState& /*proposedAlertSignalState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSignalState& /*proposedAlertSignalState*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedComponentStates& /*proposedComponentStates*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedComponentStates& /*proposedComponentStates*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedMetricStates& /*states*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedMetricStates& /*states*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}


inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsActivateOperationHandle& /*handle*/,
                                                                                     const SetService::Arguments& /*arguments*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    m_mdsActivateInvokeCounter++;
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdActivateOperationHandle& /*handle*/,
                                                                                     const SetService::Arguments& /*arguments*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                                                                     const DFL::Locale::Utf8& requestedStringValue,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    m_invokeSetStringList.emplace_back(handle.string(), requestedStringValue);
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>(InvocationState::Finished, ClientInvocationReports()));
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                                                                     const DFL::Locale::Utf8& requestedStringValue,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    m_invokeSetStringList.emplace_back(handle.string(), requestedStringValue);
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>(InvocationState::Finished, ClientInvocationReports()));
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetValueOperationHandle& /*handle*/,
                                                                                     const DFL::Mdib::Decimal& /*requestedNumericValue*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetValueOperationHandle& /*handle*/,
                                                                                     const DFL::Mdib::Decimal& /*requestedNumericValue*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedContextStates& /*proposedContextState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}


inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSystemState& /*proposedAlertSystemState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSystemState& /*proposedAlertSystemState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertConditionState& /*proposedAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertConditionState& /*proposedAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedLimitAlertConditionState& /*proposedLimitAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedLimitAlertConditionState& /*proposedLimitAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}
inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSignalState& /*proposedAlertSignalState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSignalState& /*proposedAlertSignalState*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedComponentStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedComponentStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedMetricStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedMetricStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsActivateOperationHandle& /*handle*/,
                                                                                     const SetService::Arguments& /*arguments*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    m_mdsActivateInvokeCounter++;
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdActivateOperationHandle& /*handle*/,
                                                                                     const SetService::Arguments& /*arguments*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                                                                     const DFL::Locale::Utf8& requestedStringValue,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    m_invokeSetStringList.emplace_back(handle.string(), requestedStringValue);
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>(InvocationState::Finished, ClientInvocationReports()));
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                                                                     const DFL::Locale::Utf8& requestedStringValue,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    m_invokeSetStringList.emplace_back(handle.string(), requestedStringValue);
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>(InvocationState::Finished, ClientInvocationReports()));
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetValueOperationHandle& /*handle*/,
                                                                                     const DFL::Mdib::Decimal& /*requestedNumericValue*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetValueOperationHandle& /*handle*/,
                                                                                     const DFL::Mdib::Decimal& /*requestedNumericValue*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedContextStates& /*proposedContextState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}


inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSystemState& /*proposedAlertSystemState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSystemState& /*proposedAlertSystemState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertConditionState& /*proposedAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertConditionState& /*proposedAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedLimitAlertConditionState& /*proposedLimitAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedLimitAlertConditionState& /*proposedLimitAlertConditionState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}
inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSignalState& /*proposedAlertSignalState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedAlertSignalState& /*proposedAlertSignalState*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedComponentStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedComponentStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedMetricStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline DFL::NotNull<std::shared_ptr<ClientTransaction>> OperationInvokerMock::invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& /*handle*/,
                                                                                     const SetService::ProposedMetricStates& /*proposedComponentStates*/,
                                                                                     const Safety::Information& /*safetyInformation*/,
                                                                                     const DFL::Mdib::ExtensionTypes& /*extensions*/)
{
    return DFL::asNotNull(std::make_shared<ClientTransactionMock>());
}

inline std::vector<std::pair<std::string, DFL::Locale::Utf8>> OperationInvokerMock::invokeSetStringList()
{
    return m_invokeSetStringList;
}

inline void OperationInvokerMock::clearInvokeSetStringList()
{
    m_invokeSetStringList.clear();
}

inline int OperationInvokerMock::mdsActivateInvokeCounter() const noexcept
{
    return m_mdsActivateInvokeCounter;
}

inline void OperationInvokerMock::resetMdsActivateInvokeCounter() noexcept
{
    m_mdsActivateInvokeCounter = 0;
}

}
