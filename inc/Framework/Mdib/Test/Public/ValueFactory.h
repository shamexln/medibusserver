#pragma once

#include <Framework/Mdib/Private/PrivateCodingSemantics.h>
#include <Framework/Mdib/Public/Model/BodySite.h>
#include <Framework/Mdib/Public/Model/CodedValueBuilder.h>
#include <Framework/Mdib/Public/Model/CodedValueConstants.h>
#include <Framework/Mdib/Public/Model/CodedValueFactory.h>
#include <Framework/Mdib/Public/Model/CodedValueTranslation.h>
#include <Framework/Mdib/Public/Model/CodingSystemFactory.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationDocumentation.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationInfo.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationResult.h>
#include <Framework/Mdib/Public/Model/Component/MetaData.h>
#include <Framework/Mdib/Public/Model/Component/PhysicalConnectorInfo.h>
#include <Framework/Mdib/Public/Model/Component/ProductionSpecification.h>
#include <Framework/Mdib/Public/Model/Component/Udi.h>
#include <Framework/Mdib/Public/Model/Context/LocationDetail.h>
#include <Framework/Mdib/Public/Model/Context/PatientDemographicsCoreDataBuilder.h>
#include <Framework/Mdib/Public/Model/Context/PersonReference.h>
#include <Framework/Mdib/Public/Model/Duration.h>
#include <Framework/Mdib/Public/Model/ExtensionType.h>
#include <Framework/Mdib/Public/Model/InstanceIdentifier.h>
#include <Framework/Mdib/Public/Model/Measurement.h>
#include <Framework/Mdib/Public/Model/Metric/Relation.h>
#include <Framework/Mdib/Public/Model/Metric/SampleArrayValue.h>
#include <Framework/Mdib/Public/Model/Operation/ActivateArgument.h>
#include <Framework/Mdib/Public/Model/Operation/AllowedStringValue.h>
#include <Framework/Mdib/Public/Model/Operation/OperationGroup.h>
#include <Framework/Mdib/Public/Model/Operation/XPathExpressions.h>
#include <Framework/Mdib/Public/Model/Range.h>

#include <Framework/Utils/Public/QName.h>

namespace DFL
{
namespace Mdib
{
namespace Test
{

/**
 * @brief Helper class to create random dummy MDIB data to be used in tests.
 * @ingroup Mdib
 */
class ValueFactory
{
    public:
        /**
         * @brief Provides test data.
         */
        static Locale::Utf8 aUtf8()
        {
            return Locale::Utf8("any UTF-8 string");
        }
        /**
         * @brief Provides test data.
         */
        static InstanceIdentifier aInstanceIdentifier(const std::string& extension = "single extension")
        {
            return {Root(Uri("https://any-root/")), Extension(Locale::Utf8(extension)), CodedValueFactory::create11073cfCode("532645")};
        }
        /**
         * @brief Provides test data.
         */
        static InstanceIdentifier anotherInstanceIdentifier()
        {
            return {Root(Uri("https://other-root/")), Extension(Locale::Utf8("extension")), CodedValueFactory::create11073cfCode("532645")};
        }

        /**
        * @brief Provides test data.
        */
        static LocationDetail aLocationDetail(const std::string& bed = "Bed1")
        {
            LocationDetail LocationDetail(Facility(Locale::Utf8("Fac1")),
                                          PointOfCare(Locale::Utf8("PoC")),
                                          Bed(Locale::Utf8(bed)));
            return LocationDetail;
        }

