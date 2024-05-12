#pragma once

#include <S31/Gsoap/S31Only/stdsoap2.h>
#include <S31/Sdc/Private/Common/IWebService.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Interface that plug-ins have to implement for extension.
 *
 * \ingroup S31SdcDevice
 */
class IHostedServicePlugin: public S31::Sdc::Impl::IWebService
{
public:
    /**
     * @brief Called when DPWS is stopped.
     * @details Could be used to gracefully shutdown.
     *
     */
    virtual void deviceShuttingDown();

    /**
     * @brief Plug-In name for debug purposes.
     */
    virtual std::string pluginName() const = 0;
};

inline void IHostedServicePlugin::deviceShuttingDown()
{
}

}
