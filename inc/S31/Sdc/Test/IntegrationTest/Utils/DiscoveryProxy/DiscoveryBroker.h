#pragma once

#include <S31/Sdc/Test/IntegrationTest/Utils/Common/HttpTypes.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/DiscoveryProxy/DeviceInformation.h>
#include <S31/Sdc/Test/IntegrationTest/Utils/DiscoveryProxy/DiscoveryParser.h>

#include <condition_variable>
#include <mutex>

namespace S31::Sdc::Impl
{
class ISoapContextPool;
namespace Test
{

/**
 * @brief This class handles \ref S31::Sdc::Impl::Test::HttpRequest "Discovery Http Requests".
 * @details It reacts to Ws-Discovery Hello, Bye, Probe and Resolve messages
 *          and maintains an internal list of devices discovered in this manner.
 */
class DiscoveryBroker
{
    public:
        using Devices = DiscoveryInformationMap;

        /**
         * @brief default ctor.
         */
        DiscoveryBroker();
        /**
         * @brief ctor with initial device list.
         * @param devices list of devices to initialize internal device list.
         */
        explicit DiscoveryBroker(Devices devices);

        /**
         * @brief handle a \ref S31::Sdc::Impl::Test::HttpRequest "Http Request".
         * @return a \ref S31::Sdc::Impl::Test::HttpResponse "Http Response" depending
         *         on the request.
         */
        HttpResponse handleRequest(const HttpRequest& req);

        /**
         * @brief provides a synchronization primitive in case an update of the device list is expected (e.g. in tests)
         */
         bool waitForDeviceListUpdate(const std::chrono::milliseconds& maxWaitTime);

        /**
         * @brief getter for internal list of \ref Devices.
         */
        const Devices& devices();

        /**
         * @brief call this before performing actions for which changes in the device list are expected.
         * @details A call to @ref waitForDeviceListUpdate() afterwards will be notified correctly.
         */
        void startWaitingForUpdates();

        /**
         * @brief reset the Discovery Broker, i.e. empty the \ref m_devices "internal list of devices".
         */
        void reset();

    private:
        /**
         * @brief Adds device to \ref m_devices.
         * @details In case there exists "newer" information (determined by the \ref S31::Sdc::MetadataVersion "metadata version")
         *          about the device already, the message is discarded.
         */
        HttpResponse hello(
                const DeviceProperties::DiscoveryInfo& device,
                const HttpRequest& req);
        /**
         * @brief Removes a device from \ref m_devices.
         * @details In case the device was not in the list, the message is discarded.
         */
        HttpResponse bye(
                const DeviceProperties::DiscoveryInfo& device,
                const HttpRequest& req);
        /**
         * @brief Gathers information about all devices from \ref m_devices that match the Probe Request.
         * @return Probe Match Response containing information about all devices matching the Probe Request.
         */
        HttpResponse probe(
                const DeviceProperties::DiscoveryInfo& device,
                const std::string& matchBy,
                const HttpRequest& req);
        /**
         * @brief Gather information of the device from \ref m_devices that matches the Resolve Request.
         * @return Resolve Match Response containing information about the device matching the Resolve Request.
         */
        HttpResponse resolve(
                const DeviceProperties::DiscoveryInfo& device,
                const HttpRequest& req);

        Devices m_devices;
        std::shared_ptr<S31::Sdc::Impl::ISoapContextPool> m_soapPool;
        std::mutex m_mutex;
        std::condition_variable m_waitConditionVariable;
        bool m_changed;
};

}
}
