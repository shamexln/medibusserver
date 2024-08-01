// SdcProvider.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SdcProvider.h"

#include <charconv>
#include <S31/Log/Public/Logger.h>
#include <S31/Sdc/Public/Common/CoreConfiguration.h>
#include <S31/Sdc/Public/Common/InstanceIdentifierFactory.h>
#include <S31/Sdc/Public/Common/S31CoreFactory.h>
#include <S31/Sdc/Public/Common/ThreadPoolDispatcher.h>
#include <S31/Sdc/Public/Device/LocalDevice.h>
#include <S31/Sdc/S31Only/S31SystemProperties.h>
#include <S31/Sdc/Test/Public/Common/CoreConfigurationHelper.h> // for test certificates
#include <S31/Utils/Public/MdibAccessUtil.h>
#include <S31/TestLog/S31Only/LogFile.h>
#include <Framework/Crypto/Public/RandomUuidGenerator.h>
#include <Framework/Mdib/Public/MdibFactory.h>
#include <Framework/Mdib/Public/Model/CodedValueConstants.h>
#include <Framework/Mdib/Public/Model/Component/MetaDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PatientType.h>
#include <Framework/Mdib/Public/Model/Context/Sex.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/DecimalConvert.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/CodedAttributes.h>
#include <Framework/Mdib/Public/Model/ExtensionKnown/SdpiExtensions.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricValueBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricValueBuilder.h>
#include <Framework/Mdib/Public/Model/CodedValueBuilder.h>
#include <Framework/Mdib/Public/Model/Unit.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Thread/Public/Thread.h>
#include <Framework/Utils/Public/NotNull.h>
#include <Framework/Utils/Public/ScopeExit.h>
#include <Framework/Utils/Public/Utf8.h>
#include <Framework/Utils/Public/Utf8Io.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>
#include <Framework/Mdib/Public/Model/Alert/AlertSystem.h>
#include <Framework/Mdib/Public/AlertHelper.h>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <condition_variable>

#include "ContinuousBase.h"

using DFL::Locale::Utf8;

S31_LOGGER("TestDevice");


//const DFL::Mdib::MdsHandle mdsHandle("md0");

// This is an example of an exported variable
SDCPROVIDER_API int nSdcProvider=0;

// This is an example of an exported function.
SDCPROVIDER_API int fnSdcProvider(void)
{
    return 0;
}


void CSdcProvider::initMetadata(std::string strDeviceName, std::string strDeviceId)
{
    
}

namespace
{
    struct PatientHelper
    {
        DFL::Mdib::MdibChangeSet insertPatientChangeSet(
            const DFL::Mdib::PatientContextStateBuilder& patientContextBuilder,
            const DFL::Mdib::Mdib& mdib,
            const DFL::Mdib::PatientContextHandle& patientContextHandle =
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
            const DFL::Mdib::Mdib& mdib,
            const DFL::Mdib::PatientContextHandle& patientContextHandle =
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
            const DFL::Mdib::PatientContextState& patientContextState,
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

void CSdcProvider::initPatient()
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

    patientStateBuilder.identifications({ DFL::Mdib::InstanceIdentifier(
            DFL::Mdib::Root{DFL::Mdib::Uri{"Test:Root"}}, DFL::Mdib::Extension(DFL::Locale::Utf8("1234567"))) });

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
        DFL::Mdib::LocationContextIndicatorHandle findLocationIndicatorHandle(
	        const DFL::Mdib::MdsHandle& mdsHandle, const DFL::Mdib::Mdib& mdib)
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
            const DFL::Mdib::MdsHandle& mdsHandle,
            const DFL::Mdib::LocationContextStateBuilder& locationContextBuilder,
            const DFL::Mdib::Mdib& mdib,
            const DFL::Mdib::LocationContextHandle& locationContextHandle =
            DFL::Mdib::LocationContextHandle(DFL::Locale::Utf8("testLocCtx")))
        {
            const DFL::Mdib::LocationContextIndicatorHandle contextIndicatorHandle = findLocationIndicatorHandle(mdsHandle, mdib);
            const auto                                      context =
                DFL::Mdib::EntityFactory::create(locationContextHandle, locationContextBuilder, contextIndicatorHandle);

            // With all context data in place, insert it.
            DFL::Mdib::MdibChangeSet mdibChangeSet;
            mdibChangeSet.addOneToInsert(context);
            return mdibChangeSet;
        }

