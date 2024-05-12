#pragma once

#include <S31/Sdc/Public/Client/RemoteDevice.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>

#include <memory>

namespace S31::Sdc::Impl
{

/**
 * @brief Write connect/disconnect information into service log.
 * @ingroup S31SdcClient
 */
class OnlineOfflineServiceLogger: public Sdc::RemoteDevicesObserver
{
    public:
        void online(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice) override;
        void offline(const EndpointReference& epr, const S31::Utils::Error& error) override;

};

}
