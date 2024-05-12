#pragma once

#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

#include <memory>

namespace S31::SetService::Impl
{

/**
 * @brief Default implementation of \ref InvocationCallbackRegistry.
 * @ingroup S31SetServiceDevice
 */
class InvocationCallbackRegistryImpl: public InvocationCallbackRegistry
{
    public:
        ~InvocationCallbackRegistryImpl() noexcept override;

        void registerCallback(const DFL::Mdib::MdsActivateOperationHandle& handle, const std::shared_ptr<V3::MdsActivateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetStringOperationHandle& handle, const std::shared_ptr<V3::MdsSetStringCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetValueOperationHandle& handle, const std::shared_ptr<V3::MdsSetValueCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle, const std::shared_ptr<V3::MdsSetAlertStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle, const std::shared_ptr<V3::MdsSetComponentStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetContextStateOperationHandle& handle, const std::shared_ptr<V3::MdsSetContextStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle, const std::shared_ptr<V3::MdsSetMetricStateCallback>& callback) override;

        void registerCallback(const DFL::Mdib::VmdActivateOperationHandle& handle, const std::shared_ptr<V3::VmdActivateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetStringOperationHandle& handle, const std::shared_ptr<V3::VmdSetStringCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetValueOperationHandle& handle, const std::shared_ptr<V3::VmdSetValueCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle, const std::shared_ptr<V3::VmdSetAlertStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle, const std::shared_ptr<V3::VmdSetComponentStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle, const std::shared_ptr<V3::VmdSetMetricStateCallback>& callback) override;

        std::shared_ptr<V3::MdsActivateCallback> findV3Callback(const DFL::Mdib::MdsActivateOperationHandle& operationHandle);
        std::shared_ptr<V3::MdsSetStringCallback> findV3Callback(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle);
        std::shared_ptr<V3::MdsSetValueCallback> findV3Callback(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle);
        std::shared_ptr<V3::MdsSetAlertStateCallback> findV3Callback(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle);
        std::shared_ptr<V3::MdsSetComponentStateCallback> findV3Callback(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle);
        std::shared_ptr<V3::MdsSetContextStateCallback> findV3Callback(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle);
        std::shared_ptr<V3::MdsSetMetricStateCallback> findV3Callback(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle);

        std::shared_ptr<V3::VmdActivateCallback> findV3Callback(const DFL::Mdib::VmdActivateOperationHandle& operationHandle);
        std::shared_ptr<V3::VmdSetStringCallback> findV3Callback(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle);
        std::shared_ptr<V3::VmdSetValueCallback> findV3Callback(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle);
        std::shared_ptr<V3::VmdSetAlertStateCallback> findV3Callback(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle);
        std::shared_ptr<V3::VmdSetComponentStateCallback> findV3Callback(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle);
        std::shared_ptr<V3::VmdSetMetricStateCallback> findV3Callback(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle);

    private:
        mutable std::mutex m_callbackRegistrationMutex;
        std::map<DFL::Mdib::MdsActivateOperationHandle, std::weak_ptr<V3::MdsActivateCallback>> m_v3MdsActivateCallbackMap;
        std::map<DFL::Mdib::MdsSetStringOperationHandle, std::weak_ptr<V3::MdsSetStringCallback>> m_v3MdsSetStringCallbackMap;
        std::map<DFL::Mdib::MdsSetValueOperationHandle, std::weak_ptr<V3::MdsSetValueCallback>> m_v3MdsSetValueCallbackMap;
        std::map<DFL::Mdib::MdsSetAlertStateOperationHandle, std::weak_ptr<V3::MdsSetAlertStateCallback>> m_v3MdsSetAlertStateCallbackMap;
        std::map<DFL::Mdib::MdsSetComponentStateOperationHandle, std::weak_ptr<V3::MdsSetComponentStateCallback>> m_v3MdsSetComponentStateCallbackMap;
        std::map<DFL::Mdib::MdsSetContextStateOperationHandle, std::weak_ptr<V3::MdsSetContextStateCallback>> m_v3MdsSetContextStateCallbackMap;
        std::map<DFL::Mdib::MdsSetMetricStateOperationHandle, std::weak_ptr<V3::MdsSetMetricStateCallback>> m_v3MdsSetMetricStateCallbackMap;

        std::map<DFL::Mdib::VmdActivateOperationHandle, std::weak_ptr<V3::VmdActivateCallback>> m_v3VmdActivateCallbackMap;
        std::map<DFL::Mdib::VmdSetStringOperationHandle, std::weak_ptr<V3::VmdSetStringCallback>> m_v3VmdSetStringCallbackMap;
        std::map<DFL::Mdib::VmdSetValueOperationHandle, std::weak_ptr<V3::VmdSetValueCallback>> m_v3VmdSetValueCallbackMap;
        std::map<DFL::Mdib::VmdSetAlertStateOperationHandle, std::weak_ptr<V3::VmdSetAlertStateCallback>> m_v3VmdSetAlertStateCallbackMap;
        std::map<DFL::Mdib::VmdSetComponentStateOperationHandle, std::weak_ptr<V3::VmdSetComponentStateCallback>> m_v3VmdSetComponentStateCallbackMap;
        std::map<DFL::Mdib::VmdSetMetricStateOperationHandle, std::weak_ptr<V3::VmdSetMetricStateCallback>> m_v3VmdSetMetricStateCallbackMap;

        template<class T_Callback, class T_EntityHandle>
        void registerV3Callback(std::map<T_EntityHandle, std::weak_ptr<T_Callback>>& callbackMap, const T_EntityHandle& handle, const std::shared_ptr<T_Callback>& callback);

        template <class T_Callback, class T_EntityHandle>
        std::shared_ptr<T_Callback> findV3Callback(std::map<T_EntityHandle, std::weak_ptr<T_Callback>>& callbackMap, const T_EntityHandle& operationHandle);

};

}
