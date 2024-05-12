#pragma once

#include <S31/Sdc/Public/Client/RemoteDevicesSubject.h>
#include <S31/Sdc/Public/Common/DefaultConfiguration.h>
#include <S31/Sdc/Public/Common/S31CoreFactory.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Sdc/Public/Device/MedicalDeviceData.h>
#include <S31/SetService/Public/Device/InvocationCallbackRegistry.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Utils/Public/NotNull.h>

#include <memory>

namespace S31
{
class CommandLineOptions;
class IDeviceHandler;
class ISettingHandler;
class ILocationHandler;
class IMeasurementHandler;
class IAlertHandler;
class IWaveformHandler;

namespace Sdc
{
class DiscoveryProvider;
class LocalDevice;
class RemoteDevicesSubject;
}

/**
 * \brief Entry point for \ref S31UseCases "Use Case Services".
 *
 * \details It brings up the network communication.
 *
 * \ingroup S31Startup
 */
class S31_CORE_EXPIMP IS31App
{
public:

    virtual ~IS31App() noexcept = default;

    /**
     * \brief Factory method to create instance of IS31App.
     *
     * \details Both Client and Device functionality are enabled. To create a device application call \ref
     * S31::IS31App::createDeviceApplication.
     *
     * \param coreFactory Factory for core related application building, and parameterization like SSL configuration and
     * used port numbers. ('things between OS/network an S31') \param options Command line information for configuration
     * \param deviceHandler Device handler for initial metadata retrieval.
     * \param medicalDeviceData MDIB with additional information
     * \param friendlyName Friendly name of device
     */
    static DFL::NotNull<std::unique_ptr<IS31App>> createSdcApp(
            DFL::NotNull<std::shared_ptr<S31CoreFactory>> coreFactory,
            std::shared_ptr<IDeviceHandler>               deviceHandler,
            const CommandLineOptions&                     options,
            Sdc::MedicalDeviceData                        medicalDeviceData,
            const DFL::Locale::Utf8&                      friendlyName = DefaultConfiguration::friendlyName());

    /**
     * \brief Factory method to create instance of IS31App.
     *
     * \details The application will only provide device functionality while client functionality is disabled.
     * To create a device application call \ref S31::IS31App::createDeviceApplication.
     *
     * \param coreFactory Factory for core related application building, and parameterization like SSL configuration and
     * used port numbers. ('things between OS/network an S31') \param options Command line information for configuration
     * \param deviceHandler Device handler for initial metadata retrieval.
     * \param medicalDeviceData MDIB with additional information
     * \param friendlyName Friendly name of device
     */
    static DFL::NotNull<std::unique_ptr<IS31App>> createSdcAppDeviceOnly(
            DFL::NotNull<std::shared_ptr<S31CoreFactory>> coreFactory,
            std::shared_ptr<IDeviceHandler>               deviceHandler,
            const CommandLineOptions&                     options,
            Sdc::MedicalDeviceData                        medicalDeviceData,
            const DFL::Locale::Utf8&                      friendlyName = DefaultConfiguration::friendlyName());

    /**
     * @name Device related services
     */
    ///@{

    /**
     * @brief Add device side support in the S31 application.
     */
    void createDeviceApplication(bool readMdib);

    /**
     * @brief Returns a registry for SetService callbacks.
     *
     * @returns InvocationCallbackRegistry A registry for setService callbacks.
     */
    virtual std::shared_ptr<S31::SetService::InvocationCallbackRegistry> invocationCallbackRegistry() = 0;

    virtual std::shared_ptr<S31::Sdc::LocalDevice> getLocalDevice() = 0;
    virtual std::shared_ptr<S31::Sdc::Client> getBicepsClient() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    ///@}

    /**
     * @name Generic services
     */
    ///@{
    virtual void createLocationService(DFL::NotNull<std::shared_ptr<S31::ILocationHandler>> locationHandler) = 0;
    virtual void createMeasurementService(std::shared_ptr<IMeasurementHandler> handler) = 0;
    virtual void createWaveformService(std::shared_ptr<IWaveformHandler> handler) = 0;
    virtual void createSettingService(const std::shared_ptr<ISettingHandler>& handler) = 0;
    virtual void createAlertService(const std::shared_ptr<IAlertHandler>& handler) = 0;
    ///@}

    virtual void startServices() = 0;
    virtual void stopServices() = 0;

    /**
     * get the interfaces of the services interfaces for configuration
     */
    ///@{
    /// \returns May return an empty object.
    virtual std::shared_ptr<Sdc::DiscoveryProvider> getDiscoveryProvider() = 0;

    /// @return Observable subject that the app use to observe for online/offline calls.
    virtual std::shared_ptr<Sdc::RemoteDevicesSubject> getCommunicationNodeSubject() = 0;
    ///@}

    private:
        virtual void doCreateDeviceApplication(bool readMdib) = 0;
};

} /* namespace S31 */