        DFL::Mdib::MdibChangeSet updateLocationChangeSet(
            const DFL::Mdib::LocationContextStateBuilder& locationContextBuilder,
            const DFL::Mdib::Mdib& mdib,
            const DFL::Mdib::LocationContextHandle& locationContextHandle =
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

        void setLocation(const DFL::Mdib::MdsHandle& mdsHandle,
            DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr> mdibAccess,
            const DFL::Mdib::LocationContextState& location)
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
                locCtxBuilder.identifications({ *instanceIdentifier });

                DFL::Mdib::MdibChangeSet mdibChangeSet;
                const auto               contextRange = mdib->range<DFL::Mdib::LocationContext>(
                    mdib->filters().children<DFL::Mdib::LocationContext>(findLocationIndicatorHandle(mdsHandle , *mdib)));
                if (contextRange.empty())
                {
                    mdibChangeSet = insertLocationChangeSet(mdsHandle, locCtxBuilder, *mdib);
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

void CSdcProvider::initLocation(const std::string& strFacility, const std::string& strPointOfCare,
    const std::string& strBed, const std::string& strRoom, const std::string& strBuilding, const std::string& strFloor)
{
    using DFL::Locale::Utf8;

    DFL::Mdib::LocationDetail locationDetail(
        DFL::Mdib::Facility(Utf8(strFacility.c_str())),
        DFL::Mdib::Building(Utf8(strBuilding.c_str())),
        DFL::Mdib::Floor(Utf8(strFloor.c_str())),
        DFL::Mdib::PointOfCare(Utf8(strPointOfCare.c_str())),
        DFL::Mdib::Room(Utf8(strRoom.c_str())),
        DFL::Mdib::Bed(Utf8(strBed.c_str())));

    std::cout << "Setting location to : "
        << "hospital '" << locationDetail.facility() << "', care unit '" << locationDetail.pointOfCare()
        << "', bed '" << locationDetail.bed() << "'\n";

    DFL::Mdib::LocationContextStateBuilder locationContextStateBuilder;
    locationContextStateBuilder.locationDetail(locationDetail);
    locationContextStateBuilder.contextAssociation(DFL::Mdib::ContextAssociation::Associated);
    if (auto instanceIdentifier = S31::Sdc::InstanceIdentifierFactory::fallbackInstanceIdentifier(locationDetail))
    {
        locationContextStateBuilder.identifications({ *instanceIdentifier });
        locationContextStateBuilder.validators({ S31::Sdc::InstanceIdentifierFactory::userValidated() });
    }
    LocationHelper().setLocation(m_mdsHandle, m_localMdibAccess, locationContextStateBuilder.build());
}

void addSslConfiguration(S31::CoreConfiguration& configuration)
{
    // It is fine to create test certificates in the sample code ...
    S31::Utils::Test::useTestCertificateWithAllRolesAndWildcardWhitelist(configuration, "SdcProvider");
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


void configureLogging()
{
    S31::setLogLevel(DFL::Log::Success);
    S31::setLogLevels("S31.Test=4,S31.Sdc.Client=4");
    S31::Log::useLogFile("D:\\project\\MedibusServer\\medibus\\build\\src\\RelWithDebInfo\\S31_InteractiveTestDevice");
}

CSdcProvider::CSdcProvider()
    : m_localMdibAccess(DFL::Mdib::MdibFactory::createLocalMdibAccess(DFL::Mdib::MdibConstraints::allConstraints()))

{
    configureLogging();
	S31::CoreConfiguration configuration;
    configuration.customAppMaxDelay = DFL::Chrono::Milliseconds(100);
    addSslConfiguration(configuration);

    std::string urn = "urn:uuid:" + DFL::Crypto::generateRandomUuidString();

    m_dispatcher = std::make_shared<S31::Sdc::ThreadPoolDispatcher>();
    configuration.httpIPv4Port = S31::CoreConfiguration::PORTNUMBER_ANY;
    configuration.udpIPv4Port = S31::CoreConfiguration::PORTNUMBER_ANY;

    configuration.compressionLevel = 9;

    S31::S31CoreFactory s31Factory(DFL::asNotNull(m_dispatcher), configuration);

    // For device side only it has to be started explicitly,
    // while the client is starting the dispatcher on client start automatically.
    m_dispatcher->start();

	S31::Sdc::MedicalDpwsData dpwsData{
            S31::Sdc::EndpointReference{DFL::Net::Uri{urn}},
            S31::Sdc::MetadataVersion{0U},
            S31::Sdc::DpwsDeviceMetadata{},
            S31::Sdc::CompressionConfiguration::Compression };
	S31::Sdc::MedicalDeviceData medicalDevice{ m_localMdibAccess };

    m_dpwsDevice = s31Factory.createBicepsDevice(dpwsData, medicalDevice);


}

CSdcProvider::~CSdcProvider()
{
    m_dpwsDevice->stop();
    m_dispatcher->stop();
}

void CSdcProvider::start(const std::string& strDeviceName, const std::string& strMdsCFCode, const std::string& strMdsHandle
    /*const std::string& strVmdCFCode, const std::string& strVmdHandle, const std::string& strChannelCFCode, const std::string& strChannelHandle*/)
{
    initMdib(strDeviceName, strMdsCFCode, strMdsHandle/*, strVmdCFCode, strVmdHandle, strChannelCFCode, strChannelHandle*/);

    //  Start the S31 device
    m_dpwsDevice->start();
    //initMetadata();
    //initPatient();
    //initLocation("strFacility", "strPointOfCare", "strBed", "strRoom", "strBuilding", "strFloor");
}

namespace
{

    const DFL::Mdib::VmdHandle                      vmdHandle("vmd");
    const DFL::Mdib::SystemContextHandle            sysCtxtHandle("sysContext");
    const DFL::Mdib::PatientContextIndicatorHandle  patientCtxtHandle("patientContext");
    const DFL::Mdib::LocationContextIndicatorHandle locationCtxtHandle("locationContext");
    const DFL::Mdib::ChannelHandle                  channelHandle("2436");

}  // namespace

void CSdcProvider::initMdib(const std::string& strDeviceName, const std::string& strMdsCFCode, const std::string& strMdsHandle
    /*const std::string& strVmdCFCode, const std::string& strVmdHandle, const std::string& strChannelCFCode, const std::string& strChannelHandle*/)
{
    m_mdsHandle = DFL::Mdib::MdsHandle(strMdsHandle);
    DFL::Mdib::MdibChangeSet changeSet;
    {
        // Create Mds including the friendly name in a CodedStringAttribute extension
        const auto friendlyNameAttr = DFL::Mdib::Ext::CodedStringAttribute(
            DFL::Mdib::CodedValueConstants::MDC_ATTR_ID_SOFT, DFL::Locale::Utf8{ strDeviceName.c_str() });
        DFL::Mdib::MdsDescriptorBuilder mdsDesc;
        mdsDesc.extensions(DFL::Mdib::ExtensionTypes{
                DFL::Mdib::Ext::SdpiExtensions::toExtension(DFL::Mdib::Ext::CodedAttributes{{friendlyNameAttr}}) });
        mdsDesc.type(DFL::Mdib::CodedValueFactory::create11073cfCode(strMdsCFCode));
        changeSet.addOneToInsert(DFL::Mdib::EntityFactory::create(m_mdsHandle, mdsDesc));
    }

    auto sysContext = DFL::Mdib::EntityFactory::create(sysCtxtHandle, m_mdsHandle);
    changeSet.addOneToInsert(sysContext);

    auto patientContext = DFL::Mdib::EntityFactory::create(patientCtxtHandle, sysContext->handle());
    changeSet.addOneToInsert(patientContext);

    auto locationContext = DFL::Mdib::EntityFactory::create(locationCtxtHandle, sysContext->handle());
    changeSet.addOneToInsert(locationContext);

    auto writeResult = m_localMdibAccess->writeDescription(changeSet);
    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
    {
        S31_STREAM_ERROR(writeResult);
    }
}

DFL::Mdib::MetricCategory CSdcProvider::getMetricCategory(const std::string& strMetricCategory)
{
	if (strMetricCategory == "Set")
	{
        return DFL::Mdib::MetricCategory::Setting;
	} else if (strMetricCategory == "Msrmt")
	{
		return DFL::Mdib::MetricCategory::Measurement;
	}
}

DFL::Mdib::Duration CSdcProvider::getDuration(const std::string& strPeriod)
{
    if (strPeriod.empty())
    {
        return DFL::Chrono::Seconds{ 0 };
    }
    const char last = strPeriod.back();
    if (last == 's' || last == 'S')
    {
        std::string str = strPeriod.substr(0, strPeriod.size() - 1);
        float dd = std::stof(str) * 1000;
	    return DFL::Chrono::Milliseconds{ static_cast<int>( std::stof(str) * 1000 )};
    }
    if (last == 'h' || last == 'H')
    {
        std::string str = strPeriod.substr(0, strPeriod.size() - 1);
        return DFL::Chrono::Hours{ std::stol(str) };
    }
}

bool isCharEquals(char a, char b)
{
    return std::tolower(static_cast<unsigned char>(a)) ==
        std::tolower(static_cast<unsigned char>(b));
}

bool isEquals(const std::string& a, const std::string& b)
{
    return a.size() == b.size() &&
        std::equal(a.begin(), a.end(), b.begin(), isCharEquals);
}

DFL::Mdib::DerivationMethod CSdcProvider::getDerivationMethod(const std::string& strDerivation)
{
    if (strDerivation.empty())
    {
        return DFL::Mdib::DerivationMethod::Automatic;
    }
    
    if (isEquals(strDerivation, "Auto"))
    {
        return DFL::Mdib::DerivationMethod::Automatic;
    }
    return DFL::Mdib::DerivationMethod::Manual;
}

DFL::Mdib::MetricAvailability CSdcProvider::getAvailability(const std::string& strAvailability)
{
    if (strAvailability.empty())
    {
        return DFL::Mdib::MetricAvailability::Intermittent;
    }

    if (isEquals(strAvailability, "Intr"))
    {
        return DFL::Mdib::MetricAvailability::Intermittent;
    }
    return DFL::Mdib::MetricAvailability::Continuous;
}

DFL::Mdib::SafetyClassification CSdcProvider::getMedicalClass(const std::string& strMedicalClass)
{
    if (strMedicalClass.empty())
    {
        return DFL::Mdib::SafetyClassification::MedicalClassA;
    }

    if (isEquals(strMedicalClass, "A"))
    {
        return DFL::Mdib::SafetyClassification::MedicalClassA;
    }

    if (isEquals(strMedicalClass, "B"))
    {
        return DFL::Mdib::SafetyClassification::MedicalClassB;
    }

    if (isEquals(strMedicalClass, "C"))
    {
        return DFL::Mdib::SafetyClassification::MedicalClassC;
    }
    return DFL::Mdib::SafetyClassification::MedicalClassA;
}

DFL::Mdib::Duration CSdcProvider::getMaxDelayTime(const std::string& strMaxDelayTime)
{
    if (strMaxDelayTime.empty())
    {
        return DFL::Chrono::Seconds{ 0 };
    }
    const char last = strMaxDelayTime.back();
    if (last == 's' || last == 'S')
    {
        std::string str = strMaxDelayTime.substr(0, strMaxDelayTime.size() - 1);
        return DFL::Chrono::Seconds{ std::stoi(str) };
    }
    if (last == 'h' || last == 'H')
    {
        std::string str = strMaxDelayTime.substr(0, strMaxDelayTime.size() - 1);
        return DFL::Chrono::Hours{ std::stoi(str) };
    }
}

DFL::Mdib::AlertConditionPriority CSdcProvider::getAlarmPriority(const std::string& strAlarmPriority)
{
    if (strAlarmPriority.empty())
    {
        return DFL::Mdib::AlertConditionPriority::None;
    }
    if (isEquals(strAlarmPriority, "Hi"))
    {
        return DFL::Mdib::AlertConditionPriority::High;
    }

    if (isEquals(strAlarmPriority, "Me"))
    {
        return DFL::Mdib::AlertConditionPriority::Medium;
    }

    if (isEquals(strAlarmPriority, "Lo"))
    {
        return DFL::Mdib::AlertConditionPriority::Low;
    }

    return DFL::Mdib::AlertConditionPriority::None;
}

DFL::Mdib::AlertConditionKind CSdcProvider::getAlarmKind(const std::string& strAlarmKind)
{
    if (strAlarmKind.empty())
    {
        return DFL::Mdib::AlertConditionKind::Other;
    }
    if (isEquals(strAlarmKind, "Tec"))
    {
        return DFL::Mdib::AlertConditionKind::Technical;
    }

    if (isEquals(strAlarmKind, "Phy"))
    {
        return DFL::Mdib::AlertConditionKind::Physiological;
    }

    return DFL::Mdib::AlertConditionKind::Other;
}

auto CSdcProvider::getTimePoint(const std::string& strDuration) -> boost::optional<DFL::Chrono::SystemClock::TimePoint>
{

	return DFL::Chrono::Convert::toTimePoint(strDuration);
	
}
void CSdcProvider::initNumericMetric(DFL::Mdib::MdibChangeSet& changeSets,
    const std::string& strMdsHandle,
    const std::string& strVmdHandle,
    const std::string& strVmdCode,
    const std::string& strChannelHandle,
    const std::string& strChannelCode,
    const std::string& strHandleNumericMetric,
    const std::string& strMedicalClass,
    const std::string& strTypeCode,
    const std::string& strUnitCode,
    const std::string& strMetricCategory,
    const std::string& strLowerRange,
    const std::string& strUpperRange,
    const std::string& strDeterminationPeriod,
    const std::string& strLifeTimePeriod,
    const std::string& strMaxDelayTime,
    const std::string& strResolution,
    const std::string& strDerivation,
    const std::string& strAvailability)
{
    DFL::Mdib::MdibChangeSet changeSet;
    DFL::Mdib::VmdDescriptorBuilder vmdDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strVmdCode);
        vmdDescriptor.type(t);
    }
    auto vmd = DFL::Mdib::EntityFactory::create(DFL::Mdib::VmdHandle(strVmdHandle), vmdDescriptor, m_mdsHandle);
    if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::VmdHandle(strVmdHandle)))
    {
        changeSets.addOneToInsert(vmd);
        changeSet.addOneToInsert(vmd);
    }


