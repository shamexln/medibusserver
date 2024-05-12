#pragma once

#include <S31/Sdc/Private/Discovery/WS-Discovery/Scopes.h>
#include <S31/Sdc/Private/Common/Messaging/QNameList.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>

#include <Framework/Utils/Public/Uri.h>

#include <boost/algorithm/string/case_conv.hpp>

#include <map>

namespace S31::Sdc::Impl::Test
{
namespace DeviceProperties
{

/**
 * @brief This struct acts as a container for certain information about a device.
 * @details The information collected here is especially relevant for the discovery
 *          process and used in \ref S31::Sdc::Impl::Test::DeviceProperties::DiscoveryInfo
 *          and \ref S31::Sdc::Impl::Test::DiscoveryInformationMap.
 *
 */
struct DeviceCharacteristics
{
    DeviceCharacteristics() = default;
    DeviceCharacteristics(
            QNameList types,
            WSDiscoveryScopes scopes,
            std::vector<DFL::Net::Uri> xAddrs,
            MetadataVersion mv
            ) :
                types(std::move(types)),
                scopes(std::move(scopes)),
                xAddrs(std::move(xAddrs)),
                metadataVersion(std::move(mv))
    {
    }

    QNameList types{};
    WSDiscoveryScopes scopes{};
    std::vector<DFL::Net::Uri> xAddrs{};
    MetadataVersion metadataVersion{S31::Sdc::MetadataVersion{0}};
};

/**
 * @brief This type contains information describing a single DPWS device.
 * @details It is the information about a device that can be obtained via
 *          WS-Discovery messages.
 */
using DiscoveryInfo = std::pair<EndpointReference, DeviceCharacteristics>;

}

/**
 * @brief Custom comparator for \ref S31::Sdc::Impl::Test::DiscoveryInformationMap.
 * @details \S31::Sdc::EndpointReference "Endpoint References" come in the form UUIDSs.
 *          According to <a href="https://tools.ietf.org/html/rfc4122#section-3">RFC 4122</a>,
 *          the canonical representation of UUIDs is in lower case form and comparison of UUIDs
 *          shall be performed after normalization.
 */
struct EprCompare
{
    bool operator()(const EndpointReference& lhs, const EndpointReference& rhs) const
    {

        return boost::to_lower_copy(lhs.address().str()) < boost::to_lower_copy(rhs.address().str());
    }
};

/**
 * @brief This container holds information about multiple DPWS devices.
 * @details It is the information about devices that can be obtained via
 *          WS-Discovery messages.
 */
using DiscoveryInformationMap = std::map<EndpointReference, DeviceProperties::DeviceCharacteristics, EprCompare>;

}
