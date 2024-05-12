#pragma once

#include <S31/Sdc/Private/Client/Endpoint/HostedServiceExecutor.h>
#include <S31/Sdc/Private/Client/Metadata/DeviceMetadata.h>
#include <S31/Sdc/Private/Client/Metadata/ServiceId.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/EnumClass.h>

#include <map>

namespace S31::Sdc::Impl
{

/**
 * @brief Port types processable by S31.
 * @details
 * **Port types** refers to *port types* from WSDL. See https://www.w3.org/TR/wsdl.html#_porttypes.
 *
 * For the values see *IEEE Std 11073-10207-2017 7.3 Service Model*
 * @ingroup S31SdcClient
 */
enum class PortType
{
    GetService,             //!< Get Service
    SetService,             //!< Set Service
    ContextService,         //!< Context Service
    DescriptionEventService,//!< Description Event Service
    StateEventService,      //!< State Event Service
    WaveformService,        //!< Waveform Service
    LocalizationService     //!< Localization Service
};

DFL_ENUM_CLASS_STREAM_OPERATOR(PortType, (GetService)(SetService)(ContextService)(DescriptionEventService)(StateEventService)(WaveformService)(LocalizationService))

/**
 * @brief Mapping of the \ref PortType enum value to \ref Endpoint::HostedServiceExecutor "executors".
 * @details Extracts all executors from a map of executors and relates them to port types. All SDC port types are supported.
 * @ingroup S31SdcClient
 */
class S31_CORE_EXPIMP PortTypeExecutors
{
    public:
        /**
         * @brief Default constructors with no mapped executors.
         */
        PortTypeExecutors();

        /**
         * @brief Constructor that accepts metadata and executors.
         * @details Immediately maps all available port types to executors.
         */
        PortTypeExecutors(const DeviceMetadata& metadata, const std::map<ServiceId, Endpoint::HostedServiceExecutor>& executors);

        /**
         * @brief Find executor that matches a port type.
         * @return The executor if a suitable one found for the given port type, otherwise \c boost::none.
         */
        boost::optional<Endpoint::HostedServiceExecutor> executor(PortType portType) const;

    private:
        std::map<PortType, Endpoint::HostedServiceExecutor> m_executors;
};

}
