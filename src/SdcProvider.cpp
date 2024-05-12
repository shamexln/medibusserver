#include "SdcProvider.h"

#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Public/Common/InstanceIdentifierFactory.h>
#include <S31/Sdc/Public/Common/S31CoreFactory.h>
#include <S31/Sdc/Public/Common/ThreadPoolDispatcher.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Sdc/S31Only/S31SystemProperties.h>
#include <S31/Sdc/Test/Public/Common/CoreConfigurationHelper.h> // for test certificates
#include <S31/Utils/Public/MdibAccessUtil.h>

#include <Framework/Crypto/Public/RandomUuidGenerator.h>
#include <Framework/Mdib/Public/MdibFactory.h>
#include <Framework/Mdib/Public/Model/CodedValueConstants.h>
#include <Framework/Mdib/Public/Model/Component/MetaDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientType.h>
#include <Framework/Mdib/Public/Model/Context/Sex.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/CodedAttributes.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/SdpiExtensions.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricValueBuilder.h>
#include <Framework/Mdib/Public/Model/Unit.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Thread/Public/Thread.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/ScopeExit.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Utf8Io.h>

#include <memory>
#include <mutex>
#include <sstream>
#include <string>

using DFL::Locale::Utf8;

S31_LOGGER("TestDevice");

using namespace S31::Samples;

const DFL::Mdib::MdsHandle mdsHandle("md0");

void SampleProvider::initMetadata()
{
    const DFL::Locale::Utf8    manufacturer("Dr\xC3\xA4ger");  // U+00E4 (c3 a4) LATIN SMALL LETTER A WITH DIAERESIS
    const DFL::Locale::Utf8    manufacturerUrl("www.draeger.com");
    const DFL::Mdib::Timestamp manufacturerDate(DFL::Chrono::SystemClock::now());

    const DFL::Locale::Utf8 modelName("SampleProvider");
    const DFL::Locale::Utf8 modelUrl("www.draeger.com/SampleProvider");
    const DFL::Locale::Utf8 modelNumber("0815");
    const DFL::Locale::Utf8 presentationUrl("www.draeger.com/SampleProvider/index.html");

    const DFL::Locale::Utf8 deviceName("MTP");
    const DFL::Locale::Utf8 deviceVersion("001");
    const DFL::Locale::Utf8 deviceSerialNumber("ARRB-0907");

    S31::Sdc::DpwsDeviceMetadata comNodeInfo;
    comNodeInfo.manufacturerName(manufacturer);
    comNodeInfo.manufacturerUrl(manufacturerUrl);

    comNodeInfo.modelName(modelName);
    comNodeInfo.modelNumber(modelNumber);
    comNodeInfo.presentationUrl(presentationUrl);
    comNodeInfo.modelUrl(modelUrl);

    comNodeInfo.deviceName(deviceName);
    comNodeInfo.deviceVersion(deviceVersion);
    comNodeInfo.deviceSerialNumber(deviceSerialNumber);

    m_dpwsDevice->dpwsDeviceMetadata(comNodeInfo);

    DFL::Mdib::MetaDataBuilder systemMetaDataBuilder;
    systemMetaDataBuilder.manufacturer({DFL::Mdib::LocalizedText(manufacturer)});
    systemMetaDataBuilder.manufactureDate(manufacturerDate);
    systemMetaDataBuilder.serialNumbers({DFL::Mdib::SerialNumber(deviceSerialNumber)});

    systemMetaDataBuilder.udis(DFL::Mdib::Udis(
            1,
            DFL::Mdib::Udi(
                    DFL::Mdib::DeviceIdentifier(DFL::Locale::Utf8("device identifier")),
                    DFL::Mdib::HumanReadableForm(DFL::Locale::Utf8("human readable form")),
                    DFL::Mdib::InstanceIdentifier(
                            DFL::Mdib::Root(DFL::Mdib::Uri("https://issuerroot")),
                            DFL::Mdib::Extension(DFL::Locale::Utf8("issuerextension"))))));
    systemMetaDataBuilder.modelName({DFL::Mdib::LocalizedText(modelName)});
    // Add meta data to mds.
    auto mdib = m_localMdibAccess->latestMdib();
    if (auto mds = mdib->entity(mdsHandle))
    {
        DFL::Mdib::MdsDescriptorBuilder mdsDescriptor{mds->descriptor()};
        mdsDescriptor.metaData(systemMetaDataBuilder.build());
        auto                     updatedMds = DFL::Mdib::EntityFactory::create(DFL::asNotNull(mds), mdsDescriptor);
        DFL::Mdib::MdibChangeSet changeSet;
        changeSet.addOneToUpdate(updatedMds);
        auto result = m_localMdibAccess->writeDescription(changeSet);
        if (result.status() != DFL::Mdib::WriteStatus::Success)
        {
            S31_STREAM_ERROR(result);
        }
    }
    std::cout << "Setting metadata to : "
              << " model '" << modelName << "', device '" << deviceName << "'\n";
}

