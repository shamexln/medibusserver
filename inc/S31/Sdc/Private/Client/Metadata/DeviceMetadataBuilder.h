#pragma once

#include <S31/Sdc/Public/Common/EndpointReference.h>

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>

#include <memory>

namespace S31::Sdc::Impl
{
class DeviceMetadata;

/**
 * Creates DPWS meta data in structures from \ref gSOAP format.
 *
 * \ingroup S31SdcClientMetadata
 */
class DeviceMetadataBuilder
{
    public:
        static S31::Sdc::Impl::DeviceMetadata createFromSections(const std::vector<std::shared_ptr<_wsx4__MetadataSection>>& sections, const EndpointReference& epr);

    private:
        static void addSection(DeviceMetadata& container, const _wsx4__MetadataSection& entry);
        static void setThisModel(DeviceMetadata& container, const dpws__ThisModelType& model);
        static void setThisDevice(DeviceMetadata& container, const dpws__ThisDeviceType& device);
        static void addRelationship(DeviceMetadata& container, const _dpws__Relationship& entry);
        static void addHostService(DeviceMetadata& container, const dpws__HostServiceType& hostService);
        static void addHostedService(DeviceMetadata& container, const dpws__HostedServiceType& hostedService);

};

}