    DFL::Mdib::ChannelDescriptorBuilder channelDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strChannelCode);
        channelDescriptor.type(t);
    }
    auto channel = DFL::Mdib::EntityFactory::create(DFL::Mdib::ChannelHandle(strChannelHandle), channelDescriptor, vmd->handle());
    if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::ChannelHandle(strChannelHandle)))
    {
        changeSets.addOneToInsert(channel);
        changeSet.addOneToInsert(channel);
    }


    DFL::Mdib::NumericMetricDescriptorBuilder desc;
    {
        desc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(strTypeCode));
        desc.safetyClassification(getMedicalClass(strMedicalClass));
        desc.metricCategory(getMetricCategory(strMetricCategory));
        desc.metricAvailability(getAvailability(strAvailability));
        desc.unit(DFL::Mdib::Unit(strUnitCode));
        if (!strLowerRange.empty() && !strUpperRange.empty())
        {
            desc.technicalRanges(DFL::Mdib::Ranges{ DFL::Mdib::Range(DFL::Mdib::Decimal(std::stoi(strLowerRange)), DFL::Mdib::Decimal(std::stoi(strUpperRange))) });
        }
        desc.determinationPeriod(getDuration(strDeterminationPeriod));
        desc.lifeTimePeriod(getDuration(strLifeTimePeriod));
        desc.derivationMethod(getDerivationMethod(strDerivation));
        if (!strResolution.empty())
        {
            desc.resolution(DFL::Mdib::Decimal(DFL::Mdib::Convert::toDecimal(std::stof(strResolution))));
        }
        desc.maxDelayTime(getMaxDelayTime(strMaxDelayTime));
    }

    DFL::Mdib::NumericMetricValueBuilder metricValue;
    {
        metricValue.value(DFL::Mdib::Decimal());
        metricValue.metricQuality(DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::Valid));
        metricValue.determinationTime(DFL::Chrono::SystemClock::now());
    }

    DFL::Mdib::NumericMetricStateBuilder state;
    state.metricValue(metricValue.build());

    const auto numeric = DFL::Mdib::EntityFactory::create(
        DFL::Mdib::NumericMetricHandle(strHandleNumericMetric), desc, state, channel->handle());

    changeSet.addOneToInsert(numeric);

    if (!changeSet.empty())
    {
        auto writeResult = m_localMdibAccess->writeDescription(changeSet);
        if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
        {
            S31_STREAM_ERROR(writeResult);
        }
    }
}

