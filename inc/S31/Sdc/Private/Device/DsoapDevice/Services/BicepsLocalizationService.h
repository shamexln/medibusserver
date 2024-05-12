#pragma once

#include <S31/Localization/S31Only/Device/LocalizedTextStoreImpl.h>
#include <S31/Sdc/Private/Common/IWebService.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LatestMdibSmartPtrTypes.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapGetServiceBindingService.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Realization of the BICEPS Localization service.
 * @details This service handles requests for localized text strings and languages supported by the device.
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP BicepsLocalizationService: public S31::Sdc::Impl::IWebService
{
    public:
        /**
         * @details BICEPS Localization service requires a
         * - \ref S31::Localization::Device::LocalizedTextStoreImpl to make localization calls and a
         * - local MDIB for the MdibVersionGroup attributes inherited from AbstractGetResponse.
         */
        BicepsLocalizationService(const DFL::Mdib::LatestMdibSharedPtr& latestMdib,
                                  std::weak_ptr<Localization::Device::LocalizedTextStoreImpl> textStore);

        int dispatch(struct soap* soapHandle) override;

    private:
        DFL::Mdib::LatestMdibWeakPtr m_latestMdib;
        std::weak_ptr<Localization::Device::LocalizedTextStoreImpl> m_localizedTextStore;
};

}
