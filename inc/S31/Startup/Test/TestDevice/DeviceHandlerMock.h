#pragma once

#include <S31/UseCases/S31Only/IDeviceHandler.h>

#include <Framework/Mdib/Public/Model/Component/MetaData.h>

#include <string>

namespace S31 {

class DeviceHandlerMock: public IDeviceHandler
{
    public:
        DeviceHandlerMock();
        virtual ~DeviceHandlerMock();

        /**
         * \overload
         * \see S31::IDeviceHandler
         */
        void start() override;

        /**
         * \overload
         * \see S31::IDeviceHandler
         */
        void stop() override;

        /**
         * \overload
         * \see S31::IDeviceHandler
         */
        DFL::Mdib::MetaData provideMedicalDeviceInfo() override;

        Sdc::DpwsDeviceMetadata provideCommunicationNodeInfo() override;

        /**
         * \overload
         * \see S31::IDeviceHandler
         */
        boost::optional<Sdc::EndpointReference> endpointReference() const override;

        S31::Sdc::MetadataVersion getMetadataVersion() override;
        void setNodeInfo(const Sdc::DpwsDeviceMetadata& info);
    private:

        boost::optional<Sdc::EndpointReference> m_epr;
        Sdc::DpwsDeviceMetadata m_nodeInfo;
};

} /* namespace S31 */