void CSdcProvider::initEnumStringMetric(DFL::Mdib::MdibChangeSet& changeSets,
    const std::string& strMdsHandle,
    const std::string& strVmdHandle,
    const std::string& strVmdCode,
    const std::string& strChannelHandle,
    const std::string& strChannelCode,
    const std::string& strHandleEnumStringMetric,
    const std::string& strMedicalClass,
    const std::string& strTypeCode,
    const std::string& strUnitCode,
    const std::vector<std::string>& vecAllowedValueCodes,
    const std::vector<std::string>& vecAllowedValues,
    const std::string& strMetricCategory,
    const std::string& strDerivation,
    const std::string& strAvailability)
{
    DFL::Mdib::MdibChangeSet changeSet;
    DFL::Mdib::VmdDescriptorBuilder vmdDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strVmdCode);
        vmdDescriptor.type(t);
    }
    auto vmd = DFL::Mdib::EntityFactory::create(DFL::Mdib::VmdHandle(strVmdHandle), vmdDescriptor, m_mdsHandle);
    if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::VmdHandle(strVmdHandle)))
    {
        changeSets.addOneToInsert(vmd);
        changeSet.addOneToInsert(vmd);
    }


    DFL::Mdib::ChannelDescriptorBuilder channelDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strChannelCode);
        channelDescriptor.type(t);
    }
    auto channel = DFL::Mdib::EntityFactory::create(DFL::Mdib::ChannelHandle(strChannelHandle), channelDescriptor, vmd->handle());
    if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::ChannelHandle(strChannelHandle)))
    {
        changeSets.addOneToInsert(channel);
        changeSet.addOneToInsert(channel);
    }


    DFL::Mdib::EnumStringMetricDescriptorBuilder desc;
    {
        desc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(strTypeCode));
        desc.safetyClassification(getMedicalClass(strMedicalClass));
        desc.metricCategory(getMetricCategory(strMetricCategory));
        desc.metricAvailability(getAvailability(strAvailability));
        desc.derivationMethod(getDerivationMethod(strDerivation));
        desc.unit(DFL::Mdib::Unit(strUnitCode));
        DFL::Mdib::AllowedEnumValues values;
        for (int i = 0; i < vecAllowedValueCodes.size(); i++)
        {
            values.emplace_back(DFL::Locale::Utf8(vecAllowedValues[i]), DFL::Mdib::Test::TestFactory::hashCodedValue(vecAllowedValueCodes[i]), (boost::none), (boost::none));
        }
        desc.allowedValues(values);
    }

    DFL::Mdib::EnumStringMetricStateBuilder state;
    state.activationState(DFL::Mdib::ComponentActivation::On);


    const auto numeric = DFL::Mdib::EntityFactory::create(
        DFL::Mdib::EnumStringMetricHandle(strHandleEnumStringMetric), desc, state, channel->handle());

    changeSet.addOneToInsert(numeric);

    if (!changeSet.empty())
    {
        auto writeResult = m_localMdibAccess->writeDescription(changeSet);
        if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
        {
            S31_STREAM_ERROR(writeResult);
        }
    }
}

