#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/LanguageTag.h>

#include <boost/optional/optional.hpp>

namespace S31::Sdc
{

/**
 * @brief DPWS device characteristics for the communication endpoint.
 * @ingroup S31SdcCommon
 */
class DpwsDeviceMetadata
{
    public:
        /**
         * @name Manufacturer name
         */
        ///@{
        DFL::Locale::Utf8 manufacturerName() const;
        void manufacturerName(const DFL::Locale::Utf8& m);
        ///@}

        /**
         * @name Manufacturer name language
         */
        ///@{
        boost::optional<DFL::Locale::LanguageTag> manufacturerNameLanguage() const;
        void manufacturerNameLanguage(const boost::optional<DFL::Locale::LanguageTag>& manufacturerNameLanguage);
        ///@}

        /**
         * @name Manufacturer URL
         * URL to a Web site for the manufacturer.
         */
        ///@{
        DFL::Locale::Utf8 manufacturerUrl() const;
        void manufacturerUrl(const DFL::Locale::Utf8& m);
        ///@}

        /**
         * @name Model Name
         * User-friendly name for this model of device chosen by the manufacturer.
         */
        ///@{
        DFL::Locale::Utf8 modelName() const;
        void modelName(const DFL::Locale::Utf8& m);
        ///@}

        /**
         * @name Model name language
         */
        ///@{
        boost::optional<DFL::Locale::LanguageTag> modelNameLanguage() const;
        void modelNameLanguage(const boost::optional<DFL::Locale::LanguageTag>& modelNameLanguage);
        ///@}

        /**
         * @name Model Number
         */
        ///@{
        DFL::Locale::Utf8 modelNumber() const;
        void modelNumber(const DFL::Locale::Utf8& m);
        ///@}


        /**
         * @name Model URL
         * URL to a Web site for this model.
         */
        ///@{
        DFL::Locale::Utf8 modelUrl() const;
        void modelUrl(const DFL::Locale::Utf8& m);
        ///@}

        /**
         * @name Presentation URL
         * URL to a presentation resource.
         *
         * If PresentationUrl is specified, the device may provide the resource in
         * multiple formats, but must at least provide an HTML page.
         * Clients and devices may use HTTP content negotiation to determine the
         * format and content of the presentation resource.
         *
         * Devices that use a relative URL may use HTTP Redirection 3xx codes to
         * direct clients to a dedicated web server running on another port.
         */
        ///@{
        DFL::Locale::Utf8 presentationUrl() const;
        void presentationUrl(const DFL::Locale::Utf8& p);
        ///@}

        /**
         * @name Device Name
         * User-friendly name for this individual instance.
         *
         * In contrast to the model name (that is applicable for multiple devices)
         * this name is for this individual device instance.
         */
        ///@{
        DFL::Locale::Utf8 deviceName() const;
        void deviceName(const DFL::Locale::Utf8& n);
        ///@}

        /**
         * @name Firmware version
         */
        ///@{
        DFL::Locale::Utf8 deviceVersion() const;
        void deviceVersion(const DFL::Locale::Utf8& v);
        ///@}

        /**
         * @name Serial Number
         * Manufacturer-assigned serial number.
         */
        ///@{
        DFL::Locale::Utf8 deviceSerialNumber() const;
        void deviceSerialNumber(const DFL::Locale::Utf8& s);
        ///@}

