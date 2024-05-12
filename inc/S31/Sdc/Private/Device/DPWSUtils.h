#pragma once

#include <S31/Gsoap/S31Only/generated/gsoap/soapStub.h>
#include <S31/S31CoreExImp.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>

#include <Framework/Utils/Public/LanguageTag.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/NotNull.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace S31::Sdc::Impl
{
class DpwsDevice;
class HostedService;
class NetworkInterfaceManager;

/**
 * \brief Helper function for the DpwsDevice class.
 *
 * \ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP DPWSUtils
{
    public:
        static int dispatchDevice(struct soap* soapHandle, DFL::NotNull<std::shared_ptr<DpwsDevice>> device);
        static int dispatchServiceOfDevice(struct soap* soapHandle, const std::shared_ptr<DpwsDevice>& device, const std::shared_ptr<HostedService>& service);
        static int handleProbe(wsd11__ProbeMatchesType& probeMatches,
                               const DFL::NotNull<std::shared_ptr<DpwsDevice>>& device,
                               struct soap* soapHandle,
                               const S31::Sdc::Impl::QNameList& types,
                               const std::vector<std::string>& scopes,
                               const std::string& matchBy,
                               const std::shared_ptr<NetworkInterfaceManager>& networkInterfaceManager);

        static int handleProbe(wsd11__ProbeMatchesType& probeMatches,
                               const DFL::NotNull<std::shared_ptr<DpwsDevice>>& device,
                               struct soap* soapHandle,
                               const S31::Sdc::Impl::QNameList& types,
                               const std::vector<std::string>& scopes,
                               const std::string& matchBy);

        static void fillLocWithMap(std::vector<std::shared_ptr<dpws__LocalizedStringType>>& loc, const std::map<DFL::Locale::LanguageTag, DFL::Locale::Utf8>& map);
        static void addThisModelMetadataSection(const DpwsDevice& device, _wsx4__Metadata* metadata);
        static void addThisDeviceMetadataSection(const DpwsDevice& device, _wsx4__Metadata* metadata);
        static std::shared_ptr<_dpws__Relationship> addRelationShipMetadataSection(const DpwsDevice& device, _wsx4__Metadata& metadata);
        static void addRelationShipMetadataSectionForOneService(
                struct soap* soapHandle,
                const DpwsDevice& device,
                const std::shared_ptr<HostedService>& service,
                _wsx4__Metadata& metadata);
        static void addHostedServiceType(
                struct soap* soapHandle,
                const DpwsDevice& device,
                const std::shared_ptr<HostedService>& service,
                const std::shared_ptr<_dpws__Relationship>& relationship);

        static std::string createSoapOverUdpAddressForSoapPeer(struct soap* soapHandle);

        static std::string createXaddress(struct soap* soapHandle, const DpwsDevice& device,
                NetworkInterfaceManager& networkInterfaceManager);

};

}
