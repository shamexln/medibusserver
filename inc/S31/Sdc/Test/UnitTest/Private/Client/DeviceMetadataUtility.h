#pragma once

#include <S31/Sdc/Private/Client/Endpoint/HostedServiceExecutor.h>
#include <S31/Sdc/Private/Client/Metadata/DeviceMetadata.h>
#include <S31/Sdc/Private/Client/Metadata/ServiceId.h>
#include <S31/Sdc/Private/Common/Endpoint/ResettableUrlList.h>
#include <S31/Sdc/Test/Public/Device/HostedServiceMetadataMock.h>

#include <Framework/Utils/Public/Uri.h>

#include <set>
#include <string>
#include <utility>

namespace S31::Sdc::Test
{

/**
 * @brief Reflects hosted service data as used for the \ref DeviceMetadataUtility.
 */
struct HostedServicesData
{

    NtStringView                                    serviceId;
    std::set<std::pair<NtStringView, NtStringView>> portTypes;  // QName; first is namespace, second is name
    std::vector<S31::Sdc::Impl::Endpoint::Url>      physicalAddresses;
};

/**
 * @brief Helper class to generate device metadata and executors for testing purposes.
 */
class DeviceMetadataUtility
{
    public:
        static S31::Sdc::Impl::DeviceMetadata createDeviceMetadata(const DFL::Net::Uri& eprAddress,
                                                                   const std::vector<HostedServicesData>& hostedServices);

        static std::map<S31::Sdc::Impl::ServiceId, S31::Sdc::Impl::Endpoint::HostedServiceExecutor> createExecutors(const std::vector<HostedServicesData>& hostedServices);

        static std::map<S31::Sdc::Impl::ServiceId, S31::Sdc::Impl::Endpoint::HostedServiceExecutor> createExecutors(const std::vector<HostedServicesData>& hostedServices,
                                                                                                                    const std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue>& jobQueue);
};

inline S31::Sdc::Impl::DeviceMetadata DeviceMetadataUtility::createDeviceMetadata(
        const DFL::Net::Uri& eprAddress, const std::vector<HostedServicesData>& hostedServices)
{
    auto deviceMetadata = S31::Sdc::Impl::DeviceMetadata(eprAddress);
    for (const auto& hostedServiceData : hostedServices)
    {
        auto hsMetadata = std::make_shared<S31::Sdc::Impl::Test::HostedServiceMetadataMock>(
            hostedServiceData.serviceId,
            hostedServiceData.portTypes);
        deviceMetadata.addHostedService(hsMetadata);
    }
    return deviceMetadata;
}

inline std::map<S31::Sdc::Impl::ServiceId, S31::Sdc::Impl::Endpoint::HostedServiceExecutor> DeviceMetadataUtility::createExecutors(const std::vector<HostedServicesData>& hostedServices)
{
    return createExecutors(hostedServices, std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue>());
}

inline std::map<S31::Sdc::Impl::ServiceId, S31::Sdc::Impl::Endpoint::HostedServiceExecutor> DeviceMetadataUtility::createExecutors(const std::vector<HostedServicesData>& hostedServices,
                                                                                                                                   const std::weak_ptr<S31::Sdc::Impl::IOutgoingJobQueue>& jobQueue)
{
    std::map<S31::Sdc::Impl::ServiceId, S31::Sdc::Impl::Endpoint::HostedServiceExecutor> executors;

    for (const auto& hostedServiceData : hostedServices)
    {
        auto urlList = DFL::asNotNull(std::make_shared<S31::Sdc::Impl::Endpoint::ResettableUrlList>(hostedServiceData.physicalAddresses));
        auto executor = S31::Sdc::Impl::Endpoint::HostedServiceExecutor(urlList, jobQueue);
        executors.insert(std::make_pair(S31::Sdc::Impl::ServiceId(std::string{hostedServiceData.serviceId}), executor));
    }

    return executors;
}

}