void CSdcProvider::initRealTimeMetric(DFL::Mdib::MdibChangeSet& changeSets,
    const std::string& strMdsHandle,
    const std::string& strVmdHandle,
    const std::string& strVmdCode,
    const std::string& strChannelHandle,
    const std::string& strChannelCode,
    const std::string& strHandleRealTimeMetric,
    const std::string& strMedicalClass,
    const std::string& strTypeCode,
    const std::string& strUnitCode,
    const std::string& strMetricCategory,
    const std::string& strLowerRange,
    const std::string& strUpperRange,
    const std::string& strDeterminationPeriod,
    const std::string& strLifeTimePeriod,
    const std::string& strMaxDelayTime,
    const std::string& strResolution,
    const std::string& strDerivation,
    const std::string& strAvailability,
    const std::string& strSamplePeriod)
{
    DFL::Mdib::MdibChangeSet changeSet;
    DFL::Mdib::VmdDescriptorBuilder vmdDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strVmdCode);
        vmdDescriptor.type(t);
    }
    auto vmd = DFL::Mdib::EntityFactory::create(DFL::Mdib::VmdHandle(strVmdHandle), vmdDescriptor, m_mdsHandle);
    if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::VmdHandle(strVmdHandle)))
    {
        changeSets.addOneToInsert(vmd);
        changeSet.addOneToInsert(vmd);
    }


    DFL::Mdib::ChannelDescriptorBuilder channelDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strChannelCode);
        channelDescriptor.type(t);
    }
    auto channel = DFL::Mdib::EntityFactory::create(DFL::Mdib::ChannelHandle(strChannelHandle), channelDescriptor, vmd->handle());
    if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::ChannelHandle(strChannelHandle)))
    {
        changeSets.addOneToInsert(channel);
        changeSet.addOneToInsert(channel);
    }


    DFL::Mdib::RealTimeSampleArrayMetricDescriptorBuilder desc;
    {
        desc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(strTypeCode));
        desc.safetyClassification(getMedicalClass(strMedicalClass));
        desc.metricCategory(getMetricCategory(strMetricCategory));
        desc.metricAvailability(getAvailability(strAvailability));
        desc.unit(DFL::Mdib::Unit(strUnitCode));
        if (!strLowerRange.empty() && !strUpperRange.empty())
        {
            desc.technicalRanges(DFL::Mdib::Ranges{ DFL::Mdib::Range(DFL::Mdib::Decimal(std::stoi(strLowerRange)), DFL::Mdib::Decimal(std::stoi(strUpperRange))) });
        }
        desc.determinationPeriod(getDuration(strDeterminationPeriod));
        desc.lifeTimePeriod(getDuration(strLifeTimePeriod));
        desc.derivationMethod(getDerivationMethod(strDerivation));
        if (!strResolution.empty())
        {
            desc.resolution(DFL::Mdib::Decimal(DFL::Mdib::Convert::toDecimal(std::stof(strResolution))));
        }
        desc.maxDelayTime(getMaxDelayTime(strMaxDelayTime));
        desc.samplePeriod(getDuration(strSamplePeriod));
    }

    const auto rtsa2 = DFL::Mdib::EntityFactory::create(
        DFL::Mdib::RealTimeSampleArrayMetricHandle(strHandleRealTimeMetric), desc, channel->handle());

    changeSet.addOneToInsert(rtsa2);

    if (!changeSet.empty())
    {
        auto writeResult = m_localMdibAccess->writeDescription(changeSet);
        if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
        {
            S31_STREAM_ERROR(writeResult);
        }
    }
}