namespace
{
struct PatientHelper
{
    DFL::Mdib::MdibChangeSet insertPatientChangeSet(
            const DFL::Mdib::PatientContextStateBuilder& patientContextBuilder,
            const DFL::Mdib::Mdib&                       mdib,
            const DFL::Mdib::PatientContextHandle&       patientContextHandle =
                    DFL::Mdib::PatientContextHandle(DFL::Locale::Utf8("testPatCtx")))
    {
        auto contextIndicatorHandle = S31::Utils::getUniqueEntity<DFL::Mdib::PatientContextIndicator>(mdib);

        DFL::Mdib::MdibChangeSet mdibChangeSet;
        if (!contextIndicatorHandle)
        {
            S31_STREAM_ERROR(__func__, "(): Empty context indicator handle. Returning.");
            return mdibChangeSet;
        }

        const auto context = DFL::Mdib::EntityFactory::create(
                patientContextHandle, patientContextBuilder, (*contextIndicatorHandle).handle());

        // With all context data in place, insert it.
        mdibChangeSet.addOneToInsert(context);
        return mdibChangeSet;
    }

    DFL::Mdib::MdibChangeSet updatePatientChangeSet(
            const DFL::Mdib::PatientContextStateBuilder& patientContextBuilder,
            const DFL::Mdib::Mdib&                       mdib,
            const DFL::Mdib::PatientContextHandle&       patientContextHandle =
                    DFL::Mdib::PatientContextHandle(DFL::Locale::Utf8("testPatCtx")))
    {
        const auto contextEntity = mdib.entity(patientContextHandle);

        DFL::Mdib::MdibChangeSet mdibChangeSet;
        if (contextEntity)
        {
            // With all context data in place, update the data
            const auto context = DFL::Mdib::EntityFactory::create(DFL::asNotNull(contextEntity), patientContextBuilder);
            mdibChangeSet.addOneToUpdate(context);
        }
        return mdibChangeSet;
    }

    void setPatient(
            const DFL::Mdib::PatientContextState&                    patientContextState,
            const DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& mdibAccess)
    {
        DFL::Mdib::PatientContextStateBuilder patCtxBuilder(patientContextState);

        DFL::Mdib::MdibChangeSet mdibChangeSet;
        auto                     mdib = mdibAccess.get()->latestMdib();

        const auto contextRange = mdib->range<DFL::Mdib::PatientContext>();
        if (contextRange.empty())
        {
            mdibChangeSet = insertPatientChangeSet(patCtxBuilder, *mdib);
        }
        else
        {
            mdibChangeSet = updatePatientChangeSet(patCtxBuilder, *mdib);
        }

        THROW_ON_MDIB_WRITE_FAILED(mdibAccess->writeContextStates(mdibChangeSet));
    }

    std::string getPatientFullName(const DFL::Mdib::PatientDemographicsCoreData& data)
    {
        std::ostringstream ss;

        const std::string last(data.familyName());
        if (!last.empty())
        {
            ss << last;

            const std::string first(data.givenName());
            const std::string middle = data.middleName();
            if (!first.empty() || !middle.empty())
            {
                ss << ",";
            }
            if (!first.empty())
            {
                ss << first;
            }
            if (!middle.empty())
            {
                ss << " " << middle;
            }
        }
        return ss.str();
    }
};
}  // namespace

