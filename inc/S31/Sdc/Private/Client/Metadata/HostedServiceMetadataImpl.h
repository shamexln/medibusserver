#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Client/Metadata/IHostedServiceMetadata.h>
#include <S31/Sdc/Private/Client/Metadata/RemoteHostedServiceEndpoint.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/S31CoreExImp.h>

#include <memory>

namespace DFL::Net
{
class Uri;
}

namespace S31::Sdc::Impl
{

/**
 * Implementation of IHostedServiceMetadata.
 *
 * \ingroup S31SdcClientMetadata
 */
class S31_CORE_EXPIMP HostedServiceMetadataImpl: public IHostedServiceMetadata
{
    public:
        explicit HostedServiceMetadataImpl(std::string serviceId);

        std::string getServiceId() const override;
        bool hasType(const DFL::QName& type) const override;
        std::shared_ptr<S31::Sdc::Impl::IRemoteHostedServiceEndpoint> getRemoteEndpoint() const override;

        void setTypes(const struct soap* soapHandle, const std::string& types);
        void addRemoteEndpoint(const DFL::Net::Uri& endpoint);

        const QNameList& qNameList() const override;

    private:
        const std::string m_serviceId;
        std::shared_ptr<S31::Sdc::Impl::RemoteHostedServiceEndpoint> m_endpoint;
        QNameList m_types;

};

} /* namespace S31 */
