#pragma once

#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/Model/Handle.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetAlertStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetComponentStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetContextStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetMetricStateOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetStringOperation.h>
#include <Framework/Mdib/Public/Model/Operation/SetValueOperation.h>

#include <boost/optional/optional.hpp>

#include <variant>

namespace S31::Sdc::Impl
{

/**
 * @brief Variant that can hold different operation handle types.
 * @ingroup S31SdcCommon
 */
using OperationHandleVariant = std::variant<
        DFL::Mdib::MdsActivateOperationHandle,
        DFL::Mdib::VmdActivateOperationHandle,
        DFL::Mdib::MdsSetStringOperationHandle,
        DFL::Mdib::VmdSetStringOperationHandle,
        DFL::Mdib::MdsSetValueOperationHandle,
        DFL::Mdib::VmdSetValueOperationHandle,
        DFL::Mdib::MdsSetContextStateOperationHandle,
        DFL::Mdib::VmdSetContextStateOperationHandle,
        DFL::Mdib::MdsSetAlertStateOperationHandle,
        DFL::Mdib::VmdSetAlertStateOperationHandle,
        DFL::Mdib::MdsSetComponentStateOperationHandle,
        DFL::Mdib::VmdSetComponentStateOperationHandle,
        DFL::Mdib::MdsSetMetricStateOperationHandle,
        DFL::Mdib::VmdSetMetricStateOperationHandle>;

/**
 * @brief Helper class to resolve typed operation handles based on untyped operation handles.
 * @ingroup S31SdcCommon
 */
class SafetyRequirementsHelper
{
    public:
        static boost::optional<OperationHandleVariant> findTypedOperationHandle(const DFL::Mdib::Handle& operationHandle, const DFL::Mdib::MdibChangeSet& changes);
        static boost::optional<OperationHandleVariant> findTypedOperationHandle(const DFL::Mdib::Handle& operationHandle, const DFL::Mdib::Mdib& mdib);
};

}
