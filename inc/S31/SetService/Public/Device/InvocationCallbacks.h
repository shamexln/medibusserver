#pragma once

#include <S31/SetService/Public/Common/Argument.h>
#include <S31/SetService/Public/Common/ProposedAlertStates.h>
#include <S31/SetService/Public/Common/ProposedComponentStates.h>
#include <S31/SetService/Public/Common/ProposedContextStates.h>
#include <S31/SetService/Public/Common/ProposedMetricStates.h>
#include <S31/SetService/Public/Device/DeviceTransaction.h>
#include <S31/SetService/Public/Device/InitialInvocationInfo.h>
#include <S31/SetService/Public/Device/SynchronousDeviceTransaction.h>

#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::SetService::V3
{
class MdsActivateCallback
{
    public:
        virtual ~MdsActivateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsActivateOperationHandle& operationHandle,
                              const Arguments& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class MdsSetStringCallback
{
    public:
        virtual ~MdsSetStringCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsSetStringOperationHandle& operationHandle,
                              const DFL::Locale::Utf8& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class MdsSetValueCallback
{
    public:
        virtual ~MdsSetValueCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsSetValueOperationHandle& operationHandle,
                              const DFL::Mdib::Decimal& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class MdsSetAlertStateCallback
{
    public:
        virtual ~MdsSetAlertStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsSetAlertStateOperationHandle& operationHandle,
                              const SetService::ProposedAlertStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class MdsSetComponentStateCallback
{
    public:
        virtual ~MdsSetComponentStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsSetComponentStateOperationHandle& operationHandle,
                              const SetService::ProposedComponentStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class MdsSetContextStateCallback
{
    public:
        virtual ~MdsSetContextStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsSetContextStateOperationHandle& operationHandle,
                              const SetService::ProposedContextStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class MdsSetMetricStateCallback
{
    public:
        virtual ~MdsSetMetricStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::MdsSetMetricStateOperationHandle& operationHandle,
                              const SetService::ProposedMetricStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};

class VmdActivateCallback
{
    public:
        virtual ~VmdActivateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::VmdActivateOperationHandle& operationHandle,
                              const Arguments& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class VmdSetStringCallback
{
    public:
        virtual ~VmdSetStringCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::VmdSetStringOperationHandle& operationHandle,
                              const DFL::Locale::Utf8& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class VmdSetValueCallback
{
    public:
        virtual ~VmdSetValueCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::VmdSetValueOperationHandle& operationHandle,
                              const DFL::Mdib::Decimal& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class VmdSetAlertStateCallback
{
    public:
        virtual ~VmdSetAlertStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::VmdSetAlertStateOperationHandle& operationHandle,
                              const SetService::ProposedAlertStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class VmdSetComponentStateCallback
{
    public:
        virtual ~VmdSetComponentStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::VmdSetComponentStateOperationHandle& operationHandle,
                              const SetService::ProposedComponentStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};
class VmdSetMetricStateCallback
{
    public:
        virtual ~VmdSetMetricStateCallback() noexcept = default;
        virtual void callback(const DFL::Mdib::VmdSetMetricStateOperationHandle& operationHandle,
                              const SetService::ProposedMetricStates& payload,
                              SynchronousDeviceTransaction& transaction) = 0;
};

}
