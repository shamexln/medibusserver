#pragma once

#include <S31/Localization/Public/Device/LocalizedTextStore.h>

#include <Framework/Mdib/Public/MdibEntityRange.h>

#include <deque>
#include <memory>

namespace DFL::Mdib
{
class LocationContext;
class Mds;
}

namespace S31::Sdc::Impl
{

class ILocalEventing;

/**
 * @brief Helper class to set appropriate discovery location at a local device.
 * @ingroup S31SdcDevice
 */
class LocalDeviceUpdater
{
    public:
        /**
         * Extract associated location states from location context and set them at given device as discovery locations.
         */
        static void setDiscoveryLocation(ILocalEventing& device, const DFL::Mdib::MdibEntityRange<DFL::Mdib::LocationContext>& locationRange);

        /**
         * Get Mds information to set in device discovery scopes. Includes Types and metadata info like Manufacturer, ModelName and DeviceName
         */
        static void setMdsDiscoveryInfo(ILocalEventing& device, const DFL::Mdib::MdibEntityRange<DFL::Mdib::Mds>& mdsRange, const std::shared_ptr<Localization::Device::LocalizedTextStore>& textStore);
};

}
