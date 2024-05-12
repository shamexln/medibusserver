#pragma once

namespace S31::Sdc::Impl
{

/**
 * @brief Interface that observers of HostedService must implement to get
 * notified in case of metadata changes.
 *
 * @ingroup S31SdcDevice
 */
class IHostedServiceUpdateListener
{
    public:
        virtual ~IHostedServiceUpdateListener() = default;

        virtual void hostedServiceUpdated() = 0;
};

}
