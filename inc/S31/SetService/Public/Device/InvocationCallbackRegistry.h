#pragma once

#include <S31/S31CoreExImp.h>

#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Device/DeviceTransaction.h>
#include <S31/SetService/Public/Device/InvocationCallbacks.h>

#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>

#include <functional>

namespace S31::SetService
{

/**
 * @brief Registry to register for remote invocation callbacks on the device side.
 * @ingroup S31SetServiceDevice
 */
class S31_CORE_EXPIMP InvocationCallbackRegistry
{
    public:
        virtual ~InvocationCallbackRegistry() noexcept = default;

        /**
         * @name V3 callback
         * @brief Registers a callback that reside in a SCO.
         * @details The callback is invoked every time an incoming operation request matches the given handle.
         * @{
         */

        virtual void registerCallback(const DFL::Mdib::MdsActivateOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsActivateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::MdsSetStringOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsSetStringCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::MdsSetValueOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsSetValueCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::MdsSetAlertStateOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsSetAlertStateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::MdsSetComponentStateOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsSetComponentStateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::MdsSetContextStateOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsSetContextStateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::MdsSetMetricStateOperationHandle& handle,
                                      const std::shared_ptr<V3::MdsSetMetricStateCallback>& callback) = 0;

        virtual void registerCallback(const DFL::Mdib::VmdActivateOperationHandle& handle,
                                      const std::shared_ptr<V3::VmdActivateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::VmdSetStringOperationHandle& handle,
                                      const std::shared_ptr<V3::VmdSetStringCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::VmdSetValueOperationHandle& handle,
                                      const std::shared_ptr<V3::VmdSetValueCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::VmdSetAlertStateOperationHandle& handle,
                                      const std::shared_ptr<V3::VmdSetAlertStateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::VmdSetComponentStateOperationHandle& handle,
                                      const std::shared_ptr<V3::VmdSetComponentStateCallback>& callback) = 0;
        virtual void registerCallback(const DFL::Mdib::VmdSetMetricStateOperationHandle& handle,
                                      const std::shared_ptr<V3::VmdSetMetricStateCallback>& callback) = 0;
        /** @} */
};

}
