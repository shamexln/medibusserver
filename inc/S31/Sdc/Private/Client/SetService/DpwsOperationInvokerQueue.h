#pragma once

#include <S31/Sdc/Private/Client/PortTypeExecutors.h>
#include <S31/Sdc/Private/Client/SetService/ActivateJob.h>
#include <S31/Sdc/Private/Client/SetService/InvocationReportSubject.h>
#include <S31/Sdc/Private/Client/SetService/SetStringJob.h>
#include <S31/SetService/Public/Client/ClientTransaction.h>
#include <S31/SetService/Public/Client/OperationInvokerQueue.h>
#include <S31/Sdc/Private/Client/SetService/SetValueJob.h>
#include <S31/Sdc/Private/Client/SetService/SetContextJob.h>
#include <S31/Sdc/Private/Client/SetService/SetComponentJob.h>
#include <S31/Sdc/Private/Client/SetService/SetAlertStateJob.h>
#include <S31/Sdc/Private/Client/SetService/SetMetricStateJob.h>
#include <S31/Sdc/Private/Common/Endpoint/Executor.h>

#include <Framework/Mdib/Public/MdibAccessSmartPtrTypes.h>

#include <atomic>
#include <mutex>

namespace S31::Sdc::Impl
{

/**
 * @brief Implements the \ref S31::SetService::OperationInvokerQueue that is required by the Set Service API
 * @ingroup S31SdcClient
 */
class DpwsOperationInvokerQueue:
        public S31::SetService::OperationInvokerQueue,
        public std::enable_shared_from_this<DpwsOperationInvokerQueue>,
        public S31::Utils::OutcomeConsumer<DpwsOperationInvokerQueue, SetOperationJobResult>
{
    public:
        DpwsOperationInvokerQueue(std::string urn,
                                  DFL::Mdib::MdibAccessWeakPtr mdibAccess,
                                  std::weak_ptr<InvocationReportSubject> observer,
                                  PortTypeExecutors portTypeExecutors);

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const S31::SetService::Arguments& arguments,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const DFL::Locale::Utf8& stringValue,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const DFL::Mdib::Decimal& decimalValue,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedContextStates& states,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedAlertStates& states,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedAlertSystemState& state,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedAlertConditionState& state,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedLimitAlertConditionState& state,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedAlertSignalState& state,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedComponentStates& states,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

        void enqueue(const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                     const SetService::ProposedMetricStates& states,
                     const SetService::OperationHandle& operationHandle,
                     const Safety::Information& safetyInformation,
                     const DFL::Mdib::ExtensionTypes& extensions) override;

    private:
        template <class T_Job, class T_Data>
        void queue(S31::Sdc::Impl::PortType servicePortType,
                   const DFL::NotNull<std::shared_ptr<S31::SetService::ClientTransactionWriter>>& transaction,
                   const SetService::OperationHandle& operationHandle,
                   const Safety::Information& safetyInformation,
                   const T_Data& data,
                   const DFL::Mdib::ExtensionTypes& extensions);

        std::weak_ptr<InvocationReportSubject> m_invocationReportSubject;

        std::string m_remoteUrn;
        DFL::Mdib::MdibAccessWeakPtr m_mdibAccess;
        PortTypeExecutors m_portTypeExecutors;

        struct RunningSetRequests
        {
                mutable std::mutex mutex;
                std::map<unsigned int, Endpoint::HandlerPtr> requests;
        };

        std::atomic<unsigned int> m_executorHandlerId;
        std::shared_ptr<RunningSetRequests> m_runningSetRequests;
};

} /* namespace S31 */
