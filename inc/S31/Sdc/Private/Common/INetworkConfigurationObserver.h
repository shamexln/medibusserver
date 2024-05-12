#pragma once

namespace S31::Sdc::Impl
{

/**
 * Observer for network configuration changes.
 * \ingroup S31SdcCommon
 */
class INetworkConfigurationObserver
{
    public:
        virtual ~INetworkConfigurationObserver() = default;

        virtual void onChange() = 0;
};

}
