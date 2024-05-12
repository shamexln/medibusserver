 #pragma once

#include <S31/Log/Public/KeyValue.h>
#include <S31/SetService/Private/Device/InvocationCallbackRegistryImpl.h>
#include <S31/SetService/Public/Common/InvocationError.h>
#include <S31/SetService/Public/Common/InvocationReport.h>
#include <S31/SetService/Public/Device/DeviceTransactionFactory.h>
#include <S31/SetService/Public/Device/InitialInvocationInfo.h>
#include <S31/Safety/Public/Context.h>
#include <S31/Safety/Public/DualChannel.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>
#include <S31/SetService/Public/Device/ClientInformation.h>
#include <S31/Utils/S31Only/TimerFactory.h>
#include <S31/Utils/S31Only/TimedFilter.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSignalState.h>
#include <Framework/Mdib/Public/Model/HandleIo.h>
#include <Framework/Utils/Public/Utf8.h>

#include <boost/optional/optional.hpp>

namespace S31::SetService
{

/**
 * @brief Central access point to get the device side of the set service running.
 * @details Tasks: The %ScoController accepts incoming invocation requests to
 *
 * - create immediate \ref InitialInvocationInfo result objects,
 * - check if the targeted operation's operating mode is enabled, and
 * - call the registered callback.
 * @ingroup S31SetServiceDevice
 */
class S31_CORE_EXPIMP ScoController
{
    public:
        /**
         * @brief Constructor.
         */
        ScoController(DFL::NotNull<std::shared_ptr<Utils::TimerFactory>> timerFactory,
                      DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> mdibAccess,
                      DFL::NotNull<std::shared_ptr<DeviceTransactionFactory>> deviceTransactionFactory,
                      DFL::NotNull<std::shared_ptr<Impl::InvocationCallbackRegistryImpl>> invocationCallbackRegistry);

        /**
         * @brief Accepts an \em activate operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param arguments The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const SetService::Arguments& arguments,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Accepts a *set string* operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param requestedString The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const DFL::Locale::Utf8& requestedString,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Accepts a *set value* operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param requestedValue The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const DFL::Mdib::Decimal& requestedValue,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Accepts a *set Patient/Location/Ensemble context state* operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param proposedContextStates The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const SetService::ProposedContextStates& proposedContextStates,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Accepts a *set alert states* operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param proposedAlertStates The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const SetService::ProposedAlertStates& proposedAlertStates,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Accepts a *set component state* operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param proposedComponentStates The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const SetService::ProposedComponentStates& proposedComponentStates,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Accepts a *set metric state* operation request.
         * @param operationHandle Untyped handle of the operation.
         * @param proposedMetricStates The operation request data.
         * @param context Safety context of the operation
         * @param dualChannel dual channel configuration
         * @param clientInfo client related information
         * @param serviceExtensions message extensions from the request
         */
        InitialInvocationInfo handleRequest(const DFL::Mdib::Handle& operationHandle,
                                            const SetService::ProposedMetricStates& proposedMetricStates,
                                            const Safety::Context& context,
                                            const Safety::DualChannel& dualChannel,
                                            const SetService::ClientInformation& clientInfo,
                                            const DFL::Mdib::ExtensionTypes& serviceExtensions);

        /**
         * @brief Retrieves the invocation callback registry to let customers register callbacks.
         */
        [[nodiscard]] DFL::NotNull<std::shared_ptr<InvocationCallbackRegistry>> invocationCallbackRegistry() const;

    private:
        DFL::NotNull<std::shared_ptr<Utils::TimerFactory>> m_timerFactory;
        DFL::NotNull<DFL::Mdib::MdibAccessSharedPtr> m_mdibAccess;
        DFL::NotNull<std::shared_ptr<DeviceTransactionFactory>> m_deviceTransactionFactory;
        DFL::NotNull<std::shared_ptr<SetService::Impl::InvocationCallbackRegistryImpl>> m_invocationCallbackRegistry;

        std::mutex m_retriggerableOpsMutex;
        std::map<DFL::Mdib::Handle, std::shared_ptr<Utils::Timer>> m_retriggerableOpTimers;
        std::set<DFL::Mdib::Handle> m_finishedRetriggerableOps;

        Utils::TimedFilter m_unauthorizedOperationConsumerLogFilter{DFL::Chrono::Minutes{10}};

        std::shared_ptr<Utils::Timer>
             createLastInvocationTimer(const DFL::Mdib::Handle& timerMapKey, const Log::KeyValues& securityLogInfo);
        void cleanUpRetriggerableOpTimers();

        template<class T_MdsOperationEntity, class T_VmdOperationEntity, class T_RequestData>
        InitialInvocationInfo handleTypedHandleRequest(const DFL::Mdib::Handle& operationHandle,
                                                       const T_RequestData& requestData,
                                                       const Safety::Context& context,
                                                       const Safety::DualChannel& dualChannel,
                                                       const SetService::ClientInformation& clientInfo,
                                                       const DFL::Mdib::ExtensionTypes& serviceExtensions);

        InitialInvocationInfo handleTypedHandleRequest(const DFL::Mdib::Handle& operationHandle,
                                                       const SetService::ProposedContextStates& requestData,
                                                       const Safety::Context& context,
                                                       const Safety::DualChannel& dualChannel,
                                                       const SetService::ClientInformation& clientInfo,
                                                       const DFL::Mdib::ExtensionTypes& serviceExtensions);

        template<class T_OperationEntity, class T_RequestData>
        InitialInvocationInfo handleTypedHandleRequest(const DFL::NotNull<std::shared_ptr<SetService::DeviceTransaction>>& deviceTransaction,
                                                       const DFL::NotNull<DFL::Mdib::SharedPtr<T_OperationEntity>>& operation,
                                                       const T_RequestData& requestData,
                                                       const Safety::Context& context,
                                                       const Safety::DualChannel& dualChannel,
                                                       const SetService::ClientInformation& clientInfo);

        void logUnauthorizedOperationConsumer(const SetService::ClientInformation& clientInfo,
                                              const DFL::Locale::Utf8& notAllowedReason);
};

}
