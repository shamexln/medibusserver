#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/CompilerGenerated.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapMetadataExchangeBindingService.h>

#include <memory>

namespace S31::Sdc::Impl
{
class DpwsDevice;
class HostedService;

/**
 * @brief Implementation of WS-MetadataExchange and dispatching to IMetadataListener.
 *
 * \ingroup S31SdcCommonWebServices
 */
class S31_CORE_EXPIMP MexService : private MetadataExchangeBindingService
{
        // gSOAP assign and copy do not work as expected (Coverity findings)
        DFL_NOT_COPYABLE(MexService)
    public:
        MexService(struct soap* soap, std::shared_ptr<DpwsDevice> device, std::shared_ptr<HostedService> service);

        int dispatch() override;
        int dispatch(struct soap* soapDispatch) override;

    private:
        MetadataExchangeBindingService* copy() override;
        int GetMetadata(_wsx4__GetMetadata*, _wsx4__Metadata&) override;
        int GetMetadataResponse(_wsx4__Metadata*) override;

        std::shared_ptr<DpwsDevice> m_device;
        std::shared_ptr<HostedService> m_service;

};

}
