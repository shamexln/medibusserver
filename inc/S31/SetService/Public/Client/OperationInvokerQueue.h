#pragma once

#include <S31/SetService/Public/Client/ClientTransactionWriter.h>
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
#include <Framework/Utils/Public/NotNull.h>

namespace S31::SetService
{

/**
 * @brief Interface to prepare and send operation requests.
 * @ingroup S31SetService
 */
class OperationInvokerQueue
{
public:
    virtual ~OperationInvokerQueue() noexcept = default;

    /**
     * @brief Prepares an *activate job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param arguments The arguments passed to the activate function.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const Arguments& arguments,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set string job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param stringValue The requested string value to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const DFL::Locale::Utf8& stringValue,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set value job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param decimalValue The requested decimal value to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const DFL::Mdib::Decimal& decimalValue,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set Patient/Location/Ensemble Context job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param states The requested \ref S31::SetService::ProposedContextStates to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const ProposedContextStates& states,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set Alert job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param state The requested \ref SetService::ProposedAlertStates to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const SetService::ProposedAlertStates& state,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set Alert System job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param state The requested \ref SetService::ProposedAlertSystemState to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const SetService::ProposedAlertSystemState& state,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set Alert Condition job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param state The requested \ref SetService::ProposedAlertConditionState to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const SetService::ProposedAlertConditionState& state,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set Limit Alert Condition job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param state The requested \ref SetService::ProposedLimitAlertConditionState to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const SetService::ProposedLimitAlertConditionState& state,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set Alert Signal job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param state The requested \ref SetService::ProposedAlertSignalState to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const SetService::ProposedAlertSignalState& state,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set component state job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param states The requested \ref S31::SetService::ProposedComponentStates to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const ProposedComponentStates& states,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;

    /**
     * @brief Prepares a *set metric state job* and queues it for processing.
     * @param transaction The processed transaction that can be used to notify incoming reports and set client errors.
     * @param states The requested \ref S31::SetService::ProposedMetricStates to set remotely.
     * @param operationHandle The operation handle in the remote MDIB.
     * @param safetyInformation The safety information (context and dual channel).
     * @param extensions Custom extensions passed to the AbstractSet element.
     */
    virtual void
    enqueue(const DFL::NotNull<std::shared_ptr<ClientTransactionWriter>>& transaction,
            const ProposedMetricStates& states,
            const OperationHandle& operationHandle,
            const Safety::Information& safetyInformation,
            const DFL::Mdib::ExtensionTypes& extensions) = 0;
};

}
