#pragma once

#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>

#include <vector>
#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Observer interface for discovered devices.
 *
 * @details This interface is used by the @ref DpwsDiscovery to inform
 * observers of discovery information of medical dpws devices.
 *
 * @ingroup S31SdcDiscovery
 */
class IDpwsDiscoveryObserver
{
    public:
        virtual ~IDpwsDiscoveryObserver() noexcept = default;

        /**
         * @brief Callback method for discovered devices.
         */
        virtual void foundDevice(const EndpointReference& epr,
                                 const S31::Sdc::Impl::QNameList& types,
                                 const std::vector<std::string>& scopes,
                                 const std::string& xAddrs,
                                 S31::Sdc::MetadataVersion metadataVersion,
                                 const std::string& remoteIp) = 0;

        /**
         * @brief Got WS-Discovery @c bye message.
         */
        virtual void byeFromDevice(const EndpointReference& epr) = 0;
};

}
