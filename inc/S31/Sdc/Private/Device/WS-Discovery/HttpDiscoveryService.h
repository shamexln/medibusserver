#pragma once

#include <S31/Gsoap/S31Only/generated/gsoap/soapDiscoveryBindingService.h>

#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31::Sdc::Impl
{
class DpwsDevice;

/**
 * @brief Handling for incoming directed Probe messages.
 *
 * \ingroup S31SdcDevice
 */
class HttpDiscoveryService: private DiscoveryBindingService
{
    public:
        // gSOAP assign and copy do not work as expected (Coverity findings)
        HttpDiscoveryService(const HttpDiscoveryService&) = delete;
        HttpDiscoveryService(HttpDiscoveryService&&) = delete;
        HttpDiscoveryService& operator=(const HttpDiscoveryService&) = delete;
        HttpDiscoveryService& operator=(HttpDiscoveryService&&) = delete;

        HttpDiscoveryService(struct soap* soapHandle, DFL::NotNull<std::shared_ptr<DpwsDevice>> device);
        ~HttpDiscoveryService() override = default;

        int dispatch() override;
        int dispatch(struct soap* soapDispatch) override;

    private:
        /**
         * @brief Do not use!
         * @details
         * Copy is not supported by gSOAP. S31 does not want to add copy support. Thus, this class is not copyable.
         */
        DiscoveryBindingService* copy() override;

        int ProbeOp(wsd11__ProbeType*) override;

        DFL::NotNull<std::shared_ptr<DpwsDevice>> m_device;
};

}
