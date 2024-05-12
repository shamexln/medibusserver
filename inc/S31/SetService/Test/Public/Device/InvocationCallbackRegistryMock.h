#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>

#include <Framework/Mdib/Public/Model/HandleIo.h>

#include <mutex>

namespace S31::SetService::Test
{
namespace Impl
{
/**
 * @ingroup S31SetServiceDevice
 */
template<class T_Data, class T_EntityHandle>
class ScoMock
{
    public:

        using Callback = std::function<void(const T_EntityHandle&, const T_Data&, const DFL::NotNull<std::shared_ptr<SetService::DeviceTransaction>>&)>;
};
}

/**
 * @ingroup S31SetServiceDevice
 */
class InvocationCallbackRegistryMock : public SetService::InvocationCallbackRegistry
{
    public:
        void registerCallback(const DFL::Mdib::MdsActivateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsActivateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetStringOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetStringCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetValueOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetValueCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetAlertStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetComponentStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetContextStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetContextStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetMetricStateCallback>& callback) override;

        void registerCallback(const DFL::Mdib::VmdActivateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdActivateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetStringOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetStringCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetValueOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetValueCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetAlertStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetComponentStateCallback>& callback) override;
        void registerCallback(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetMetricStateCallback>& callback) override;

        std::shared_ptr<SetService::V3::MdsActivateCallback> getV3Callback(const DFL::Mdib::MdsActivateOperationHandle& handle) const;
        std::shared_ptr<SetService::V3::MdsSetStringCallback> getV3Callback(const DFL::Mdib::MdsSetStringOperationHandle& handle) const;
        std::shared_ptr<SetService::V3::MdsSetContextStateCallback> getV3Callback(const DFL::Mdib::MdsSetContextStateOperationHandle& handle) const;
        std::shared_ptr<SetService::V3::VmdActivateCallback> getV3Callback(const DFL::Mdib::VmdActivateOperationHandle& handle) const;
        std::shared_ptr<SetService::V3::VmdSetStringCallback> getV3Callback(const DFL::Mdib::VmdSetStringOperationHandle& handle) const;

    private:
        // mutable to remove expired weak_ptr on const access
        mutable std::map<DFL::Mdib::MdsActivateOperationHandle, std::weak_ptr<SetService::V3::MdsActivateCallback>> m_mdsActivateCallback;
        mutable std::map<DFL::Mdib::MdsSetStringOperationHandle, std::weak_ptr<SetService::V3::MdsSetStringCallback>> m_mdsSetStringCallback;
        mutable std::map<DFL::Mdib::MdsSetValueOperationHandle, std::weak_ptr<SetService::V3::MdsSetValueCallback>> m_mdsSetValueCallback;
        mutable std::map<DFL::Mdib::MdsSetAlertStateOperationHandle, std::weak_ptr<SetService::V3::MdsSetAlertStateCallback>> m_mdsSetAlertStateCallback;
        mutable std::map<DFL::Mdib::MdsSetComponentStateOperationHandle, std::weak_ptr<SetService::V3::MdsSetComponentStateCallback>> m_mdsSetComponentStateCallback;
        mutable std::map<DFL::Mdib::MdsSetContextStateOperationHandle, std::weak_ptr<SetService::V3::MdsSetContextStateCallback>> m_mdsSetContextStateCallback;
        mutable std::map<DFL::Mdib::MdsSetMetricStateOperationHandle, std::weak_ptr<SetService::V3::MdsSetMetricStateCallback>> m_mdsSetMetricStateCallback;

        mutable std::map<DFL::Mdib::VmdActivateOperationHandle, std::weak_ptr<SetService::V3::VmdActivateCallback>> m_vmdActivateCallback;
        mutable std::map<DFL::Mdib::VmdSetStringOperationHandle, std::weak_ptr<SetService::V3::VmdSetStringCallback>> m_vmdSetStringCallback;
        mutable std::map<DFL::Mdib::VmdSetValueOperationHandle, std::weak_ptr<SetService::V3::VmdSetValueCallback>> m_vmdSetValueCallback;
        mutable std::map<DFL::Mdib::VmdSetAlertStateOperationHandle, std::weak_ptr<SetService::V3::VmdSetAlertStateCallback>> m_vmdSetAlertStateCallback;
        mutable std::map<DFL::Mdib::VmdSetComponentStateOperationHandle, std::weak_ptr<SetService::V3::VmdSetComponentStateCallback>> m_vmdSetComponentStateCallback;
        mutable std::map<DFL::Mdib::VmdSetMetricStateOperationHandle, std::weak_ptr<SetService::V3::VmdSetMetricStateCallback>> m_vmdSetMetricStateCallback;
        template <class T_Callback, class T_Handle>
        std::shared_ptr<T_Callback> getV3Callback(std::map<T_Handle, std::weak_ptr<T_Callback>>& map, const T_Handle& handle) const;

