#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/LanguageTag.h>
#include <Framework/Utils/Public/Uri.h>
#include <Framework/Utils/Public/Utf8.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{

class IHostedServiceMetadata;

/**
 * Stores information about a DPWS device and makes them via getter available
 *
 * \ingroup S31SdcClientMetadata
 */
class S31_CORE_EXPIMP DeviceMetadata
{
    public:
        using LocalizedTextsMap = std::map<DFL::Locale::LanguageTag, DFL::Locale::Utf8>;

        explicit DeviceMetadata(const DFL::Net::Uri& eprAddress); // NOLINT(modernize-pass-by-value)

        /**
         * The Endpoint Reference Address of a DPWS device is typically a UUID in urn format.
         *
         * E.g., urn:uuid:9e01b26f-c400-4dd4-92c6-5a1c230c42d7
         */
        DFL::Net::Uri eprAddress() const;

        /**
         * @name Model
         * To express device characteristics that are typically fixed across all devices of the same model by their manufacturer.
         * <a href="http://docs.oasis-open.org/ws-dd/dpws/1.1/os/wsdd-dpws-1.1-spec-os.html#_Toc228672093">Specification</a> for ThisModel data elements.
         */
        ///@{

        /// NB: Manufacturer may be a localized string.
        DFL::Locale::Utf8 manufacturer() const;
        const LocalizedTextsMap& manufacturerMap() const;
        DFL::Locale::Utf8 manufacturerUrl() const;

        /// User-friendly name for this model of device chosen by the manufacturer.
        /// NB: May be a localized string.
        DFL::Locale::Utf8 modelName() const;
        const LocalizedTextsMap& modelNameMap() const;

        DFL::Locale::Utf8 modelNumber() const;
        DFL::Locale::Utf8 modelUrl() const;
        DFL::Locale::Utf8 presentationUrl() const;

        ///@}


        /**
         * @name Device
         * To express device characteristics that typically vary from one device to another of the same kind.
         * <a href="http://docs.oasis-open.org/ws-dd/dpws/1.1/os/wsdd-dpws-1.1-spec-os.html#_Toc228672093">Specification</a> for ThisDevice data elements.
         */
        ///@{
        /// NB: The friendly name may be a localized string.
        DFL::Locale::Utf8 friendlyName() const;
        DFL::Locale::Utf8 firmwareVersion() const;
        /// Manufacturer-assigned serial number.
        DFL::Locale::Utf8 serialNumber() const;
        ///@}

        /**
         * Hosted services the DPWS device is offering.
         *
         * Details are in <a href="http://docs.oasis-open.org/ws-dd/dpws/1.1/os/wsdd-dpws-1.1-spec-os.html#_Toc228672094">DPWS&nbsp;1.1 section&nbsp;4.2</a>.
         */
        std::vector<std::shared_ptr<S31::Sdc::Impl::IHostedServiceMetadata>> hostedServices() const;

        void eprAddress(const DFL::Net::Uri& eprAddress);
        void addManufacturer(const DFL::Locale::Utf8& name, const DFL::Locale::LanguageTag& lang);
        void manufacturerUrl(const DFL::Locale::Utf8& url);
        void addModelName(const DFL::Locale::Utf8& name, const DFL::Locale::LanguageTag& lang);
        void modelNumber(const DFL::Locale::Utf8& modelNumber);
        void modelUrl(const DFL::Locale::Utf8& url);
        void presentationUrl(const DFL::Locale::Utf8& url);

        void friendlyName(const DFL::Locale::Utf8& name, const DFL::Locale::LanguageTag& lang);
        void firmwareVersion(const DFL::Locale::Utf8& firmwareVersion);
        void serialNumber(const DFL::Locale::Utf8& serialNumber);
        void addHostedService(const std::shared_ptr<S31::Sdc::Impl::IHostedServiceMetadata>& hostedService);

    private:
        static DFL::Locale::Utf8 getDefaultFromMap(const LocalizedTextsMap& map);

        DFL::Net::Uri m_eprAddress;

        // ThisModel
        LocalizedTextsMap m_manufacturer;
        DFL::Locale::Utf8 m_manufacturerUrl;
        LocalizedTextsMap m_modelName;
        DFL::Locale::Utf8 m_modelNumber;
        DFL::Locale::Utf8 m_modelUrl;
        DFL::Locale::Utf8 m_presentationUrl;

        // ThisDevice
        LocalizedTextsMap m_friendlyName;
        DFL::Locale::Utf8 m_firmwareVersion;
        DFL::Locale::Utf8 m_serialNumber;

        // Hosted Services
        std::vector<std::shared_ptr<S31::Sdc::Impl::IHostedServiceMetadata> > m_hostedServices;
};

}
