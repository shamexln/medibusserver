#pragma once

namespace S31::Sdc::Impl
{

/**
 * Callback interface for network (cable) connect/disconnect.
 * @ingroup S31SdcCommon
 */
class INetworkMediaObserver
{
    public:
        virtual ~INetworkMediaObserver() = default;

        virtual void lastMediaDisconnected() = 0;
        virtual void firstMediaConnected() = 0;
};

}
