#pragma once

#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>
#include <S31/SetService/Public/Device/DeviceTransaction.h>
#include <S31/SetService/Public/Device/InvocationCallbacks.h>

#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/DecimalIo.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8Io.h>

#include <any>
#include <condition_variable>
#include <mutex>
#include <type_traits>


namespace S31::SetService::Test::V3
{
class InvocationCallbackMock:
    public S31::SetService::V3::MdsActivateCallback,
    public S31::SetService::V3::MdsSetStringCallback,
    public S31::SetService::V3::MdsSetValueCallback,
    public S31::SetService::V3::MdsSetAlertStateCallback,
    public S31::SetService::V3::MdsSetComponentStateCallback,
    public S31::SetService::V3::MdsSetContextStateCallback,
    public S31::SetService::V3::MdsSetMetricStateCallback,
    public S31::SetService::V3::VmdActivateCallback,
    public S31::SetService::V3::VmdSetStringCallback,
    public S31::SetService::V3::VmdSetValueCallback,
    public S31::SetService::V3::VmdSetAlertStateCallback,
    public S31::SetService::V3::VmdSetComponentStateCallback,
    public S31::SetService::V3::VmdSetMetricStateCallback
{
    public:
        DFL::Mdib::Handles calledHandles() const
        {
            return m_calledHandles;
        }

        void callback(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                      const Arguments& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                      const DFL::Locale::Utf8& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                      const DFL::Mdib::Decimal& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                      const SetService::ProposedAlertStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                      const SetService::ProposedComponentStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                      const SetService::ProposedContextStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                      const SetService::ProposedMetricStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }

        void callback(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                      const Arguments& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                      const DFL::Locale::Utf8& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                      const DFL::Mdib::Decimal& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                      const SetService::ProposedAlertStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                      const SetService::ProposedComponentStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }
        void callback(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                      const SetService::ProposedMetricStates& payload,
                      SynchronousDeviceTransaction& transaction) override
        {
            commonCallback(operationHandle, payload, transaction);
        }

        bool waitForHandleCount(std::chrono::milliseconds timeout, std::size_t count)
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            return m_conditionVariable.wait_for(lock, timeout, [&]{ return m_calledHandles.size() == count; });
        }

        const std::vector<std::any>& receivedPayload() const noexcept
        {
            return m_payload;
        }

        const std::vector<S31::Safety::Context>& contexts() const noexcept
        {
            return m_safetyContexts;
        }

        const std::vector<S31::Safety::DualChannel>& dualChannels() const noexcept
        {
            return m_dualChannels;
        }

        const std::vector<DFL::Mdib::ExtensionTypes>& serviceExtensions() const noexcept
        {
            return m_serviceExtensions;
        }

        void resetMock()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_calledHandles.clear();
            m_payload.clear();
            m_safetyContexts.clear();
            m_dualChannels.clear();
            m_serviceExtensions.clear();
        }

    private:
        template<class T_Handle, class T_Payload>
        void commonCallback(const T_Handle& operationHandle,
                      const T_Payload& payload,
                      SynchronousDeviceTransaction& transaction)
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_calledHandles.push_back(toHandle(operationHandle));
                m_payload.push_back(payload);
                m_safetyContexts.push_back(transaction.safetyContext());
                m_dualChannels.push_back(transaction.dualChannel());
                m_serviceExtensions.push_back(transaction.serviceExtensions());
            }
            transaction.finished(DFL::Mdib::MdibVersion{DFL::Mdib::Uri{"urn:uuid:3ef60505-c1ba-4136-8ba9-bcafb3273752"}},
                                 S31::SetService::OperationTarget(DFL::Mdib::Handle("operation_target")));
            m_conditionVariable.notify_all();
        }

        DFL::Mdib::Handles m_calledHandles;
        std::vector<std::any> m_payload;
        std::vector<S31::Safety::Context> m_safetyContexts;
        std::vector<S31::Safety::DualChannel> m_dualChannels;
        std::vector<DFL::Mdib::ExtensionTypes> m_serviceExtensions;

        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;

};

}