        /**
         * @brief Provides test data.
         */
        static InstanceIdentifiers someInstanceIdentifiers(const std::string& extension = "some extension")
        {
            InstanceIdentifiers result;
            result.push_back(aInstanceIdentifier(extension));
            result.push_back(aInstanceIdentifier("instance1"));
            result.push_back(aInstanceIdentifier("instance2"));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static BodySites someBodySites()
        {
            BodySites result;
            result.push_back(aCodedValue("123"));
            result.push_back(aCodedValue("456"));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static CodedValue aCodedValue(const std::string& codeId = "12345")
        {
            return CodedValueFactory::create11073cfCode(codeId);
        }
        /**
         * @brief Provides test data.
         */
        static CodedValue anotherCodedValue()
        {
            return CodedValueFactory::create11073cfCode("123");
        }
        /**
         * @brief Provides test data.
         */
        static CodedValue aCodedValueFromCustomCodingSystem(const std::string& codeId = "12345")
        {
            return CodedValue{CodingSystem{CodingSystemId{Uri{"urn:my_name"}}},
                              CodeId{Locale::Utf8{codeId}}};
        }

        /**
         * @brief Provides test data.
         */
        static CodedValueTranslation aCodedValueTranslation(const std::string& codeId = "12345")
        {
            return {CodingSystemFactory::ieee11073CodingSystem(), DFL::Locale::Utf8{codeId}};
        }
        /**
         * @brief Provides test data.
         */
        static Unit aUnit()
        {
            return Unit("262688");
        }
        /**
         * @brief Provides test data.
         */
        static Unit anotherUnit()
        {
            return Unit("262656");
        }
        /**
         * @brief Provides test data.
         */
        static Measurement aMeasurement(int value = 98)
        {
            return {Decimal(value), aUnit()};
        }
        /**
         * @brief Provides test data.
         */
        static Measurement anotherMeasurement()
        {
            return {Decimal(97), anotherUnit()};
        }
        /**
         * @brief Provides test data.
         */
        static Udi aUdi()
        {
          return {DeviceIdentifier(Locale::Utf8("51022222233")),
                                  HumanReadableForm(Locale::Utf8("(01)51022222233(11)141231(17)150707(10)A213B1(21)1234")),
                                  InstanceIdentifier(Root(Uri("Root2")), Extension(Locale::Utf8("extension2"))),
                                  InstanceIdentifier(Root(Uri("Root3")), Extension(Locale::Utf8("jurisdiction")))};

        }
        /**
         * @brief Provides test data.
         */
        static Udi anotherUdi()
        {
          return {DeviceIdentifier(Locale::Utf8("51022222233336")),
                                  HumanReadableForm(Locale::Utf8("(01)51022222233336(11)141231(17)150707(10)A213B1(21)1234")),
                                  InstanceIdentifier(Root(Uri("Root")), Extension(Locale::Utf8("extension")))};
        }

        /**
         * @brief Provides test data.
         */
        static Udi extendedUdi()
        {
          return {DeviceIdentifier(Locale::Utf8("51022222233336")),
                HumanReadableForm(Locale::Utf8("(01)51022222233336(11)141231(17)150707(10)A213B1(21)1234")),
                InstanceIdentifier(Root(Uri("Root")), Extension(Locale::Utf8("extension"))),
                boost::none,
                someExtensions()};
        }
        /**
         * @brief Provides test data.
         */
        static SerialNumber aSerialNumber()
        {
            return SerialNumber(Locale::Utf8("1234-5678"));
        }
        /**
         * @brief Provides test data.
         */
        static SerialNumbers someSerialNumbers()
        {
            SerialNumbers result;
            result.push_back(SerialNumber(Locale::Utf8("1234-5678")));
            result.push_back(SerialNumber(Locale::Utf8("XYZ34GH-2")));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static Udis someUdis()
        {
            Udis result;
            result.push_back(aUdi());
            result.push_back(anotherUdi());
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationResult aCalibrationResult()
        {
            return {aCodedValue(), aMeasurement()};
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationResults someCalibrationResults()
        {
            CalibrationResults result(1, aCalibrationResult());
            result.push_back(CalibrationResult(CodedValueFactory::create11073cfCode("12"), anotherMeasurement()));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static LocalizedTexts someLocalizedTexts(const std::string& defaultText = "default text")
        {
            LocalizedTexts result;
            result.push_back(LocalizedText(Locale::Utf8(defaultText)));
            result.push_back(LocalizedText(Locale::Utf8("Standard Text auf deutsch"), Locale::LanguageTag("de")));
            result.push_back(LocalizedText(Locale::Utf8("special US text version"), Locale::LanguageTag("en-US")));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static LocalizedTexts otherLocalizedTexts()
        {
            LocalizedTexts result;
            result.push_back(LocalizedText(Locale::Utf8("no language tag text")));
            result.push_back(LocalizedText(Locale::Utf8("the german version"), Locale::LanguageTag("de-DE")));
            result.push_back(LocalizedText(Locale::Utf8("special US text version"), Locale::LanguageTag("en-US")));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationDocumentation aCalibrationDocumentation()
        {
            return {someLocalizedTexts(), someCalibrationResults()};
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationDocumentations someCalibrationDocumentations()
        {
            CalibrationDocumentations result(1, aCalibrationDocumentation());
            result.push_back(CalibrationDocumentation(otherLocalizedTexts(), someCalibrationResults()));
            result.push_back(CalibrationDocumentation(someLocalizedTexts(), CalibrationResults()));
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationInfo aMinimalCalibrationInfo()
        {
            return {boost::none,
                    CalibrationType::TwoPoint,
                    boost::none,
                    CalibrationDocumentations()};
        }
        /**
         * @brief Provides test data.
         */
        static Duration aDuration(int value = 45)
        {
            return Duration(value);
        }
        /**
         * @brief Provides test data.
         */
        static Timestamp aTimestamp()
        {
            // We do not use now() since the resolution is too high for Biceps
            // timestamp round trips. Biceps typically uses an unsigned int with milliseconds
            // since 1970.
            // Rounding now() to milliseconds is also not enough, since the gSOAP
            // s2xsd_dateTime parser uses float for parsing fractional seconds and does
            // a rounding which sometimes failes the round trip.
            const Chrono::Seconds timestamp(1537863721); // 2018-09-25T08:22:01
            return Chrono::SystemClock::TimePoint(timestamp + Chrono::Milliseconds(333));
        }
        /**
         * @brief Provides test data.
         */
        static Timestamp anotherTimestamp()
        {
            const Chrono::Seconds timestamp(1537993721);
            return Chrono::SystemClock::TimePoint(timestamp + Chrono::Milliseconds(111));
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationInfo aCalibrationInfo()
        {
            return {boost::optional<CalibrationState>(CalibrationState::Running),
                    CalibrationType::TwoPoint,
                    aTimestamp(),
                    someCalibrationDocumentations()};
        }
        /**
         * @brief Provides test data.
         */
        static CalibrationInfo anotherCalibrationInfo()
        {
          return {boost::optional<CalibrationState>(CalibrationState::NotCalibrated),
                  CalibrationType::Offset,
                  aTimestamp() + Chrono::Hours(1),
                  someCalibrationDocumentations()};
        }

        /**
         * @brief Provides test data.
         */
        static ProductionSpecification aProductSpecification()
        {
            return {aCodedValue(), aUtf8(), aInstanceIdentifier()};
        }
        /**
         * @brief Provides test data.
         */
        static ProductionSpecifications someProductSpecifications()
        {
            ProductionSpecifications results;
            results.push_back(aProductSpecification());
            results.push_back(ProductionSpecification(anotherCodedValue(), aUtf8(), aInstanceIdentifier()));
            return results;
        }
        /**
         * @brief Provides the Draeger private 11073 coding system identifier for test
         */
        static ProductionSpecification draeger11073PrivateCodingSystem()
        {
          return {CodedValueConstants::MDC_ATTR_PRIV_CODING_SEMANTICS,
                  Locale::Utf8(DFL::Mdib::Impl::Draeger11073PrivateCodingSystem),
                  boost::none};
        }
        /**
         * @brief Provides test data.
         */
        static PhysicalConnectorInfo aPhysicalConnectorInfo()
        {
            return {PhysicalConnectorNumber(3), someLocalizedTexts("connector")};
        }
        /**
         * @brief Provides test data.
         */
        static Handles someHandles()
        {
            Handles result;
            result.emplace_back("mds1");
            result.emplace_back("channel42");
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static Relation aRelation()
        {
            return {Kind::EffectOnContainmentTreeEntries,
                    someHandles(),
                    aCodedValue(),
                    aInstanceIdentifier("my relation")};
        }
        /**
         * @brief Provides test data.
         */
        static Relations someRelations()
        {
            Relations result;
            result.push_back(Relation(Kind::EffectOnContainmentTreeEntries, Handles(), boost::none, boost::none, someExtensions()));
            result.push_back(aRelation());
            return result;
        }
        /**
         * @brief Provides test data.
         */
        static SampleArrayValue aSimpleSampleArrayValue()
        {
            Annotations const annotations(1, Annotation::MDC_EVT_FLAG_INVALID);
            Samples samples;
            samples.push_back(Sample(Decimal(20)));
            samples.push_back(Sample(Decimal(30)));
            samples.push_back(Sample(Decimal(40)));
            return {MetricQuality(MeasurementValidity::Valid),
                    annotations,
                    boost::optional<Timestamp>(Chrono::Seconds(10000)),
                    boost::optional<Timestamp>(Chrono::Seconds(50000)),
                    boost::optional<Timestamp>(Chrono::Seconds(10001)),
                    samples};
        }

        /**
         * @brief Provides test data.
         */
       static Range aRange(int upper = 20)
       {
           return {Decimal(0), Decimal(upper)};
       }

       /**
        * @brief Provides test data.
        */
       static Ranges someRanges()
       {
           Ranges result;
           result.push_back(Range(Decimal(0), Decimal(10)));
           result.push_back(Range(Decimal(10), Decimal(20), Decimal(2), Decimal(5), Decimal(6)));
           return result;
       }
       /**
        * @brief Provides test data.
        */
       static AllowedStringValues someAllowedStringValues()
       {
           AllowedStringValues result;
           result.push_back(AllowedStringValue(Locale::Utf8("val1")));
           result.push_back(AllowedStringValue(Locale::Utf8("val2")));
           result.push_back(AllowedStringValue(Locale::Utf8("val4")));
           result.push_back(AllowedStringValue(Locale::Utf8("val8")));
           return result;
       }
       /**
        * @brief Provides test data.
        */
       static ActivateArguments someActivateArguments()
       {
           ActivateArguments result;
           result.push_back(ActivateArgument(aCodedValue("12234"), XsdSimpleType::String));
           result.push_back(ActivateArgument(aCodedValue("12235"), XsdSimpleType::Decimal));
           return result;
       }
       /**
        * @brief Provides test data.
        */
       static XPathExpressions someXPathExpressions()
       {
           XPathExpressions result;
           result.push_back(XPathExpression(Locale::Utf8("/pm:MdState/")));
           result.push_back(XPathExpression(Locale::Utf8("/pm:MdState/pm:State/")));
           return result;
       }

       /**
        * @brief Provides test data.
        */
       static OperationGroup anOperationGroup()
       {
           return {OperatingMode::Enabled, someHandles(), aCodedValue("1223")};
       }
       /**
        * @brief Provides test data.
        */
       static OperationGroups someOperationGroups()
       {
           OperationGroups result;
           result.push_back(OperationGroup(OperatingMode::Disabled, someHandles(), aCodedValue("12345")));
           result.push_back(anOperationGroup());
           return result;
       }
       /**
        * @brief Provides test data.
        */
       static OperationGroup anExtendedOperationGroup()
       {
           return {OperatingMode::Enabled, someHandles(), aCodedValue("1223"), someExtensions()};
       }

       /**
        * @brief Provides test data.
        */
       static PersonReference aPersonReference()
       {
           return PersonReference{someInstanceIdentifiers("mother"), aBaseDemographics("Maximilian")};
       }

       /**
        * @brief Provides test data.
        */
       static PersonReference aPersonReferenceWithoutDemographics()
       {
           return PersonReference{someInstanceIdentifiers("mother"), boost::none};
       }

       /**
        * @brief Provides test data.
        */
       static BaseDemographics aBaseDemographics(const std::string& givenName = "Max")
       {
           return BaseDemographics{Locale::Utf8(givenName),
                                   Locale::Utf8("Tom"),
                                   Locale::Utf8("Smith"),
                                   Locale::Utf8("Miller"),
                                   Locale::Utf8("Dr.")};
       }

       /**
        * @brief Provides test data.
        */
       static PatientDemographicsCoreData aPatient(const std::string& givenName = "Lara")
       {
           using namespace DFL::Chrono;
           PatientDemographicsCoreDataBuilder builder;
           
           builder.givenName(Locale::Utf8(givenName));
           builder.middleName(Locale::Utf8("Sue"));
           builder.familyName(Locale::Utf8("Tomson"));
           builder.birthName(Locale::Utf8("Craft"));
           builder.title(Locale::Utf8("Prof."));
           builder.sex(Sex::Female);
           builder.patientType(PatientType::Pediatric);
           builder.dateOfBirth(DateOfBirth(Year(2010) / aug / 21));
           builder.height(aMeasurement(120));
           builder.weight(anotherMeasurement());
           builder.race(aCodedValue("race"));
           builder.gestationalAge(aMeasurement(42));
           builder.birthLength(aMeasurement(4));
           builder.birthWeight(aMeasurement(54));
           builder.headCircumference(aMeasurement(53));
           builder.mother(aPersonReference());

           return builder.build();
       }

        /**
         * @brief Provides test data.
         */
        static ExtensionTypes someExtensions()
        {
            return DFL::Mdib::ExtensionTypes{
                { DFL::QName( DFL::NamespaceUri("http://test-namespace"), DFL::NamePrefix("tst"), "aName" ), MustUnderstand::True },
                { DFL::QName( DFL::NamespaceUri("http://different-namespace"), DFL::NamePrefix("tst"), "anotherName" ), MustUnderstand::False }
            };
        }

        /**
         * @brief Provides test data for descriptors.
         */
        static ExtensionTypes someExtensionWithRetrievabilities()
        {
            return DFL::Mdib::ExtensionTypes{
                { Dom::Nodes{ {Dom::NodeDepth(0), Dom::Element(QName(NamespaceUri("http://standards.ieee.org/downloads/11073/11073-10207-2017/message"), NamePrefix("msg"), "Retrievability"))},
                              {Dom::NodeDepth(1), Dom::Element(QName(NamespaceUri("http://standards.ieee.org/downloads/11073/11073-10207-2017/message"), NamePrefix("msg"), "By"),
                                                                     Dom::Attributes{ {QName("Method"), Locale::Utf8("Get")} } ) } }, MustUnderstand::False },
                { DFL::QName( DFL::NamespaceUri("http://test-namespace"), DFL::NamePrefix("tst"), "aName" ), MustUnderstand::True }};
        }
};

}
}
}