void SampleProvider::initPatient()
{
    DFL::Mdib::PatientContextStateBuilder         patientStateBuilder;
    DFL::Mdib::PatientDemographicsCoreDataBuilder coreDataPatient;
    coreDataPatient.dateOfBirth(DFL::Mdib::Convert::toDateOfBirth("1999-01-20T00:00:00"));
    coreDataPatient.patientType(DFL::Mdib::PatientType::Adult);
    coreDataPatient.givenName(DFL::Locale::Utf8("Holly"));
    coreDataPatient.middleName(DFL::Locale::Utf8("Ann"));
    coreDataPatient.familyName(DFL::Locale::Utf8("Smith"));
    coreDataPatient.sex(DFL::Mdib::Sex::Female);
    coreDataPatient.height(DFL::Mdib::Measurement(DFL::Mdib::Decimal(172), DFL::Mdib::Unit::CENTI_M));
    coreDataPatient.weight(DFL::Mdib::Measurement(DFL::Mdib::Decimal(60), DFL::Mdib::Unit::KILO_G));
    patientStateBuilder.patientDemographicsCoreData(coreDataPatient.build());

    patientStateBuilder.identifications({DFL::Mdib::InstanceIdentifier(
            DFL::Mdib::Root{DFL::Mdib::Uri{"Test:Root"}}, DFL::Mdib::Extension(DFL::Locale::Utf8("1234567")))});

    auto patientContextState = patientStateBuilder.build();

    auto        idList = patientContextState.identifications();
    std::string id;
    if (!idList.empty())
    {
        id = idList.front().extension().get();
    }
    std::string name = PatientHelper().getPatientFullName(*patientContextState.patientDemographicsCoreData());
    std::cout << "Setting patient to : "
              << "name '" << name << "', id '" << id << "'\n";

    PatientHelper().setPatient(patientContextState, m_localMdibAccess);
}

namespace
{
struct LocationHelper
{
    DFL::Mdib::LocationContextIndicatorHandle findLocationIndicatorHandle(const DFL::Mdib::Mdib& mdib)
    {
        const auto systemContextRange =
                mdib.range<DFL::Mdib::SystemContext>(mdib.filters().children<DFL::Mdib::SystemContext>(mdsHandle));
        if (systemContextRange.empty())
        {
            S31_STREAM_WARN_M("Empty system context range. Returning new handle.");
            return {};
        }
        const auto systemContextHandle = (*systemContextRange.begin())->handle();

        const auto contextIndicatorRange = mdib.range<DFL::Mdib::LocationContextIndicator>(
                mdib.filters().children<DFL::Mdib::LocationContextIndicator>(systemContextHandle));
        if (contextIndicatorRange.empty())
        {
            S31_STREAM_WARN_M("Empty context indicator range. Returning new handle.");
            return {};
        }
        return (*contextIndicatorRange.begin())->handle();
    }

    DFL::Mdib::MdibChangeSet insertLocationChangeSet(
            const DFL::Mdib::LocationContextStateBuilder& locationContextBuilder,
            const DFL::Mdib::Mdib&                        mdib,
            const DFL::Mdib::LocationContextHandle&       locationContextHandle =
                    DFL::Mdib::LocationContextHandle(DFL::Locale::Utf8("testLocCtx")))
    {
        const DFL::Mdib::LocationContextIndicatorHandle contextIndicatorHandle = findLocationIndicatorHandle(mdib);
        const auto                                      context =
                DFL::Mdib::EntityFactory::create(locationContextHandle, locationContextBuilder, contextIndicatorHandle);

        // With all context data in place, insert it.
        DFL::Mdib::MdibChangeSet mdibChangeSet;
        mdibChangeSet.addOneToInsert(context);
        return mdibChangeSet;
    }

    DFL::Mdib::MdibChangeSet updateLocationChangeSet(
            const DFL::Mdib::LocationContextStateBuilder& locationContextBuilder,
            const DFL::Mdib::Mdib&                        mdib,
            const DFL::Mdib::LocationContextHandle&       locationContextHandle =
                    DFL::Mdib::LocationContextHandle(DFL::Locale::Utf8("testLocCtx")))
    {
        const auto contextEntity = mdib.entity(locationContextHandle);

        DFL::Mdib::MdibChangeSet mdibChangeSet;
        if (contextEntity)
        {
            // With all context data in place, update the data
            const auto context =
                    DFL::Mdib::EntityFactory::create(DFL::asNotNull(contextEntity), locationContextBuilder);
            mdibChangeSet.addOneToUpdate(context);
        }
        return mdibChangeSet;
    }

