#pragma once

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Public/Client/RemoteDevicesObserver.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Common/EndpointReferenceIo.h>
#include <S31/Sdc/Public/Common/ErrorDefinitions.h>
#include <S31/Sdc/Test/Utils/TestDevice.h>
#include <S31/Sdc/Test/Utils/s31core_it_utils_exp_imp.h>

#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibConstraints.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <chrono>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
#include <vector>

namespace S31::Sdc::Test
{

/**
 * @brief Creates a uuid from the given uuid (-pattern).
 * @details Used to generate uuid of the following pattern:
 *  urn:uuid:a8eb656c-642c-4e6f-9c16-aaaaaaa10000 (with index == 0)
 *  urn:uuid:a8eb656c-642c-4e6f-9c16-aaaaaaa10001 (with index == 1)
 *  ...
 *
 * @param index last part of the generated uuid (random index)
 * @param uuidPattern used for the (random) prefix (may throw std::out_of_range if this pattern is not a uuid/long enough)
 */
S31::Sdc::EndpointReference makeEndpointReference(int index, const std::string& uuidPattern);

using EndpointReferences = std::vector<S31::Sdc::EndpointReference>;

/// Creates a range of endpoint references like {urn:uuid:a8eb656c-642c-4e6f-9c16-aaaaaaa10000, urn:uuid:a8eb656c-642c-4e6f-9c16-aaaaaaa10001, ...}
EndpointReferences makeEndpointReferences(int numberOfElements, const std::string& uuidPattern);

/// Order for @ref S31::Sdc::EndpointReference, for e.g. std::map.
struct CompareEndpointReference
{
    bool operator()(const S31::Sdc::EndpointReference& lhs, const S31::Sdc::EndpointReference& rhs) const
    {
        return lhs.address().str() < rhs.address().str();
    }
};

namespace Impl
{
struct NumberOfThreadsPerDeviceTag;
}

/// to control the number of threads in the single devices
using NumberOfThreadsPerDevice =  DFL::StrongTypedef<unsigned int, Impl::NumberOfThreadsPerDeviceTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable, DFL::Skill::LessThanComparable>;

/**
 * @brief Holds a given number of started devices.
 */
class S31_CORE_IT_UTIL_EXPIMP TestDevices
{
    public:

        using DevicePtr = DFL::NotNull<std::shared_ptr<S31::Sdc::Test::TestDevice>>;
        using DeviceContainer = std::map<S31::Sdc::EndpointReference, DevicePtr, CompareEndpointReference>;

        /// Creates this class with 0 devices.
        TestDevices() = default;

        /// ctor, creates and starts the according devices.
        TestDevices(
                unsigned int numberOfDevicesToStart,
                const CoreConfiguration& configuration,
                const DFL::Mdib::MdibChangeSet& initialMdib = DFL::Mdib::MdibChangeSet(),
                const std::shared_ptr<S31::Localization::Device::LocalizedTextStore>& store = nullptr,
                const DFL::Mdib::MdibConstraints& constraints = DFL::Mdib::MdibConstraints::allConstraints(),
                const std::optional<NumberOfThreadsPerDevice>& numberOfThreads = std::nullopt);

        /// mutable reference to the devices
        DeviceContainer& devices();

        const DeviceContainer& devices() const;

        const EndpointReferences endpointReferences() const;
    private:
        void startOneDevice(const EndpointReference& epr,
                const DFL::Mdib::MdibChangeSet& initialChangeSet,
                boost::optional<DFL::Chrono::Milliseconds> customAppMaxDelay,
                const boost::optional<S31::CoreConfiguration>& coreConfiguration,
                const DFL::Mdib::MdibConstraints& withConstraints,
                const std::shared_ptr<S31::Localization::Device::LocalizedTextStore>& store,
                const std::optional<NumberOfThreadsPerDevice>& numberOfThreads);

        std::chrono::milliseconds m_waitTimeBetweenDeviceStart = std::chrono::milliseconds(50);
        DeviceContainer m_devices;
};

/// Can be used by a client that connects to some @ref TestDevices for tracking.
class S31_CORE_IT_UTIL_EXPIMP RemoteDevicesWatcher: public S31::Sdc::RemoteDevicesObserver
{
    public:
        void online(const DFL::NotNull<std::shared_ptr<S31::Sdc::RemoteDevice>>& remoteDevice) override;

        void offline(const S31::Sdc::EndpointReference& epr, const S31::Utils::Error& error) override;

        int onlineDevices() const;

        int errorDevices() const;

        std::string errorMessages() const;
        void clearErrorMessages();
    private:
        mutable std::mutex m_mutex;
        int m_onlineDevices{0};
        int m_errorDevices{0};
        std::vector<std::string> m_errors;
        std::set<EndpointReference, CompareEndpointReference> m_connectedNodes;
};

}
