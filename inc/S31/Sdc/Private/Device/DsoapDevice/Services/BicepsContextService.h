#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::SetService
{
class ScoController;
}

namespace S31::Sdc
{
class DualChannelFactoryManager;

namespace Impl
{
class ISoapContextPool;
class LocalDevice;
class SubscriberInfo;

/**
 * @brief Service implementation for context information in the \ref Mdib.
 *
 * @details
 * This service class handles sensible information of the patient and other
 * context relevant information which are useful to get further information
 * of a patient using the device. The ContextService shall transfer its data
 * in a secured way to the peer.
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP BicepsContextService: public S31::Sdc::Impl::IWebService
{
    public:
        BicepsContextService(std::weak_ptr<SetService::ScoController> scoController,
                             DFL::Mdib::LatestMdibWeakPtr latestMdib,
                             DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>> dualChannelFactoryManager,
                             std::weak_ptr<Sdc::Impl::SubscriberInfo> subscriberInfo);

        /**
         * @brief Implementation of S31::Sdc::Impl::IWebService.
         *
         * @details Is used to dispatch incoming web service requests.
         */
        int dispatch(struct soap* soapHandle) override;

    private:
        std::weak_ptr<SetService::ScoController> m_scoController;
        std::weak_ptr<Sdc::Impl::SubscriberInfo> m_subscriberInfo;
        DFL::Mdib::LatestMdibWeakPtr m_latestMdib;
        DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>> m_dualChannelFactoryManager;
};

}
}
