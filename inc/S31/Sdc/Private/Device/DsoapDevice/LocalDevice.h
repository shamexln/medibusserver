#pragma once

#include <S31/BicepsXml/S31Only/MdibChangesSerializer.h>
#include <S31/Localization/S31Only/Device/LocalizedTextStoreImpl.h>
#include <S31/S31CoreExImp.h>
#include <S31/Safety/Public/Requirement.h>
#include <S31/Sdc/Private/Common/ParticipantKeyPurposeMapper.h>
#include <S31/Sdc/Private/Device/DsoapDevice/ILocalEventing.h>
#include <S31/Sdc/Private/Device/History/HistoryEventingPlugin.h>
#include <S31/Sdc/Private/Device/MetaDataChangesObserver.h>
#include <S31/Sdc/Private/Device/SetService/DsoapDeviceTransactionFactory.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriberInfo.h>
#include <S31/Sdc/Private/Device/WS-Eventing/SubscriptionCounter.h>
#include <S31/Sdc/Public/Common/CompressionConfiguration.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Public/Common/MetadataVersion.h>
#include <S31/Sdc/Public/Device/ClientSubscriptionObserver.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Sdc/Public/Device/LocalMdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Public/Device/MedicalDeviceData.h>
#include <S31/Sdc/Public/Device/MedicalDpwsData.h>
#include <S31/SetService/Public/Common/TransactionId.h>
#include <S31/Utils/Public/ObservableSubject.h>

#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>

#include <atomic>
#include <memory>

namespace S31
{
namespace History
{
class Service;
}
namespace SetService
{
class ScoController;
}

namespace Sdc::Impl
{
class CommunicationEndpoint;
class DpwsDevice;
class IOutgoingMessage;
class WSEventingPlugin;
class MdibChangesPublisher;
class LocalDeviceEventing;

/**
 * @brief This class implements all stuff to act as a SDC device.
 *
 * @details It is a DPWS device that has BICEPS GET, SET, ... services
 * and contains the local MDIB representation.
 * Based on this MDIB all BICEPS network events are generated
 * by subscribing as a MdibChangeListener.
 *
 * @ingroup S31SdcDevice
 */
class S31_CORE_EXPIMP LocalDevice: public ILocalEventing, public Sdc::LocalDevice, public std::enable_shared_from_this<LocalDevice>
{
    DFL_NOT_COPYABLE(LocalDevice)

    public:
        LocalDevice(
                MedicalDpwsData                                                      dpwsData,
                MedicalDeviceData                                                    medicalData,
                DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::CommunicationEndpoint>> communicationEndpoint,
                DFL::NotNull<std::shared_ptr<CoreConfiguration>>                     config);

        ~LocalDevice() noexcept override;

        const S31::Sdc::EndpointReference& epr() const override;

        bool isRunning() const override;

        void init();
        void start() override;
        void stop() override;

        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> localMdibAccess() const override;

        bool hasEventListenerForAction(std::string_view actionUri) const override;
        bool hasEventListenerForAnyAction() const override;
        void fireEvent(DFL::NotNull<std::unique_ptr<S31::Sdc::Impl::IOutgoingMessage>> event) override;
        void setDiscoveryLocationScopes(const std::vector<std::string>& locations) override;
        void setDiscoveryMdsInfoScopes(const std::vector<std::string>& scopes) override;

        // Used for transport layer information, mostly used by Coco. Update the Mdib for Mds info changes/discovery scope changes.
        void dpwsDeviceMetadata(const Sdc::DpwsDeviceMetadata& deviceInfo) override;

        DFL::NotNull<std::shared_ptr<SetService::InvocationCallbackRegistry>> invocationCallbackRegistry() const override;

        std::shared_ptr<Localization::Device::LocalizedTextStore> localizedTextStore() const override;
        std::shared_ptr<History::Service>                         historyService() const override;

        S31::Sdc::MedicalDeviceData& medicalDeviceData() override;

        void registerSubscriptionInfoObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer) override;
        void unregisterSubscriptionInfoObserver(const std::shared_ptr<ClientSubscriptionObserver>& observer) override;
        ClientSubscriptions subscriptions() const override;

        void onComponentReportCompleted(
                const DFL::Mdib::MdibVersion&                      version,
                std::function<void(const DFL::Mdib::MdibVersion&)> callback) override;
        void componentReportDeliveryStarting(const DFL::Mdib::MdibVersion& version) override;
        void componentReportDeliveryCompleted(const DFL::Mdib::MdibVersion& version) noexcept override;
        void sendHello() override;

    private:
        bool isCertificateValid();

        void internalStop();

        void setDpwsDeviceInfo();

        //Creates Context, Descriptor, Get, State, Waveform and Set services
        void createBicepsServices();
        void createHistoryServiceIfAvailable();
        void createLocalizationServiceIfAvailable();

        std::vector<std::string> createDiscoveryScopes() const;

        void addParticipantKeyPurposes(const DFL::Oids& keyPurposes);

        void copySubscriptionInfoObservers(const DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::WSEventingPlugin>>& newEventingPlugin) const;

        DFL::NotNull<std::shared_ptr<LocalDeviceEventing>> m_localDeviceEventing;

        DFL::NotNull<std::shared_ptr<Sdc::Impl::CommunicationEndpoint>> m_communicationEndpoint;
        MedicalDpwsData m_dpwsData;
        MedicalDeviceData m_medicalData;
        std::shared_ptr<MdibChangesPublisher> m_mdibChangesPublisher;
        std::shared_ptr<Sdc::Impl::MetaDataChangesObserver> m_metaDataObserver;

        SharedSubscriptionCounter m_subscriptionCounter;
        std::shared_ptr<S31::Sdc::Impl::DpwsDevice> m_dpwsDevice;
        std::vector<DFL::NotNull<std::shared_ptr<S31::Sdc::Impl::WSEventingPlugin>>> m_eventingPlugins;
        std::shared_ptr<HistoryEventingPlugin> m_historyEventingPlugin;
        std::shared_ptr<Sdc::Impl::SubscriberInfo> m_operationInvokedService;
        class MediaLossReporter;
        std::shared_ptr<MediaLossReporter> m_mediaLossReporter;

        DFL::NotNull<DFL::NotNull<std::shared_ptr<CoreConfiguration>>> m_config;

        DFL::NotNull<std::shared_ptr<Sdc::Impl::DsoapDeviceTransactionFactory>> m_deviceTransactionFactory;
        DFL::NotNull<std::shared_ptr<SetService::ScoController>> m_scoController;

        std::set<std::string> m_pkpTypes;
        std::vector<std::string> m_locationScopes;
        std::vector<std::string> m_mdsScopes;

        S31::Utils::ObservableSubjectDelegate<ClientSubscriptionObserver> m_subscriptionInfoObservableSubject;

        using SubscriptionInfoObservers = std::set<std::weak_ptr<ClientSubscriptionObserver>, std::owner_less<std::weak_ptr<ClientSubscriptionObserver>>>;
        static void removeNonLockableItems(SubscriptionInfoObservers& observers);
        mutable std::mutex m_subscriptionInfoObserversMutex;
        SubscriptionInfoObservers m_subscriptionInfoObservers;

        mutable std::mutex m_mdibUpdateReportObserverMutex;
        std::map<DFL::Mdib::VersionCounter, std::vector<std::function<void(const DFL::Mdib::MdibVersion&)>>> m_componentReportCompletionObservers;
};

}
}
