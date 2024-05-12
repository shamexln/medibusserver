#pragma once

#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/Component/MetaData.h>

#include <string>

namespace S31
{
/**
 * This interface declares the feature set of the device
 * worker in the specific device implementation.
 *
 * \ingroup S31UseCases
 */
class S31_CORE_EXPIMP IDeviceHandler
{
    public:
        virtual ~IDeviceHandler() noexcept = default;

        /**
         * Starts the device handler.
         */
        virtual void start() = 0;
        /**
         * Stops the device handler.
         */
        virtual void stop() = 0;

        /**
         * Provides the device information for the SDC model.
         *
         * @returns the system meta data
         */
        virtual DFL::Mdib::MetaData provideMedicalDeviceInfo() = 0;

        /**
         * Provides the device information for the DPWS info.
         *
         * @returns the communication node info
         */
        virtual Sdc::DpwsDeviceMetadata provideCommunicationNodeInfo() = 0;

        /**
         * Returns the WS-Discovery EndpointReference of the device (DPWS-1.1 R0004).
         *
         * @returns the EndpointReference of the device.
         */
        virtual boost::optional<Sdc::EndpointReference> endpointReference() const = 0;

        /**
         * @brief Returns WS-Discovery metadata version.
         * @details The version shall never decrement and shall increment with each
         * WS-Discovery metadata change. How this is ensured, (can be) implementation specific.
         *
         * @returns the metadata version
         */
        virtual S31::Sdc::MetadataVersion getMetadataVersion() = 0;

};

} /* namespace S31 */
