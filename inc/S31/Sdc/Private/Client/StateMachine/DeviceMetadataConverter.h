#pragma once

#include <S31/Sdc/Private/Client/Metadata/DeviceMetadata.h>
#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Creates %DpwsDeviceMetadata out of \ref DeviceMetadata.
 * @ingroup S31SdcClient
 */
class DeviceMetadataConverter
{
    public:
        static DpwsDeviceMetadata toDpwsDeviceMetadata(const DeviceMetadata& deviceMetadata);
};

inline DpwsDeviceMetadata DeviceMetadataConverter::toDpwsDeviceMetadata(const DeviceMetadata& deviceMetadata)
{
    Sdc::DpwsDeviceMetadata ddm;
    ddm.manufacturerName(deviceMetadata.manufacturer());
    ddm.manufacturerNameLanguage(boost::none);
    ddm.manufacturerUrl(deviceMetadata.manufacturerUrl());
    ddm.modelName(deviceMetadata.modelName());
    ddm.modelNameLanguage(boost::none);
    ddm.modelNumber(deviceMetadata.modelNumber());
    ddm.modelUrl(deviceMetadata.modelUrl());
    ddm.presentationUrl(deviceMetadata.presentationUrl());
    ddm.deviceName(deviceMetadata.friendlyName());
    ddm.deviceVersion(deviceMetadata.firmwareVersion());
    ddm.deviceSerialNumber(deviceMetadata.serialNumber());
    return ddm;
}

}
