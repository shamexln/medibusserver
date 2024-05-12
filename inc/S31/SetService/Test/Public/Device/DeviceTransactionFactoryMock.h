#pragma once

#include <S31/SetService/Public/Device/DeviceTransactionFactory.h>
#include <S31/SetService/Test/Public/Device/DeviceTransactionMock.h>

#include <Framework/Mdib/Public/MdibFactory.h>

#include <cstdint>

namespace S31::SetService::Test
{

/**
 * @brief Mock class to create mock device transactions.
 * @ingroup S31SetServiceDevice
 */
class DeviceTransactionFactoryMock: public DeviceTransactionFactory
{
    public:
        DeviceTransactionFactoryMock();
        DFL::NotNull<std::unique_ptr<SetService::DeviceTransaction>> create(const DFL::Mdib::Handle& operationHandle,
                                                                            const Safety::Context& safetyContext,
                                                                            const Safety::DualChannel& dualChannel,
                                                                            const SetService::ClientInformation& clientInfo,
                                                                            const DFL::Mdib::ExtensionTypes& serviceExtensions) override;

    private:
        std::uint32_t m_lastTransactionId;
};

inline DeviceTransactionFactoryMock::DeviceTransactionFactoryMock() :
        m_lastTransactionId(0)
{
}

inline DFL::NotNull<std::unique_ptr<SetService::DeviceTransaction>> DeviceTransactionFactoryMock::create(const DFL::Mdib::Handle& /* operationHandle */,
                                                                                                         const Safety::Context& safetyContext,
                                                                                                         const Safety::DualChannel& dualChannel,
                                                                                                         const SetService::ClientInformation& clientInfo,
                                                                                                         const DFL::Mdib::ExtensionTypes& serviceExtensions)
{
    return DFL::asNotNull(std::unique_ptr<SetService::DeviceTransaction>(new DeviceTransactionMock(
            TransactionId(++m_lastTransactionId),
            safetyContext,
            dualChannel,
            clientInfo,
            serviceExtensions)));
}

}
