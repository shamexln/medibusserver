#pragma once

#include <S31/Sdc/Private/Device/DsoapDevice/ILocalEventing.h>
#include <S31/Sdc/Private/Device/SetService/DsoapDeviceTransaction.h>
#include <S31/SetService/Public/Common/TransactionId.h>
#include <S31/SetService/Public/Device/ClientInformation.h>
#include <S31/SetService/Public/Device/DeviceTransactionFactory.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <atomic>
#include <cstdint>
#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Web service specific implementation of S31::SetService::DeviceTransactionFactory.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP DsoapDeviceTransactionFactory: public SetService::DeviceTransactionFactory
{
    public:
        DsoapDeviceTransactionFactory(DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::ILocalEventing>> eventing,
                                      DFL::NotNull<DFL::Mdib::LatestMdibSharedPtr> latestMdib);

        DFL::NotNull<std::unique_ptr<SetService::DeviceTransaction>> create(const DFL::Mdib::Handle& operationHandle,
                                                                            const Safety::Context& safetyContext,
                                                                            const Safety::DualChannel& dualChannel,
                                                                            const SetService::ClientInformation& clientInfo,
                                                                            const DFL::Mdib::ExtensionTypes& serviceExtensions) override;

    private:
        DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::ILocalEventing>> m_eventing;
        DFL::NotNull<DFL::Mdib::LatestMdibSharedPtr>                  m_latestMdib;
        std::atomic<uint32_t> m_transactionId;

        SetService::TransactionId createTransactionId();
};

}
