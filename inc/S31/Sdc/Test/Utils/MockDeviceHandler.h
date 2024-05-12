#pragma once

#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>
#include <S31/UseCases/S31Only/IDeviceHandler.h>

#include <Framework/Mdib/Public/Model/Component/MetaData.h>

#include <string>

namespace S31
{

class IDeviceTransfer;

class S31_CORE_IT_UTIL_EXPIMP MockDeviceHandler: public IDeviceHandler
{
    public:

        /**
         * Constructor.
         */
        MockDeviceHandler();

        /**
         * Destructor.
         */
        virtual ~MockDeviceHandler();

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

        void setCommunicationNodeInfo(const Sdc::DpwsDeviceMetadata& info);

    private:
        boost::optional<S31::Sdc::EndpointReference> m_epr;
        Sdc::DpwsDeviceMetadata m_deviceInfo;
};

} /* namespace S31 */