void CSdcProvider::initAlarmStatus(DFL::Mdib::MdibChangeSet& changeSets,
    const std::string& strMdsHandle,
    const std::string& strVmdHandle,
    const std::string& strVmdCode,
    const std::string& strHandleAlarmStatus,
    const std::string& strMedicalClass,
    const std::string& strTypeCode,
    const std::string& strSysHandle,
    const std::string& strSysSelfCheckPeriod,
    const std::string& strSysMaxPhysiologicalParallelAlarms,
    const std::string& strSysMaxTechnicalParallelAlarms,
    const std::string& strHandle,
    const std::string& strSource,
    const std::string& strDefaultConditionGenerationDelay,
    const std::string& strKind,
    const std::string& strPriority,
    const std::string& strAlertType,
    const std::string& strInitialActivationState)
{
    DFL::Mdib::MdibChangeSet changeSet;

    DFL::Mdib::VmdDescriptorBuilder vmdDescriptor;
    {
        auto t = DFL::Mdib::CodedValueFactory::create11073cfCode(strVmdCode);
        vmdDescriptor.type(t);
    }
    if (!strVmdHandle.empty())
    {
        auto vmd = DFL::Mdib::EntityFactory::create(DFL::Mdib::VmdHandle(strVmdHandle), vmdDescriptor, m_mdsHandle);
        if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::VmdHandle(strVmdHandle)))
        {
            changeSets.addOneToInsert(vmd);
            changeSet.addOneToInsert(vmd);
        }
        auto vmdAlertSystem = DFL::Mdib::EntityFactory::create(DFL::Mdib::VmdAlertSystemHandle(strSysHandle), DFL::Mdib::VmdHandle(strVmdHandle));
        
        DFL::Mdib::AlertSystemStateBuilder alertSystemStateBuilder(vmdAlertSystem->state());
        alertSystemStateBuilder.lastSelfCheck(getTimePoint(strSysSelfCheckPeriod));
        if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::VmdAlertSystemHandle(strSysHandle)))
        {
            changeSets.addOneToInsert(vmdAlertSystem);
            changeSet.addOneToInsert(vmdAlertSystem);
        }
        DFL::Mdib::AlertConditionDescriptorBuilder builder;

        // a condition with non latching signals
        DFL::Mdib::CodedValueBuilder type(DFL::Mdib::CodedValueFactory::create11073cfCode(strTypeCode));
        builder.type(type.build());
        builder.priority(getAlarmPriority(strPriority));
        builder.kind(getAlarmKind(strKind));
        builder.safetyClassification(getMedicalClass(strMedicalClass));
        builder.defaultConditionGenerationDelay(getDuration(strDefaultConditionGenerationDelay));
        std::vector<DFL::Mdib::Handle> handles;
        handles.emplace_back(toHandle(DFL::Mdib::NumericMetricHandle(strSource)));
        builder.sources(handles);
        auto alarm = DFL::Mdib::EntityFactory::create(DFL::Mdib::BasicHandle<DFL::Mdib::VmdAlertCondition>(strHandle),
            builder, DFL::Mdib::VmdAlertSystemHandle(strSysHandle));
        if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::VmdAlertConditionHandle(strHandle)))
        {
            changeSets.addOneToInsert(alarm);
            changeSet.addOneToInsert(alarm);
        }

        if (!changeSet.empty())
        {
            auto writeResult = m_localMdibAccess->writeDescription(changeSet);
            if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
            {
                S31_STREAM_ERROR(writeResult);
            }
        }
    }
    else
    {
        auto mdsAlertSystem = DFL::Mdib::EntityFactory::create(DFL::Mdib::MdsAlertSystemHandle(strSysHandle), m_mdsHandle);
        DFL::Mdib::AlertSystemStateBuilder alertSystemStateBuilder(mdsAlertSystem->state());
        alertSystemStateBuilder.lastSelfCheck(getTimePoint(strSysSelfCheckPeriod));
        if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::MdsAlertSystemHandle(strSysHandle)))
        {
            changeSets.addOneToInsert(mdsAlertSystem);
            changeSet.addOneToInsert(mdsAlertSystem);
        }

        DFL::Mdib::AlertConditionDescriptorBuilder builder;

        // a condition with non latching signals
        DFL::Mdib::CodedValueBuilder type(DFL::Mdib::CodedValueFactory::create11073cfCode(strTypeCode));
        builder.type(type.build());
        builder.priority(getAlarmPriority(strPriority));
        builder.kind(getAlarmKind(strKind));
        builder.safetyClassification(getMedicalClass(strMedicalClass));
        builder.defaultConditionGenerationDelay(getDuration(strDefaultConditionGenerationDelay));
        std::vector<DFL::Mdib::Handle> handles;
        handles.emplace_back(toHandle(DFL::Mdib::NumericMetricHandle(strSource)));
        builder.sources(handles);
        auto alarm = DFL::Mdib::EntityFactory::create(DFL::Mdib::BasicHandle<DFL::Mdib::MdsAlertCondition>(strHandle),
            builder, DFL::Mdib::MdsAlertSystemHandle(strSysHandle));
        if (!changeSets.isAlreadyInsertedOrUpdated(DFL::Mdib::MdsAlertConditionHandle(strHandle)))
        {
            changeSets.addOneToInsert(alarm);
            changeSet.addOneToInsert(alarm);
        }

        if (!changeSet.empty())
        {
            auto writeResult = m_localMdibAccess->writeDescription(changeSet);
            if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
            {
                S31_STREAM_ERROR(writeResult);
            }
        }
    }
   
}

void CSdcProvider::updateNumericMetricValue(const std::string& handle, int value)
{
    auto initNumericMetricValue = [](const boost::optional<DFL::Mdib::NumericMetricValue>& metricValue)
    {
        if (metricValue)
        {
            return DFL::asNotNull(std::make_unique<DFL::Mdib::NumericMetricValueBuilder>(metricValue.get()));
        }
        return DFL::asNotNull(std::make_unique<DFL::Mdib::NumericMetricValueBuilder>());
    };

    auto numericMetric = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::NumericMetricHandle(handle));
    if (numericMetric)
    {
        auto numericMetricValueBuilder = initNumericMetricValue(numericMetric->state()->metricValue());
        numericMetricValueBuilder->value(DFL::Mdib::Decimal(value));
        auto now = DFL::Chrono::SystemClock::now();
        numericMetricValueBuilder->determinationTime(now);

        DFL::Mdib::NumericMetricStateBuilder state(numericMetric->state());
        state.metricValue(numericMetricValueBuilder->build());
        state.activationState(DFL::Mdib::ComponentActivation::On);
        DFL::Mdib::MdibChangeSet changeSet;
        changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(numericMetric), state));

        if (!changeSet.empty())
        {
            auto writeResult = m_localMdibAccess->writeMetricStates(changeSet);
            if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
            {
                S31_STREAM_ERROR(writeResult);
                // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeMetricStates(changeSet));
            }
        }
    }
}

