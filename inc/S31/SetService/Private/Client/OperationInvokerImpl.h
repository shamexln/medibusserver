#pragma once

#include <S31/Safety/Public/Requirement.h>
#include <S31/SetService/Public/Client/OperationInvoker.h>

#include <Framework/Mdib/Public/MdibAccessSmartPtrTypes.h>

namespace S31::SetService
{
class OperationInvokerQueue;
namespace Impl
{
/**
 * @brief Default implementation of \ref OperationInvoker.
 * @ingroup S31SetService
 */
class OperationInvokerImpl: public OperationInvoker
{
    public:
        OperationInvokerImpl(DFL::Mdib::MdibAccessWeakPtr mdibAccess,
                             DFL::NotNull<std::shared_ptr<OperationInvokerQueue>> operationInvokerQueue,
                             std::string remoteDeviceUrn);

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                                                                const Arguments& arguments) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                                                                const Arguments& arguments) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                                                                const DFL::Locale::Utf8& requestedStringValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                                                                const DFL::Locale::Utf8& requestedStringValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                                                                const SetService::ProposedContextStates& proposedContextStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertStates& proposedAlertStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertStates& proposedAlertStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                                                                const ProposedMetricStates& proposedMetricStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                                                                const ProposedMetricStates& proposedMetricStates) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                                                                const Arguments& arguments,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                                                                const Arguments& arguments,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                                                                const DFL::Locale::Utf8& requestedStringValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                                                                const DFL::Locale::Utf8& requestedStringValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                                                                const DFL::Mdib::Decimal& requestedNumericValue,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                                                                const SetService::ProposedContextStates& proposedContextStates,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSystemState& proposedAlertSystemState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertConditionState& proposedAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                const SetService::ProposedAlertSignalState& proposedAlertSignalState,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                                                                const SetService::ProposedComponentStates& proposedComponentStates,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                                                                const ProposedMetricStates& states,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                                                                const ProposedMetricStates& states,
                                                                const Safety::Information& safetyInformation) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
               const Arguments&                             arguments,
               const Safety::Information&                   safetyInformation,
               const DFL::Mdib::ExtensionTypes&             extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
               const Arguments&                             arguments,
               const Safety::Information&                   safetyInformation,
               const DFL::Mdib::ExtensionTypes&             extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
               const DFL::Locale::Utf8&                      requestedStringValue,
               const Safety::Information&                    safetyInformation,
               const DFL::Mdib::ExtensionTypes&              extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
               const DFL::Locale::Utf8&                      requestedStringValue,
               const Safety::Information&                    safetyInformation,
               const DFL::Mdib::ExtensionTypes&              extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
               const DFL::Mdib::Decimal&                    requestedNumericValue,
               const Safety::Information&                   safetyInformation,
               const DFL::Mdib::ExtensionTypes&             extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
               const DFL::Mdib::Decimal&                    requestedNumericValue,
               const Safety::Information&                   safetyInformation,
               const DFL::Mdib::ExtensionTypes&             extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
               const SetService::ProposedContextStates&            proposedContextStates,
               const Safety::Information&                          safetyInformation,
               const DFL::Mdib::ExtensionTypes&                    extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
               const SetService::ProposedAlertSystemState&       proposedAlertSystemState,
               const Safety::Information&                        safetyInformation,
               const DFL::Mdib::ExtensionTypes&                  extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
               const SetService::ProposedAlertSystemState&       proposedAlertSystemState,
               const Safety::Information&                        safetyInformation,
               const DFL::Mdib::ExtensionTypes&                  extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
               const SetService::ProposedAlertConditionState&    proposedAlertConditionState,
               const Safety::Information&                        safetyInformation,
               const DFL::Mdib::ExtensionTypes&                  extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
               const SetService::ProposedAlertConditionState&    proposedAlertConditionState,
               const Safety::Information&                        safetyInformation,
               const DFL::Mdib::ExtensionTypes&                  extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle&   operationHandle,
               const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
               const Safety::Information&                          safetyInformation,
               const DFL::Mdib::ExtensionTypes&                    extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle&   operationHandle,
               const SetService::ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
               const Safety::Information&                          safetyInformation,
               const DFL::Mdib::ExtensionTypes&                    extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
               const SetService::ProposedAlertSignalState&       proposedAlertSignalState,
               const Safety::Information&                        safetyInformation,
               const DFL::Mdib::ExtensionTypes&                  extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
               const SetService::ProposedAlertSignalState&       proposedAlertSignalState,
               const Safety::Information&                        safetyInformation,
               const DFL::Mdib::ExtensionTypes&                  extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
               const SetService::ProposedComponentStates&            proposedComponentStates,
               const Safety::Information&                            safetyInformation,
               const DFL::Mdib::ExtensionTypes&                      extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
               const SetService::ProposedComponentStates&            proposedComponentStates,
               const Safety::Information&                            safetyInformation,
               const DFL::Mdib::ExtensionTypes&                      extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
               const ProposedMetricStates&                        states,
               const Safety::Information&                         safetyInformation,
               const DFL::Mdib::ExtensionTypes&                   extensions) override;

        DFL::NotNull<std::shared_ptr<ClientTransaction>>
        invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
               const ProposedMetricStates&                        states,
               const Safety::Information&                         safetyInformation,
               const DFL::Mdib::ExtensionTypes&                   extensions) override;

    private:
        DFL::Mdib::MdibAccessWeakPtr m_mdibAccess;
        DFL::NotNull<std::shared_ptr<OperationInvokerQueue>> m_operationInvokerQueue;
        std::string m_remoteDeviceUrn;

        template<class T_OperationEntity, class T_Data>
        DFL::NotNull<std::shared_ptr<ClientTransaction>> invokeOperation(
                const DFL::Mdib::BasicHandle<T_OperationEntity>& operationHandle,
                const T_Data&                                    data,
                const Safety::Information&                       safetyInformation,
                const DFL::Mdib::ExtensionTypes&                 extensions);

        template<class T_OperationEntity>
        DFL::Mdib::SharedPtr<T_OperationEntity> getEntity(const DFL::Mdib::BasicHandle<T_OperationEntity>& operationHandle) const;

};

}
}