    void setLocation(
            DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> mdibAccess,
            const DFL::Mdib::LocationContextState&            location)
    {
        if (!location.locationDetail())
        {
            std::stringstream msg;
            msg << "location.locationDetail() is not set." << __FILE__ << __LINE__ << "\n";
            throw std::runtime_error(msg.str());
        }

        if (auto instanceIdentifier = S31::Sdc::InstanceIdentifierFactory::fallbackInstanceIdentifier(
                    location.locationDetail().get_value_or(DFL::Mdib::LocationDetail())))
        {
            auto mdib = mdibAccess->latestMdib();
            // if the Context is associated then disassociate it first - otherwise identification cannot be changed
            {
                auto handle = DFL::Mdib::LocationContextHandle(DFL::Locale::Utf8("testLocCtx"));
                if (auto context = mdib->entity(handle))
                {
                    if (context->state()->contextAssociation() == DFL::Mdib::ContextAssociation::Associated)
                    {
                        DFL::Mdib::MdibChangeSet mdibChangeSet;
                        auto                     builder = DFL::Mdib::getBuilder(context->state());
                        builder.contextAssociation(DFL::Mdib::ContextAssociation::Disassociated);
                        auto newContext = DFL::Mdib::EntityFactory::create(DFL::asNotNull(context), builder);
                        mdibChangeSet.addOneToUpdate(newContext);
                        THROW_ON_MDIB_WRITE_FAILED(mdibAccess->writeContextStates(mdibChangeSet));
                    }
                }
            }
            mdib = mdibAccess->latestMdib();

            DFL::Mdib::LocationContextStateBuilder locCtxBuilder(location);
            locCtxBuilder.identifications({*instanceIdentifier});

            DFL::Mdib::MdibChangeSet mdibChangeSet;
            const auto               contextRange = mdib->range<DFL::Mdib::LocationContext>(
                    mdib->filters().children<DFL::Mdib::LocationContext>(findLocationIndicatorHandle(*mdib)));
            if (contextRange.empty())
            {
                mdibChangeSet = insertLocationChangeSet(locCtxBuilder, *mdib);
            }
            else
            {
                mdibChangeSet = updateLocationChangeSet(locCtxBuilder, *mdib);
            }

            THROW_ON_MDIB_WRITE_FAILED(mdibAccess->writeContextStates(mdibChangeSet));
        }
    }
};
}  // namespace

void SampleProvider::initLocation()
{
    using DFL::Locale::Utf8;

    DFL::Mdib::LocationDetail locationDetail(
            DFL::Mdib::Facility(Utf8("Britannia Hospital")),
            DFL::Mdib::Building(Utf8("New Wing")),
            DFL::Mdib::Floor(Utf8("Floor 42")),
            DFL::Mdib::PointOfCare(Utf8("Poc 42")),
            DFL::Mdib::Room(Utf8("Room 42")),
            DFL::Mdib::Bed(Utf8("Bed 42")));

    std::cout << "Setting location to : "
              << "hospital '" << locationDetail.facility() << "', care unit '" << locationDetail.pointOfCare()
              << "', bed '" << locationDetail.bed() << "'\n";

    DFL::Mdib::LocationContextStateBuilder locationContextStateBuilder;
    locationContextStateBuilder.locationDetail(locationDetail);
    locationContextStateBuilder.contextAssociation(DFL::Mdib::ContextAssociation::Associated);
    if (auto instanceIdentifier = S31::Sdc::InstanceIdentifierFactory::fallbackInstanceIdentifier(locationDetail))
    {
        locationContextStateBuilder.identifications({*instanceIdentifier});
        locationContextStateBuilder.validators({S31::Sdc::InstanceIdentifierFactory::userValidated()});
    }
    LocationHelper().setLocation(m_localMdibAccess, locationContextStateBuilder.build());
}

