#pragma once

#include <S31/Sdc/Private/Common/Messaging/QNameList.h>

#include <memory>
#include <string>

namespace S31::Sdc::Impl
{

class IRemoteHostedServiceEndpoint;

/**
 * Container for DPWS hosted service metadata.
 *
 * \ingroup S31SdcClientMetadata
 */
class IHostedServiceMetadata
{
    public:
        virtual ~IHostedServiceMetadata() = default;

        virtual std::string getServiceId() const = 0;
        virtual bool hasType(const DFL::QName& type) const = 0;
        virtual std::shared_ptr<S31::Sdc::Impl::IRemoteHostedServiceEndpoint> getRemoteEndpoint() const = 0;
        virtual const QNameList& qNameList() const = 0;

};

}
