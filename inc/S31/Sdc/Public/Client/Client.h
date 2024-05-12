#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesProvider.h>
#include <S31/Sdc/Public/Common/InstanceIdentifiersUtil.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace S31::Sdc
{
class DiscoveryProvider;

/**
 * @brief Specify the initial probing of SDC client.
 * @ingroup S31SdcClient
 */
enum class InitialProbe
{
        /**
         * @brief Probe for all SDC device in the network.
         * @details It searches really for all independent of any location.
         */
        SearchAll,

        /**
         * @brief No initial search at all.
         * @details
         * The customer is free to start whatever probe is appropriate for the current use case.
         */
        None
};

/**
 * @brief %Client is the central access point in order to discover and connect remote SDC devices.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP Client
{
    public:
        virtual ~Client() noexcept = default;

        /**
         * @brief Provides the @ref DiscoveryProvider of the client to monitor the detected
         * devices in the network.
         *
         * @details The @ref DiscoveryProvider allows to register an observer for found devices in the
         * network and it can be used to send probe messages.
         */
        virtual std::shared_ptr<DiscoveryProvider> discoveryProvider() const = 0;

        /**
         * @brief Provides the @ref RemoteDevicesProvider which allows to get the %MDIB and
         * other information from connected devices.
         */
        virtual std::shared_ptr<RemoteDevicesProvider> remoteDevicesProvider() const = 0;

        /**
         * @brief Deprecated, there is no semantic for client start.
         * @deprecated Function is noop and will be removed.
         */
        static void start(InitialProbe probe = InitialProbe::SearchAll);

        /**
         * @brief Deprecated, there is no semantic for client stop.
         * @deprecated Function is noop and will be removed.
         */
        virtual void stop();
};

}
