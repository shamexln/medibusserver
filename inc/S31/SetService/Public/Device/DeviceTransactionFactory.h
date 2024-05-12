#pragma once

#include <S31/SetService/Public/Device/DeviceTransaction.h>

#include <Framework/Mdib/Public/Model/Handle.h>

namespace S31::SetService
{

/**
 * @brief Interface definition of factory to create \ref DeviceTransaction instances.
 * @ingroup S31SetServiceDevice
 */
class DeviceTransactionFactory
{
    public:
        virtual ~DeviceTransactionFactory() = default;

        /**
         * @brief Create new instance based on a given operation handle.
         */
        virtual DFL::NotNull<std::unique_ptr<SetService::DeviceTransaction>> create(const DFL::Mdib::Handle& operationHandle,
                                                                                    const Safety::Context& safetyContext,
                                                                                    const Safety::DualChannel& dualChannel,
                                                                                    const SetService::ClientInformation& clientInfo,
                                                                                    const DFL::Mdib::ExtensionTypes& serviceExtensions) = 0;
};

}
