#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriberInfo.h>
#include <S31/SetService/Public/Device/ScoController.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>

#include <memory>

namespace S31::Sdc
{
class DualChannelFactoryManager;
namespace Impl
{

/**
 * \brief Realization of the BICEPS SET service.
 *
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP BicepsSetService: public S31::Sdc::Impl::IWebService
{
    public:
        BicepsSetService(std::weak_ptr<SetService::ScoController> scoController,
                         DFL::Mdib::LatestMdibWeakPtr latestMdib,
                         DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>> dualChannelFactoryManager,
                         std::weak_ptr<Sdc::Impl::SubscriberInfo> subscriberInfo);

        /**
         * \brief Implementation of S31::Sdc::Impl::IWebService.
         *
         * \details Is used to dispatch incoming web service requests.
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