void addSslConfiguration(S31::CoreConfiguration& configuration)
{
    // It is fine to create test certificates in the sample code ...
    S31::Utils::Test::useTestCertificateWithAllRolesAndWildcardWhitelist(configuration, "SampleProvider");
    // ... and allow test root CAs.
    S31::Utils::Test::addTestRootCas(configuration);
}

struct InitialConfigurationStrings
{
    std::string networkInterface;
    std::string deviceUrn;
    std::string modelName;
    std::string mdib;
    std::string reportPath;
};

void printInitialConfiguration(const InitialConfigurationStrings& config)
{
    std::cout << "\n____________________ Initial Configuration ____________________\n";
    std::cout << "\nNetwork Interface: '" << config.networkInterface << "'";
    std::cout << "\nDeviceUrn: '" << config.deviceUrn << "'";
    std::cout << "\n_______________________________________________________________\n\n";
}

SampleProvider::SampleProvider(CommandLineOptions options)
    : m_paramValue(0)
    , m_options(std::move(options))
    , m_localMdibAccess(DFL::Mdib::MdibFactory::createLocalMdibAccess(DFL::Mdib::MdibConstraints::allConstraints()))
    , m_numericMetric(m_localMdibAccess)
    , m_waveform(m_localMdibAccess)
    , m_stringMetric(m_localMdibAccess)
    , m_alert(m_localMdibAccess)
{

    InitialConfigurationStrings initialDeviceConfigForPrintout;
    DFL::ScopeExit              printConfig([&] { printInitialConfiguration(initialDeviceConfigForPrintout); });

    CoreConfiguration configuration;
    configuration.customAppMaxDelay = DFL::Chrono::Milliseconds(100);
    addSslConfiguration(configuration);

    std::string urn = m_options.getSystemProperty("S31.UUID");
    if (urn.empty())
    {
        urn = "urn:uuid:" + DFL::Crypto::generateRandomUuidString();
    }
    initialDeviceConfigForPrintout.deviceUrn = urn;

    // Configuration of the network interface via Command Line Options
    const auto& networkInterface = m_options.getSystemProperty("S31.NetworkInterface");
    if (!networkInterface.empty())
    {
        configuration.allowedInterfaces.insert(networkInterface);
        initialDeviceConfigForPrintout.networkInterface = networkInterface;
    }

    m_dispatcher               = std::make_shared<S31::Sdc::ThreadPoolDispatcher>();
    configuration.httpIPv4Port = S31::CoreConfiguration::PORTNUMBER_ANY;
    configuration.udpIPv4Port  = S31::CoreConfiguration::PORTNUMBER_ANY;

    configuration.compressionLevel = 9;

    S31::S31CoreFactory s31Factory(DFL::asNotNull(m_dispatcher), configuration);

    // For device side only it has to be started explicitly,
    // while the client is starting the dispatcher on client start automatically.
    m_dispatcher->start();

    Sdc::MedicalDpwsData dpwsData{
            S31::Sdc::EndpointReference{DFL::Net::Uri{urn}},
            S31::Sdc::MetadataVersion{0U},
            Sdc::DpwsDeviceMetadata{},
            Sdc::CompressionConfiguration::Compression};
    Sdc::MedicalDeviceData medicalDevice{m_localMdibAccess};

    m_dpwsDevice = s31Factory.createBicepsDevice(dpwsData, medicalDevice);

    initMdib();

    //  Start the S31 device
    m_dpwsDevice->start();
}

SampleProvider::~SampleProvider()
{
    if (m_started)
    {
        stop();
    }
    m_dpwsDevice->stop();
    m_dispatcher->stop();
}

void SampleProvider::start()
{
    if (m_started)
    {
        return;
    }

    m_started = true;
    initMetadata();
    initPatient();
    initLocation();

    std::cout << std::endl;  // flush console output

   m_numericMetric.start();
   m_waveform.start();
    m_stringMetric.start();
   m_alert.start();
}

void SampleProvider::stop()
{
    if (!m_started)
    {
        return;
    }

    m_started = false;
    m_numericMetric.stop();
    m_waveform.stop();
    m_stringMetric.stop();
    m_alert.stop();
}

