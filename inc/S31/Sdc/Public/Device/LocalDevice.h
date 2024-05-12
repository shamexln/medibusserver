#pragma once

#include <S31/Localization/Public/Device/LocalizedTextStore.h>
#include <S31/Sdc/Public/Common/DpwsDeviceMetadata.h>
#include <S31/Sdc/Public/Common/EndpointReference.h>
#include <S31/Sdc/Public/Device/ClientSubscriptionObserver.h>
#include <S31/Sdc/Public/Device/MedicalDeviceData.h>
#include <S31/Sdc/Public/Device/SubscriptionInfo.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <functional>
#include <memory>

namespace S31::BicepsXml
{
class XmlReportObserver;
}

namespace S31::History
{
class Service;
}

namespace S31::Sdc
{

/**
 * @brief Main interface for a local SDC device.
 *
 * @details An object of this class allows to provide information
 * for other devices in the SDC network. In most cases there
 * is one instance per physical medical device in the network.
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP LocalDevice
{
    public:
        virtual ~LocalDevice() noexcept = default;

        /**
         * @name Device meta data
         */
        ///@{

        /**
         * @brief Gets the endpoint reference of the device.
         */
        virtual const EndpointReference& epr() const = 0;

        /**
         * @brief Metadata of the (network) communication node.
         *
         * It may be the same metadata as for the medical device itself (MDS SystemMetadata) or
         * can be different meta data in case of a separate communication node.
         */
        virtual void dpwsDeviceMetadata(const DpwsDeviceMetadata& deviceInfo) = 0;

        ///@}

        /**
         * @name Life-cycle
         *
         * The network communication can be started and stopped for the biceps device.
         */
        ///@{

        /**
         * @brief Makes the device available in the network.
         * @details It announces itself with a Hello and provides its %MDIB.
         */
        virtual void start() = 0;

        /**
         * @brief Leaves the network.
         * @details Device does not response to any network requests anymore.
         */
        virtual void stop() = 0;

        /**
         * @brief Check if device is available in the network.
         */
        virtual bool isRunning() const = 0;

        /**
         * @brief Register a callback for completion of an %Mdib component report with a specific @ref
         * DFL::Mdib::MdibVersion.
         *
         * @details Caller provides a function to execute when an %Mdib component update report has finished delivery to
         * all WS-Eventing subscribers, or when delivery is not possible (e.g. no subscribers).
         *
         * @param version The specific %Mdib version to monitor.
         * @param callback The callback function to run when the %Mdib component update report is completed.
         */
        virtual void onComponentReportCompleted(
                const DFL::Mdib::MdibVersion& version, std::function<void(const DFL::Mdib::MdibVersion&)> callback) = 0;
        ///@}

        /**
         * @brief Retrieve an invocation callback registry to register for incoming set operation calls.
         */
        virtual DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>> invocationCallbackRegistry() const = 0;

        /**
         * @name Mdib
         *
         * Access to the device's MDIB and created change reports.
         */
        ///@{

        /**
         * @brief Provides the Mdib currently configured for the local biceps device.
         * @return reference to the current MDIB of the device.
         */
        virtual DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> localMdibAccess() const = 0;

        ///@}

        /**
         * @brief Provides a store for localized texts if localization is supported by the device
         * @return Localized text storage of device if supported, @e nullptr if not.
         */
        virtual std::shared_ptr<Localization::Device::LocalizedTextStore> localizedTextStore() const = 0;

        /**
         * @brief Provides access to the passed in history service (if available).
         */
        virtual std::shared_ptr<History::Service> historyService() const = 0;

        /**
         * @brief Provides the originally injected medical device data.
         */
        virtual S31::Sdc::MedicalDeviceData& medicalDeviceData() = 0;

        /**
         * @name Client subscription information
         *
         * Changes to the device's client subscriptions are notified to
         * @ref S31::Sdc::ClientSubscriptionObserver "ClientSubscriptionObservers".
         * Subscriptions may be polled following the event notification to retrieve the current subscription status.
         */
        ///@{

        /**
         * @brief Register an observer for client subscription updates.
         * @details Updates are notified in case of any subscription changes.
         * @param observer The listener to be registered
         */
        virtual void registerSubscriptionInfoObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer) = 0;

        /**
         * @brief Removes an observer for client subscription updates.
         * @param observer the listener to be removed
         */
        virtual void unregisterSubscriptionInfoObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer) = 0;

        /**
         * @brief Returns the active subscriptions.
         */
        virtual ClientSubscriptions subscriptions() const = 0;
        ///@}

        /**
         * @brief Sends a hello.
         */
        virtual void sendHello() = 0;
};

}
