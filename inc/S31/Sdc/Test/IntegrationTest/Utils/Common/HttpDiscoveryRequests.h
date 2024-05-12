#pragma once

#include <S31/Gsoap/S31Only/SoapFwd.h>
#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/Common/HttpTypes.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/DiscoveryProxy/DeviceInformation.h>

namespace S31::Sdc::Impl::Test
{

namespace DiscoveryRequests
{

HttpRequest requestWithNoSoapBody(
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

HttpRequest helloMsg(
        const DeviceProperties::DiscoveryInfo& device,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

HttpRequest byeMsg(
        const DeviceProperties::DiscoveryInfo& device,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

HttpRequest probeMsg(
        const QNameList& types,
        const WSDiscoveryScopes& scopes,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

HttpRequest resolveMsg(
        const EndpointReference& epr,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

HttpRequest probeMatchMsg(
        const DiscoveryInformationMap& device,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

HttpRequest resolveMatchMsg(
        const DeviceProperties::DiscoveryInfo& device,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

std::string probe(
        struct soap* soap,
        const QNameList& types,
        const WSDiscoveryScopes& scopes,
        const DFL::Net::Uri& targetUrl = DFL::Net::Uri("http://dummy/"));

std::string probeMatch(
        struct soap* soap,
        const DiscoveryInformationMap& devices);

std::string resolveMatch(
        struct soap* soap,
        const boost::optional<DeviceProperties::DiscoveryInfo>& device);

}

}