namespace
{

const DFL::Mdib::VmdHandle                      vmdHandle("vmd");
const DFL::Mdib::SystemContextHandle            sysCtxtHandle("sysContext");
const DFL::Mdib::PatientContextIndicatorHandle  patientCtxtHandle("patientContext");
const DFL::Mdib::LocationContextIndicatorHandle locationCtxtHandle("locationContext");
const DFL::Mdib::ChannelHandle                  channelHandle("2436");

}  // namespace

void SampleProvider::initMdib()
{
    DFL::Mdib::MdibChangeSet changeSet;

    {
        // Create Mds including the friendly name in a CodedStringAttribute extension
        std::ostringstream friendlyName;
        friendlyName << "Device " << std::this_thread::get_id();
        const auto friendlyNameAttr = DFL::Mdib::Ext::CodedStringAttribute(
                DFL::Mdib::CodedValueConstants::MDC_ATTR_ID_SOFT, DFL::Locale::Utf8{friendlyName.str()});
        DFL::Mdib::MdsDescriptorBuilder mdsDesc;
        mdsDesc.extensions(DFL::Mdib::ExtensionTypes{
                DFL::Mdib::Ext::SdpiExtensions::toExtension(DFL::Mdib::Ext::CodedAttributes{{friendlyNameAttr}})});
        mdsDesc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("100000"));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(mdsHandle, mdsDesc));
    }

    auto sysContext = DFL::Mdib::EntityFactory::create(sysCtxtHandle, mdsHandle);
    changeSet.addOneToInsert(sysContext);

    auto patientContext = DFL::Mdib::EntityFactory::create(patientCtxtHandle, sysContext->handle());
    changeSet.addOneToInsert(patientContext);

    auto locationContext = DFL::Mdib::EntityFactory::create(locationCtxtHandle, sysContext->handle());
    changeSet.addOneToInsert(locationContext);

    DFL::Mdib::VmdDescriptorBuilder vmdDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode("69798");
        vmdDescriptor.type(t);
    }
    auto vmd = DFL::Mdib::EntityFactory::create(vmdHandle, vmdDescriptor, mdsHandle);
    changeSet.addOneToInsert(vmd);

    DFL::Mdib::ChannelDescriptorBuilder channelDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode("69787");
        channelDescriptor.type(t);
    }

    auto channel = DFL::Mdib::EntityFactory::create(channelHandle, channelDescriptor, vmd->handle());

    changeSet.addOneToInsert(channel);

    m_waveform.initMdib(changeSet, vmd, channel);
    m_numericMetric.initMdib(changeSet, vmd, channel);
    m_stringMetric.initMdib(changeSet, vmd, channel);
    m_alert.initMdib(changeSet, vmd, channel);

    auto writeResult = m_localMdibAccess->writeDescription(changeSet);
    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
    {
        S31_STREAM_ERROR(writeResult);
    }
}

void SampleProvider::shutdownMdsAndWaitReportSent()
{
    auto mdib = m_localMdibAccess->latestMdib();
    auto mdss = mdib->range<DFL::Mdib::Mds>();

    DFL::Mdib::MdibChangeSet changes;
    for (const auto& mds : mdss)
    {
        auto mdsState = DFL::Mdib::getBuilder(mds->state());
        mdsState.activationState(DFL::Mdib::ComponentActivation::Shutdown);
        changes.addOneToUpdate(DFL::Mdib::EntityFactory::create(mds, mdsState));
    }
    auto result = m_localMdibAccess->writeComponentStates(changes);

    std::cout << "\n\n\n\n\rWaiting for shutdown report delivery...\n";
    std::mutex              waitForShutdownMutex;
    std::condition_variable waitForShutdown;
    bool                    shutdownCompleted = false;
    m_dpwsDevice->onComponentReportCompleted(
            result.mdib()->mdibVersion(),
            [&](const DFL::Mdib::MdibVersion&)
            {
                std::lock_guard lock(waitForShutdownMutex);
                shutdownCompleted = true;
                // Keep lock for notify, since waiting thread will destroy
                // the condition variable when wait completes.
                waitForShutdown.notify_one();
            });

    std::unique_lock lock(waitForShutdownMutex);
    waitForShutdown.wait(lock, [&] { return shutdownCompleted; });
    std::cout << "Shutdown report delivery completed\n";
}
