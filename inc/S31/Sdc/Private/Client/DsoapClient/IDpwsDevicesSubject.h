#pragma once

namespace S31::Sdc::Impl
{
class IDpwsDeviceObserver;

/**
 * @brief Interface for DPWS devices registry.
 *
 * @ingroup S31SdcClient
 */
class IDpwsDevicesSubject
{
    public:
        virtual ~IDpwsDevicesSubject() = default;

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual void registerObserver(const std::shared_ptr<IDpwsDeviceObserver>& observer) = 0;

        virtual void connectUrn(const std::string& urn) = 0;
        virtual void disconnectUrn(const std::string& urn) = 0;

};

}