void CSdcProvider::updateEnumStringMetricValue(const std::string& handle, const std::string& value)
{
    auto now = DFL::Chrono::SystemClock::now();
    auto enumStringMetric = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::EnumStringMetricHandle(handle));
    if (enumStringMetric)
    {
        DFL::Mdib::StringMetricValueBuilder stringMetricValueBuilder;
        if (!value.empty())
        {
            stringMetricValueBuilder.value(DFL::Locale::Utf8(value));
            stringMetricValueBuilder.metricQuality(DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::Valid));
            stringMetricValueBuilder.determinationTime(now);
            stringMetricValueBuilder.startTime(now);
            stringMetricValueBuilder.stopTime(now + DFL::Mdib::Duration(DFL::Chrono::Milliseconds(1000)));

            DFL::Mdib::EnumStringMetricStateBuilder builder(enumStringMetric->state());
            builder.activationState(DFL::Mdib::ComponentActivation::On);
            builder.metricValue(stringMetricValueBuilder.build());

            DFL::Mdib::MdibChangeSet changeSet;
            changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(enumStringMetric), builder));

            if (!changeSet.empty())
            {
                auto writeResult = m_localMdibAccess->writeMetricStates(changeSet);
                if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                {
                    S31_STREAM_ERROR(writeResult);
                    // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeMetricStates(changeSet));
                }
            }
        }
        else
        {
            // if quality is NA, the value must not be set.
            // or, SDC stack will fail.
            // stringMetricValueBuilder.value(DFL::Locale::Utf8("value"));
            stringMetricValueBuilder.metricQuality(DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::NotAvailable));
            
            DFL::Mdib::EnumStringMetricStateBuilder builder(enumStringMetric->state());
            builder.activationState(DFL::Mdib::ComponentActivation::StandBy);
            builder.metricValue(stringMetricValueBuilder.build());

            DFL::Mdib::MdibChangeSet changeSet;
            changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(enumStringMetric), builder));

            if (!changeSet.empty())
            {
                auto writeResult = m_localMdibAccess->writeMetricStates(changeSet);
                if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                {
                    S31_STREAM_ERROR(writeResult);
                    // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeMetricStates(changeSet));
                }
            }
        }
        
    }
}

void CSdcProvider::updateRealTimeMetricValue(const std::string& handle, const std::vector<double>& values)
{
    auto realtimeMetric = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::RealTimeSampleArrayMetricHandle(handle));
    if (realtimeMetric)
    {
        DFL::Mdib::RealTimeSampleArrayMetricStateBuilder state = DFL::Mdib::RealTimeSampleArrayMetricStateBuilder(realtimeMetric->state());
        auto determinationTime = DFL::Chrono::SystemClock::now();
        DFL::Mdib::Samples samples;
        samples.reserve(values.size());
        for (const auto& s : values)
        {
            samples.push_back(DFL::Mdib::Sample(DFL::Mdib::Decimal(static_cast<int>(s * 1000), -3)));
        }
        DFL::Mdib::SampleArrayValue sav(
            DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::Valid),
            DFL::Mdib::Annotations(),
            boost::none,
            boost::none,
            determinationTime,
            std::move(samples));

        state.metricValue(sav);

        DFL::Mdib::MdibChangeSet changeSet;
        changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*realtimeMetric, state));

        if (!changeSet.empty())
        {
            auto writeResult = m_localMdibAccess->writeSampleArrayMetricStates(changeSet);
            if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
            {
                S31_STREAM_ERROR(writeResult);
                // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeSampleArrayMetricStates(changeSet));
            }
        }
    }
}