        template <class T_Callback, class T_Handle>
        void insertCallback(std::map<T_Handle, std::weak_ptr<T_Callback>>& map, const T_Handle& handle, const std::shared_ptr<T_Callback>& callback);

};

inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsActivateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsActivateCallback>& callback)
{
    insertCallback(m_mdsActivateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsSetStringOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetStringCallback>& callback)
{
    insertCallback(m_mdsSetStringCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsSetValueOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetValueCallback>& callback)
{
    insertCallback(m_mdsSetValueCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetAlertStateCallback>& callback)
{
    insertCallback(m_mdsSetAlertStateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetComponentStateCallback>& callback)
{
    insertCallback(m_mdsSetComponentStateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsSetContextStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetContextStateCallback>& callback)
{
    insertCallback(m_mdsSetContextStateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle, const std::shared_ptr<SetService::V3::MdsSetMetricStateCallback>& callback)
{
    insertCallback(m_mdsSetMetricStateCallback, handle, callback);
}

inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::VmdActivateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdActivateCallback>& callback)
{
    insertCallback(m_vmdActivateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::VmdSetStringOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetStringCallback>& callback)
{
    insertCallback(m_vmdSetStringCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::VmdSetValueOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetValueCallback>& callback)
{
    insertCallback(m_vmdSetValueCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetAlertStateCallback>& callback)
{
    insertCallback(m_vmdSetAlertStateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetComponentStateCallback>& callback)
{
    insertCallback(m_vmdSetComponentStateCallback, handle, callback);
}
inline void InvocationCallbackRegistryMock::registerCallback(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle, const std::shared_ptr<SetService::V3::VmdSetMetricStateCallback>& callback)
{
    insertCallback(m_vmdSetMetricStateCallback, handle, callback);
}

inline std::shared_ptr<SetService::V3::MdsActivateCallback> InvocationCallbackRegistryMock::getV3Callback(const DFL::Mdib::MdsActivateOperationHandle& handle) const
{
    return getV3Callback(m_mdsActivateCallback, handle);
}
inline std::shared_ptr<SetService::V3::MdsSetStringCallback> InvocationCallbackRegistryMock::getV3Callback(const DFL::Mdib::MdsSetStringOperationHandle& handle) const
{
    return getV3Callback(m_mdsSetStringCallback, handle);
}
inline std::shared_ptr<SetService::V3::MdsSetContextStateCallback> InvocationCallbackRegistryMock::getV3Callback(const DFL::Mdib::MdsSetContextStateOperationHandle& handle) const
{
    return getV3Callback(m_mdsSetContextStateCallback, handle);
}

inline std::shared_ptr<SetService::V3::VmdActivateCallback> InvocationCallbackRegistryMock::getV3Callback(const DFL::Mdib::VmdActivateOperationHandle& handle) const
{
    return getV3Callback(m_vmdActivateCallback, handle);
}
inline std::shared_ptr<SetService::V3::VmdSetStringCallback> InvocationCallbackRegistryMock::getV3Callback(const DFL::Mdib::VmdSetStringOperationHandle& handle) const
{
    return getV3Callback(m_vmdSetStringCallback, handle);
}

template<class T_Callback, class T_Handle>
std::shared_ptr<T_Callback> InvocationCallbackRegistryMock::getV3Callback(std::map<T_Handle, std::weak_ptr<T_Callback>>& map, const T_Handle& handle) const
{
    auto it = map.find(handle);
    if (it != map.end())
    {
        if (auto callback = it->second.lock())
        {
            return callback;
        }
        S31_STREAM_INFO_LOGGER("S31.SetService", "Callback for handle '", handle, "' expired");
        map.erase(it);
        return nullptr;
    }
    S31_STREAM_INFO_LOGGER("S31.SetService", "Callback for handle '", handle, "' not found");
    return nullptr;
}

template<class T_Callback, class T_Handle>
void InvocationCallbackRegistryMock::insertCallback(std::map<T_Handle, std::weak_ptr<T_Callback>>& map, const T_Handle& handle, const std::shared_ptr<T_Callback>& callback)
{
    S31_STREAM_INFO_LOGGER("S31.SetService", "Register callback for handle ", handle);
    {
        auto it = map.find(handle);
        if (it != map.end())
        {
            // previous entry exist for handle
            if (!it->second.expired())
            {
                S31_STREAM_WARN_LOGGER("S31.SetService", "There is a previous (not expired) callback for handle ", handle, " already registered");
            }
            map.erase(it);
        }
    }
    map.insert(std::make_pair(handle, callback));
}

}