    private:
        DFL::Locale::Utf8 m_manufacturerName;
        boost::optional<DFL::Locale::LanguageTag> m_manufacturerNameLanguage;
        DFL::Locale::Utf8 m_manufacturerUrl;
        DFL::Locale::Utf8 m_modelName;
        boost::optional<DFL::Locale::LanguageTag> m_modelNameLanguage;
        DFL::Locale::Utf8 m_modelNumber;
        DFL::Locale::Utf8 m_modelUrl;
        DFL::Locale::Utf8 m_presentationUrl;
        DFL::Locale::Utf8 m_deviceName;
        DFL::Locale::Utf8 m_deviceVersion;
        DFL::Locale::Utf8 m_deviceSerialNumber;
};

inline DFL::Locale::Utf8 DpwsDeviceMetadata::deviceName() const
{
    return m_deviceName;
}

inline void DpwsDeviceMetadata::deviceName(const DFL::Locale::Utf8& n)
{
    m_deviceName = n;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::deviceSerialNumber() const
{
    return m_deviceSerialNumber;
}

inline void DpwsDeviceMetadata::deviceSerialNumber(const DFL::Locale::Utf8& s)
{
    m_deviceSerialNumber = s;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::deviceVersion() const
{
    return m_deviceVersion;
}

inline void DpwsDeviceMetadata::deviceVersion(const DFL::Locale::Utf8& v)
{
    m_deviceVersion = v;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::manufacturerName() const
{
    return m_manufacturerName;
}

inline void DpwsDeviceMetadata::manufacturerName(const DFL::Locale::Utf8& m)
{
    m_manufacturerName = m;
}

inline boost::optional<DFL::Locale::LanguageTag> DpwsDeviceMetadata::manufacturerNameLanguage() const
{
    return m_manufacturerNameLanguage;
}

inline void DpwsDeviceMetadata::manufacturerNameLanguage(const boost::optional<DFL::Locale::LanguageTag>& manufacturerNameLanguage)
{
    m_manufacturerNameLanguage = manufacturerNameLanguage;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::manufacturerUrl() const
{
    return m_manufacturerUrl;
}

inline void DpwsDeviceMetadata::manufacturerUrl(const DFL::Locale::Utf8& m)
{
    m_manufacturerUrl = m;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::modelName() const
{
    return m_modelName;
}

inline void DpwsDeviceMetadata::modelName(const DFL::Locale::Utf8& m)
{
    m_modelName = m;
}

inline boost::optional<DFL::Locale::LanguageTag> DpwsDeviceMetadata::modelNameLanguage() const
{
    return m_modelNameLanguage;
}

inline void DpwsDeviceMetadata::modelNameLanguage(const boost::optional<DFL::Locale::LanguageTag>& modelNameLanguage)
{
    m_modelNameLanguage = modelNameLanguage;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::modelNumber() const
{
    return m_modelNumber;
}

inline void DpwsDeviceMetadata::modelNumber(const DFL::Locale::Utf8& m)
{
    m_modelNumber = m;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::modelUrl() const
{
    return m_modelUrl;
}

inline void DpwsDeviceMetadata::modelUrl(const DFL::Locale::Utf8& m)
{
    m_modelUrl = m;
}

inline DFL::Locale::Utf8 DpwsDeviceMetadata::presentationUrl() const
{
    return m_presentationUrl;
}

inline void DpwsDeviceMetadata::presentationUrl(const DFL::Locale::Utf8& p)
{
    m_presentationUrl = p;
}

inline bool operator==(const DpwsDeviceMetadata& lhs, const DpwsDeviceMetadata& rhs) noexcept
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.presentationUrl() == rhs.presentationUrl()
           && lhs.modelUrl() == rhs.modelUrl()
           && lhs.modelNumber() == rhs.modelNumber()
           && lhs.modelName() == rhs.modelName()
           && lhs.modelNameLanguage() == rhs.modelNameLanguage()
           && lhs.manufacturerName() == rhs.manufacturerName()
           && lhs.manufacturerNameLanguage() == rhs.manufacturerNameLanguage()
           && lhs.manufacturerUrl() == rhs.manufacturerUrl()
           && lhs.deviceVersion() == rhs.deviceVersion()
           && lhs.deviceName() == rhs.deviceName()
           && lhs.deviceSerialNumber() == rhs.deviceSerialNumber();
}

inline bool operator!=(const DpwsDeviceMetadata& lhs, const DpwsDeviceMetadata& rhs) noexcept
{
    return !(lhs == rhs);
}

}
