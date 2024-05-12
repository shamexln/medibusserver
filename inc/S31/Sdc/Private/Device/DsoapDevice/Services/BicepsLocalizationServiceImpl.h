#pragma once

#include <S31/Sdc/Private/Device/DsoapDevice/Services/BicepsBaseService.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Implementation of BicepsGetService.
 * A separate class was created for unit testing.
 * @ingroup S31SdcDevice
 */
class BicepsLocalizationServiceImpl: private BicepsBaseService
{
    public:
        BicepsLocalizationServiceImpl(struct soap* soapHandle,
                                      DFL::Mdib::LatestMdibWeakPtr latestMdib,
                                      std::weak_ptr<Localization::Device::LocalizedTextStoreImpl> textStore);

        int GetLocalizedText(_msg__GetLocalizedText* request, _msg__GetLocalizedTextResponse& response) override;
        int GetSupportedLanguages(_msg__GetSupportedLanguages* request, _msg__GetSupportedLanguagesResponse& response) override;

        int dispatch() override;
        int dispatch(struct soap* soapDispatch) override;

    private:
        static Localization::LocalizedTextFilter gsoapToLocalizedTextFilter(_msg__GetLocalizedText* request) ;

        DFL::Mdib::LatestMdibWeakPtr m_latestMdib;
        std::weak_ptr<Localization::Device::LocalizedTextStoreImpl> m_localizedTextStore;
};

}
