#pragma once

#include <S31/SetService/Private/Client/OperationInvokerImpl.h>

#include <Framework/Mdib/Public/MdibAccess.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::SetService
{

/**
 * @brief Factory to create Operation Invokers.
 * @ingroup S31SetService
 */
class OperationInvokerFactory
{

    public:
        /**
         * @brief Creates an \ref OperationInvoker instance based on the given dependencies.
         * @param mdibAccess Is used to find typed operations and check the operating modes.
         * @param operationInvokerQueue Is used to queue the operation requests.
         * @param deviceIdentifierForLogPurposes identifier of the remote device for log purposes
         */
        static DFL::NotNull<std::unique_ptr<OperationInvoker>> create(
                const DFL::Mdib::MdibAccessWeakPtr& mdibAccess,
                const DFL::NotNull<std::shared_ptr<OperationInvokerQueue>>& operationInvokerQueue,
                const std::string& deviceIdentifierForLogPurposes);
};

inline DFL::NotNull<std::unique_ptr<OperationInvoker>> OperationInvokerFactory::create(
        const DFL::Mdib::MdibAccessWeakPtr& mdibAccess,
        const DFL::NotNull<std::shared_ptr<OperationInvokerQueue>>& operationInvokerQueue,
        const std::string& deviceIdentifierForLogPurposes)
{
    return DFL::asNotNull(std::make_unique<Impl::OperationInvokerImpl>(mdibAccess, operationInvokerQueue, deviceIdentifierForLogPurposes));
}

}
