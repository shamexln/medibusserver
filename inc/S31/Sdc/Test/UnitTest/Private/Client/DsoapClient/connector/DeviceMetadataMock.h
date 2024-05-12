#pragma once

#include <S31/Sdc/Private/Client/Metadata/IHostedServiceMetadata.h>

#include <Framework/Utils/Public/Utf8.h>

#include <memory>
#include <vector>

namespace S31::Sdc::Impl::Test
{

class DeviceMetadataMock
{
    public:
        DeviceMetadataMock(const DFL::Locale::Utf8& urn);

        DFL::Locale::Utf8 getEprAddress() const;
        DFL::Locale::Utf8 getManufacturer() const;
        DFL::Locale::Utf8 getManufacturerUrl() const;
        DFL::Locale::Utf8 getModelName() const;

        DFL::Locale::Utf8 getModelNumber() const;
        DFL::Locale::Utf8 getModelUrl() const;
        DFL::Locale::Utf8 getPresentationUrl() const;
        DFL::Locale::Utf8 getFriendlyName() const;
        DFL::Locale::Utf8 getFirmwareVersion() const;
        DFL::Locale::Utf8 getSerialNumber() const;
        std::vector<std::shared_ptr<Sdc::Impl::IHostedServiceMetadata>> getHostedServices() const;

        void addHostedService(const std::shared_ptr<Sdc::Impl::IHostedServiceMetadata>& hostedServiceMetadata);

    private:
        DFL::Locale::Utf8 m_urn;
        std::vector<std::shared_ptr<Sdc::Impl::IHostedServiceMetadata> > m_services;
};

}
