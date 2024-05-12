#pragma once

#include <S31/Safety/Public/Requirement.h>
#include <S31/Sdc/Public/Common/DefaultConfiguration.h>
#include <S31/Sdc/Public/Device/LocalMdibAccessSmartPtrTypes.h>
#include <S31/Sdc/Public/Device/MedicalDeviceData.h>
#include <S31/Startup/S31Only/IS31App.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/MdibObserver.h>
#include <Framework/Utils/Public/CompilerGenerated.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/Utf8.h>

#include <memory>
#include <vector>

namespace S31
{
namespace Sdc
{
class IDispatcher;
class Client;
class LocalDevice;
}

namespace Localization::Device
{
class LocalizedTextStore;
}

class S31CoreFactory;
class S31Service;
class LocationService;
class MeasurementService;
class CommandLineOptions;
class WaveformService;
class SettingService;
class AlertService;
class IDeviceHandler;
class IJobQueue;

/**
 * \brief Implementation of \ref S31::IS31App for the SDC network protocol.
 * \ingroup S31Startup
 */
class SdcApp: public S31::IS31App
{
        DFL_NOT_COPYABLE(SdcApp)

    public:
        /**
         * @brief Enum to configure SdcApp.
         * @details This can be used to explicitly make client/device functionality unavailable.
         */
        enum class ApplicationMode
        {
            ClientAndDevice,
            DeviceOnly
        };

        SdcApp(DFL::NotNull<std::shared_ptr<S31CoreFactory>> s31CoreFactory,
               std::shared_ptr<S31::IDeviceHandler>          deviceHandler,
               const CommandLineOptions&                     commandLineOptions,
               Sdc::MedicalDeviceData                        medicalDeviceData,
               ApplicationMode                               mode,
               DFL::Locale::Utf8                             friendlyName = DefaultConfiguration::friendlyName());

        ~SdcApp() noexcept override;

        void doCreateDeviceApplication(bool readMdib) override;
        void start() override;
        void stop() override;

        void createLocationService(DFL::NotNull<std::shared_ptr<ILocationHandler>> locationHandler) override;
        void createMeasurementService(std::shared_ptr<IMeasurementHandler> handler) override;
        void createWaveformService(std::shared_ptr<IWaveformHandler> handler) override;
        void createSettingService(const std::shared_ptr<ISettingHandler>& handler) override;
        void createAlertService(const std::shared_ptr<IAlertHandler>& handler) override;

        std::shared_ptr<S31::SetService::InvocationCallbackRegistry> invocationCallbackRegistry() override;
        std::shared_ptr<S31::Sdc::LocalDevice> getLocalDevice() override;
        std::shared_ptr<S31::Sdc::Client> getBicepsClient() override;

        std::shared_ptr<Sdc::DiscoveryProvider> getDiscoveryProvider() override;
        std::shared_ptr<Sdc::RemoteDevicesSubject> getCommunicationNodeSubject() override;

        void startServices() override;
        void stopServices() override;

        void readMdibFile();

    private:

        [[nodiscard]] Sdc::EndpointReference endpointReference() const;

        void internalStop();
        void internalCreateLocationService(DFL::NotNull<std::shared_ptr<ILocationHandler>> locationHandler);

        void resetLocationService();

        void updateMedicalDeviceInfoInFirstMds();

        DFL::NotNull<std::shared_ptr<S31CoreFactory>> m_coreFactory;
        const CommandLineOptions& m_options;
        std::shared_ptr<IDeviceHandler> m_deviceHandler;
        std::shared_ptr<Sdc::LocalDevice> m_dpwsDevice;
        Sdc::MedicalDeviceData m_medicalDeviceData;
        std::shared_ptr<Sdc::IDispatcher> m_dispatcher;
        std::shared_ptr<IJobQueue> m_scheduler;

        std::shared_ptr<Sdc::Client> m_bicepsClient;

        std::vector<std::shared_ptr<S31Service> > m_services;

        std::shared_ptr<MeasurementService> m_measurementService;
        std::shared_ptr<LocationService> m_locationService;
        std::shared_ptr<ILocationHandler> m_locationHandler;
        std::shared_ptr<WaveformService> m_waveformService;
        std::shared_ptr<SettingService> m_settingService;
        std::shared_ptr<AlertService> m_alertService;

        std::shared_ptr<Sdc::RemoteDevicesSubject> m_commNodeSubject;
        const DFL::Locale::Utf8 m_friendlyName;
        bool m_isCommNodeSubjectDistributedToServices = false;
        bool m_running = false;
};

DFL_ENUM_CLASS_STREAM_OPERATOR(SdcApp::ApplicationMode, (ClientAndDevice)(DeviceOnly))

}
