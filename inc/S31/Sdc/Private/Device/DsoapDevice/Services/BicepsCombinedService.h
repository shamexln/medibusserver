#pragma once

#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
namespace SetService
{
class ScoController;
}
namespace Sdc
{
class DualChannelFactoryManager;
namespace Impl
{
class SubscriberInfo;

/**
 * \brief Implementation of all high priority Biceps services combined into one hosted endpoint.
 *
 * This class forwards service requests to the appropriate service based on the given soap action.
 * Will handle dispatch requests for GetService, SetService and ContextService.
 *
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP BicepsCombinedService: public S31::Sdc::Impl::IWebService
{
    public:
        BicepsCombinedService(
                DFL::Mdib::LatestMdibSharedPtr                           latestMdib,
                DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>> dualChannelFactoryManager,
                std::weak_ptr<SetService::ScoController>                 scoController,
                std::weak_ptr<Sdc::Impl::SubscriberInfo>                 subscriberInfo);

        /**
         * Implementation of S31::Sdc::Impl::IWebService.
         *
         * Is used to dispatch incoming SOAP web service requests.
         */
        int dispatch(struct soap* soapHandle) override;

    private:
        DFL::Mdib::LatestMdibSharedPtr m_latestMdib;
        DFL::NotNull<std::shared_ptr<DualChannelFactoryManager>> m_dualChannelFactoryManager;
        std::weak_ptr<SetService::ScoController> m_scoController;
        std::weak_ptr<Sdc::Impl::SubscriberInfo> m_subscriberInfo;
};

}
}
}