void CSdcProvider::updateAlarmStatus(const std::string& mdshandle, const std::string& vmdhandle, const std::string& syshandle, const std::string& handle, const std::string& strKind, const std::string& value)
{
    DFL::Mdib::MdibChangeSet changeSet;
    DFL::Mdib::MdibChangeSet changeSet2;

    if (vmdhandle.empty())
    {
        auto mdsAlertSystem = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::MdsAlertSystemHandle(syshandle));

        auto setMdsAlertSystemState = [&](DFL::Mdib::AlertActivation activationState, const std::string& strKind)
        {
            if (mdsAlertSystem)
            {
                DFL::Mdib::AlertSystemStateBuilder alertSystemStateBuilder(mdsAlertSystem->state());
                alertSystemStateBuilder.activationState(activationState);
                if (activationState == DFL::Mdib::AlertActivation::On)
                {
                    if (strKind == "Phy")
                    {
                        alertSystemStateBuilder.presentPhysiologicalAlarmConditions(
                            DFL::Mdib::HandleSet{ DFL::Mdib::Handle(toHandle(DFL::Mdib::MdsAlertConditionHandle(handle))) });
                    }
                    else if (strKind == "Tec")
                    {
                        alertSystemStateBuilder.presentTechnicalAlarmConditions(
                            DFL::Mdib::HandleSet{ DFL::Mdib::Handle(toHandle(DFL::Mdib::MdsAlertConditionHandle(handle))) });
                    }
                }
                changeSet.addOneToUpdate(
                    DFL::Mdib::EntityFactory::create(DFL::asNotNull(mdsAlertSystem), alertSystemStateBuilder));
            }
        };

        auto alertCondition = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::MdsAlertConditionHandle(handle));
        if (alertCondition)
        {
            if (!value.empty())
            {
                DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder(alertCondition->state());
                alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::Present);
            	alertConditionStateBuilder.activationState(DFL::Mdib::AlertActivation::On);
                alertConditionStateBuilder.actualPriority(getAlarmPriority(value));
                alertConditionStateBuilder.determinationTime(DFL::Chrono::SystemClock::now());

                if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
                {
                    changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*alertCondition, alertConditionStateBuilder));
                }

                setMdsAlertSystemState(DFL::Mdib::AlertActivation::On, strKind);

                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeDescription(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                        // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeSampleArrayMetricStates(changeSet));
                    }
                }
            }
            else
            {
                DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder(alertCondition->state());
                alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::NotPresent);
                if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
                {
                    changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*alertCondition, alertConditionStateBuilder));
                }

                auto mdsAlertSystem = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::MdsAlertSystemHandle(syshandle));
                DFL::Mdib::AlertHelper::setAlertSystemConditionPresenceLists(m_localMdibAccess->latestMdib(), changeSet, DFL::Mdib::AlertHelper::PresenceListsUpdateModus::ResetAllLists);
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeAlertStates(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                        // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeSampleArrayMetricStates(changeSet));
                    }
                }

            	alertConditionStateBuilder.activationState(DFL::Mdib::AlertActivation::Off);
                if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
                {
                    changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*alertCondition, alertConditionStateBuilder));
                }
                DFL::Mdib::AlertHelper::setAlertSystemConditionPresenceLists(m_localMdibAccess->latestMdib(), changeSet, DFL::Mdib::AlertHelper::PresenceListsUpdateModus::ResetAllLists);
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeAlertStates(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                        // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeSampleArrayMetricStates(changeSet));
                    }
                }

                //setMdsAlertSystemState(DFL::Mdib::AlertActivation::Off, strKind);
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeDescription(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                        // THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeSampleArrayMetricStates(changeSet));
                    }
                }
            }

        }
    }
    else
    {
        auto vmdAlertSystem = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::VmdAlertSystemHandle(syshandle));

        auto setVmdAlertSystemState = [&](DFL::Mdib::AlertActivation activationState, const std::string& strKind)
        {
            if (vmdAlertSystem)
            {
                DFL::Mdib::AlertSystemStateBuilder alertSystemStateBuilder(vmdAlertSystem->state());
                alertSystemStateBuilder.activationState(activationState);
                if (strKind == "Phy")
                {
                    alertSystemStateBuilder.presentPhysiologicalAlarmConditions(
                        DFL::Mdib::HandleSet{ DFL::Mdib::Handle(toHandle(DFL::Mdib::VmdAlertConditionHandle(handle))) });
                }
                else if (strKind == "Tec")
                {
                    alertSystemStateBuilder.presentTechnicalAlarmConditions(
                        DFL::Mdib::HandleSet{ DFL::Mdib::Handle(toHandle(DFL::Mdib::VmdAlertConditionHandle(handle))) });
                }

                changeSet.addOneToUpdate(
                    DFL::Mdib::EntityFactory::create(DFL::asNotNull(vmdAlertSystem), alertSystemStateBuilder));
            }
        };

        auto alertCondition = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::VmdAlertConditionHandle(handle));
        if (alertCondition)
        {
            if (!value.empty())
            {
                DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder(alertCondition->state());
                alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::Present);
                alertConditionStateBuilder.activationState(DFL::Mdib::AlertActivation::On);
                alertConditionStateBuilder.actualPriority(getAlarmPriority(value));
                alertConditionStateBuilder.determinationTime(DFL::Chrono::SystemClock::now());

                setVmdAlertSystemState(DFL::Mdib::AlertActivation::On, strKind);
                if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
                {
                    changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*alertCondition, alertConditionStateBuilder));
                }
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeDescription(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                    }
                }
            }
            else
            {
                DFL::Mdib::AlertConditionStateBuilder alertConditionStateBuilder(alertCondition->state());
                alertConditionStateBuilder.presence(DFL::Mdib::AlertConditionPresence::NotPresent);

                if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
                {
                    changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*alertCondition, alertConditionStateBuilder));
                }

                auto mdsAlertSystem = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::MdsAlertSystemHandle(syshandle));
                DFL::Mdib::AlertHelper::setAlertSystemConditionPresenceLists(m_localMdibAccess->latestMdib(), changeSet, DFL::Mdib::AlertHelper::PresenceListsUpdateModus::ResetAllLists);
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeAlertStates(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                    }
                }

                alertConditionStateBuilder.activationState(DFL::Mdib::AlertActivation::Off);
                if (alertConditionStateBuilder.isChanged(*alertCondition->state()))
                {
                    changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(*alertCondition, alertConditionStateBuilder));
                }
                DFL::Mdib::AlertHelper::setAlertSystemConditionPresenceLists(m_localMdibAccess->latestMdib(), changeSet, DFL::Mdib::AlertHelper::PresenceListsUpdateModus::ResetAllLists);
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeAlertStates(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                    }
                }

                //setVmdAlertSystemState(DFL::Mdib::AlertActivation::Off, strKind);
                if (!changeSet.empty())
                {
                    auto writeResult = m_localMdibAccess->writeDescription(changeSet);
                    if (writeResult.status() != DFL::Mdib::WriteStatus::Success)
                    {
                        S31_STREAM_ERROR(writeResult);
                    }
                }
            }

        }
    }
    
}

void CSdcProvider::shutdownMdsAndWaitReportSent()
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

