#pragma once

#include <S31/Safety/Public/Information.h>
#include <S31/SetService/Public/Client/ClientTransaction.h>
#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/ProposedAlertState.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>

#include <Framework/Mdib/Public/Model/Alert/AlertConditionState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalState.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystemState.h>
#include <Framework/Mdib/Public/Model/Alert/LimitAlertConditionState.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextState.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>

namespace S31::SetService
{

/**
 * @brief A tool to invoke operations on the client side.
 * @ingroup S31SetService
 */
class OperationInvoker
{
    public:
        virtual ~OperationInvoker() noexcept = default;

        /**
         * @brief Invokes an *activate* that accepts an \ref DFL::Mdib::MdsActivateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                                                                        const Arguments& arguments) = 0;

        /**
         * @brief Invokes an *activate* that accepts a \ref DFL::Mdib::VmdActivateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                                                                        const Arguments& arguments) = 0;

        /**
         * @brief Invokes a *set string* that accepts an \ref DFL::Mdib::MdsSetStringOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                                                                        const DFL::Locale::Utf8& requestedStringValue) = 0;

        /**
         * @brief Invokes a *set string* that accepts a \ref DFL::Mdib::VmdSetStringOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                                                                        const DFL::Locale::Utf8& requestedStringValue) = 0;

        /**
         * @brief Invokes a *set value* that accepts an \ref DFL::Mdib::MdsSetValueOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                                                                        const DFL::Mdib::Decimal& requestedNumericValue) = 0;

        /**
         * @brief Invokes a *set value* that accepts a \ref DFL::Mdib::VmdSetValueOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                                                                        const DFL::Mdib::Decimal& requestedNumericValue) = 0;

        /**
         * @brief Invokes a *set context state* that accepts an \ref DFL::Mdib::MdsSetContextStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                                                                        const ProposedContextStates& proposedContextState) = 0;

        /**
         * @brief Invokes a *set alert state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         * @details
         * Currently only allows one alert state. This will change with upcoming SDC fix.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertStates& proposedAlertStates) = 0;

        /**
         * @brief Invokes a *set alert state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         * @details
         * Currently only allows one alert state. This will change with upcoming SDC fix.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertStates& proposedAlertStates) = 0;


        /**
         * @brief Invokes a *set alert system context state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSystemState& proposedAlertSystemState) = 0;

        /**
         * @brief Invokes a *set alert system state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSystemState& proposedAlertSystemState) = 0;

        /**
         * @brief Invokes a *set alert condition state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertConditionState& proposedAlertConditionState) = 0;

        /**
         * @brief Invokes a *set alert condition state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertConditionState& proposedAlertConditionState) = 0;

        /**
         * @brief Invokes a *set limit alert condition state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedLimitAlertConditionState& proposedLimitAlertConditionState) = 0;

        /**
         * @brief Invokes a *set limit alert condition state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedLimitAlertConditionState& proposedLimitAlertConditionState) = 0;

        /**
         * @brief Invokes a *set alert signal state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSignalState& proposedAlertSignalState) = 0;

        /**
         * @brief Invokes a *set alert signal state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSignalState& proposedAlertSignalState) = 0;

        /**
         * @brief Invokes a *set component state* that accepts a \ref DFL::Mdib::MdsSetComponentStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                                                                        const ProposedComponentStates& proposedComponentStates) = 0;

        /**
         * @brief Invokes a *set component state* that accepts a \ref DFL::Mdib::VmdSetComponentStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                                                                        const ProposedComponentStates& proposedComponentStates) = 0;

        /**
         * @brief Invokes a *set metric state* that accepts an \ref DFL::Mdib::MdsSetMetricStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                                                                        const ProposedMetricStates& proposedMetricState) = 0;

        /**
         * @brief Invokes a *set metric state* that accepts an \ref DFL::Mdib::VmdSetMetricStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                                                                        const ProposedMetricStates& proposedMetricState) = 0;

        /**
         * @brief Invokes a safe *activate* that accepts an \ref DFL::Mdib::MdsActivateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                                                                        const Arguments& arguments,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *activate* that accepts a \ref DFL::Mdib::VmdActivateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                                                                        const Arguments& arguments,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set string* that accepts an \ref DFL::Mdib::MdsSetStringOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                                                                        const DFL::Locale::Utf8& requestedStringValue,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set string* that accepts a \ref DFL::Mdib::VmdSetStringOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                                                                        const DFL::Locale::Utf8& requestedStringValue,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set value* that accepts an \ref DFL::Mdib::MdsSetValueOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                                                                        const DFL::Mdib::Decimal& requestedNumericValue,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set value* that accepts a \ref DFL::Mdib::VmdSetValueOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                                                                        const DFL::Mdib::Decimal& requestedNumericValue,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set context state* that accepts an \ref DFL::Mdib::MdsSetContextStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                                                                        const ProposedContextStates& proposedContextState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set alert system state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSystemState& proposedAlertSystemState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set alert system state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSystemState& proposedAlertSystemState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set alert condition state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertConditionState& proposedAlertConditionState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set alert condition state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertConditionState& proposedAlertConditionState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set limit alert condition state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set limit alert condition state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a *set alert signal state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSignalState& proposedAlertSignalState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a *set alert signal state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSignalState& proposedAlertSignalState,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set component state* that accepts a \ref DFL::Mdib::MdsSetComponentStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                                                                        const ProposedComponentStates& proposedComponentStates,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set component state* that accepts a \ref DFL::Mdib::VmdSetComponentStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                                                                        const ProposedComponentStates& proposedComponentStates,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set metric state* that accepts an \ref DFL::Mdib::MdsSetMetricStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                                                                        const ProposedMetricStates& states,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a safe *set metric state* that accepts an \ref DFL::Mdib::VmdSetMetricStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                                                                        const ProposedMetricStates& states,
                                                                        const Safety::Information& safetyInformation) = 0;

        /**
         * @brief Invokes a *activate* that accepts an \ref DFL::Mdib::MdsActivateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                                                                        const Arguments& arguments,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *activate* that accepts a \ref DFL::Mdib::VmdActivateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                                                                        const Arguments& arguments,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set string* that accepts an \ref DFL::Mdib::MdsSetStringOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                                                                        const DFL::Locale::Utf8& requestedStringValue,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set string* that accepts a \ref DFL::Mdib::VmdSetStringOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                                                                        const DFL::Locale::Utf8& requestedStringValue,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set value* that accepts an \ref DFL::Mdib::MdsSetValueOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                                                                        const DFL::Mdib::Decimal& requestedNumericValue,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set value* that accepts a \ref DFL::Mdib::VmdSetValueOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                                                                        const DFL::Mdib::Decimal& requestedNumericValue,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set context state* that accepts an \ref DFL::Mdib::MdsSetContextStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                                                                        const ProposedContextStates& proposedContextState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set alert system state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSystemState& proposedAlertSystemState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set alert system state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSystemState& proposedAlertSystemState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set alert condition state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertConditionState& proposedAlertConditionState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set alert condition state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertConditionState& proposedAlertConditionState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set limit alert condition state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set limit alert condition state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedLimitAlertConditionState& proposedLimitAlertConditionState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set alert signal state* that accepts an \ref DFL::Mdib::MdsSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSignalState& proposedAlertSignalState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set alert signal state* that accepts a \ref DFL::Mdib::VmdSetAlertStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                                                                        const ProposedAlertSignalState& proposedAlertSignalState,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set component state* that accepts a \ref DFL::Mdib::MdsSetComponentStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                                                                        const ProposedComponentStates& proposedComponentStates,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set component state* that accepts a \ref DFL::Mdib::VmdSetComponentStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                                                                        const ProposedComponentStates& proposedComponentStates,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set metric state* that accepts an \ref DFL::Mdib::MdsSetMetricStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                                                                        const ProposedMetricStates& states,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

        /**
         * @brief Invokes a *set metric state* that accepts an \ref DFL::Mdib::VmdSetMetricStateOperationHandle.
         */
        virtual DFL::NotNull<std::shared_ptr<ClientTransaction>> invoke(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                                                                        const ProposedMetricStates& states,
                                                                        const Safety::Information& safetyInformation,
                                                                        const DFL::Mdib::ExtensionTypes& extensions) = 0;

};

}
