#pragma once

#include <S31/History/Public/InMemoryHistoryService.h>
#include <S31/Localization/Public/Device/LocalizedTextStore.h>
#include <S31/Sdc/Public/Common/MdibChangesSerializeStorer.h>
#include <S31/Sdc/Public/Device/MdibChangesStorer.h>
#include <S31/Sdc/Public/Discovery/DiscoveryProvider.h>
#include <S31/Sdc/Public/Discovery/LocationContextDiscovery.h>
#include <S31/Sdc/S31Only/CommandLineOptions.h>
#include <S31/Sdc/Test/Utils/MockLocationHandler.h>
#include <S31/SetService/Public/Device/InvocationCallbacks.h>

#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>
#include <Framework/Mdib/Public/Model/Context/PatientContextState.h>
#include <Framework/Mdib/Public/Model/Metric/MeasurementValidity.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/ChangesProvider.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/RecurringTasks.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/WaveformDataGenerator.h>
#include <Framework/Utils/Public/NotNull.h>

#include <thread>

namespace S31
{
namespace Sdc
{
class IDispatcher;
class LocalDevice;
}
namespace Test
{

enum class LocalizationConfig
{
    ServiceAvailable,
    ServiceUnavailable
};

class LocationsOfOtherDevicesObserver: public S31::Sdc::LocationContextDiscoveryObserver
{
    public:
        // Note: That this LocationContextDiscoveryObserver knows its own registry (LocationContextDiscoveryRegistry) is
        // just to keep this sample simple.
        LocationsOfOtherDevicesObserver(std::weak_ptr<S31::Sdc::LocationContextDiscoveryRegistry> registry):
            m_registry(std::move(registry))
        {}

        void joinsLocation(const Sdc::RemoteDeviceInfo& device) override;
        void leavesLocation(const Sdc::EndpointReference& epr) override;

    private:
        void streamOutDevicesInfo();
        std::weak_ptr<S31::Sdc::LocationContextDiscoveryRegistry> m_registry;


};

/**
 * @brief Sample SDC device for manual testing.
 */
class InteractiveTestDevice
{
    public:
        explicit InteractiveTestDevice(CommandLineOptions options);
        ~InteractiveTestDevice();
        void consoleLoop();

    private:
        static void printHelp();
        DFL::Mdib::LocalizedTexts initMdib(S31::Test::LocalizationConfig lc);
        void loadMdib(const std::string& name);
        void setMetadata();

        void changeLocation();
        void setLocation (const char* txt);

        template<typename T_Builder>
        void writeNumericMetric(const DFL::NotNull<DFL::Mdib::NumericMetricSharedPtr> metric,
                                const T_Builder &builder,
                                bool description=false);

        void setMetricValue(const std::string& handle, int value);
        void changeMetricValidity(const std::string& handle);
        void toggleWaveformValidity();
        void changeMetricAvailability(const std::string& handle);
        void changeMetricGenerationMode(const std::string& handle);
        void changeMetricActivationState(const std::string& handle);
        void changeDeterminationPeriod(const std::string& handle);

        void changePatient();
        static std::string getPatientFullName(const DFL::Mdib::PatientDemographicsCoreData& patientData);

        void changeModel();

        void fillLocationList();
        void fillPatientList();
        void fillModelList();

        void metricUpdateThread();

        void setupMdibChanger();

        void setupLocationContextDiscovery(const DFL::Mdib::LocationDetail& location);

        void shutdownMdsAndWaitReportSent();

        std::atomic_bool m_running;
        int m_paramValue;
        DFL::Locale::Utf8 m_modelName;
        CommandLineOptions m_options;
        std::shared_ptr<S31::Sdc::LocalDevice> m_dpwsDevice;
        DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> m_localMdibAccess;
        std::shared_ptr<Localization::Device::LocalizedTextStore> m_localizedTextStore;
        std::shared_ptr<History::InMemoryHistoryService> m_historyService;
        std::shared_ptr<S31::Test::MockLocationHandler> m_locationHandler;
        std::thread m_metricUpdateThread;

        unsigned int m_nextLocation;
        std::vector<DFL::Mdib::LocationDetail> m_locationList;
        unsigned int m_nextPatient;
        std::vector<DFL::Mdib::PatientContextState> m_patientList;
        unsigned int m_nextModel;
        std::vector<std::string> m_modelList;
        DFL::Mdib::MeasurementValidity m_waveformValidity;
        DFL::Chrono::Milliseconds m_waveformDelay;
        DFL::Chrono::Milliseconds m_waveformDelayIncrement;

        std::shared_ptr<DFL::Mdib::Test::WaveformChanger> m_waveformChanger;
        DFL::Mdib::Test::RecurringTasksScheduler m_mdibChanger;

        std::shared_ptr<S31::SetService::V3::MdsSetStringCallback> m_setStringCallback;
        std::shared_ptr<S31::Sdc::IDispatcher> m_dispatcher;
        std::unique_ptr<S31::Sdc::Experimental::MdibChangesStorer> m_changesStorer;
        std::unique_ptr<S31::Sdc::Experimental::MdibChangesSerializeStorer> m_changesBinaryStorer;

        std::shared_ptr<LocationsOfOtherDevicesObserver> m_locationsOfOtherDevicesObserver;
        std::shared_ptr<S31::Sdc::LocationContextDiscoveryRegistry> m_locationContextDiscoveryRegistry;
        std::shared_ptr<S31::Sdc::DiscoveryProvider> m_discoveryProvider;
};

}
}
