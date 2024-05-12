#pragma once

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/MdibFactory.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricValueBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/SampleArrayValueBuilder.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricValueBuilder.h>
#include <Framework/Mdib/Public/Roles.h>
#include <Framework/Mdib/Test/Public/MdibWriter.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace DFL::Mdib::Test::Impl
{

enum class CheckerRequired
{
    /// A MDIB checker is required for a given entity.
    True,
    /// A MDIB checker is not required for a given entity.
    False
};

DFL::NotNull<DFL::Mdib::LocalMdibAccessUniquePtr> createMdib();

template<class EntityType>
void checkInsertError(DFL::Mdib::LocalMdibAccess& mdib,
                      const DFL::Mdib::BasicHandle<EntityType>& metricHandle,
                      const typename EntityType::DescriptorBuilderType& descBuilder,
                      const DFL::Mdib::BasicHandle<typename EntityType::ParentType>& parentHandle,
                      const char* errorMessage)
{
    DFL::Mdib::MdibChangeSet changes;
    changes.addOneToInsert(DFL::Mdib::EntityFactory::create(metricHandle, descBuilder, parentHandle));
    auto result = mdib.writeDescription(changes);

    using namespace testing;
    ASSERT_THAT(result.status(), Eq(DFL::Mdib::WriteStatus::CheckPluginError)) << "Failed for EntityType= " << typeid(EntityType).name();
    EXPECT_THAT(result.error().value(), AllOf(HasSubstr(metricHandle.string()), HasSubstr(errorMessage)));
}

template<class EntityType>
void insertSuccessfully(DFL::Mdib::LocalMdibAccess& mdib,
                        const DFL::Mdib::BasicHandle<EntityType>& metricHandle,
                        const typename EntityType::DescriptorBuilderType& descBuilder,
                        const DFL::Mdib::BasicHandle<typename EntityType::ParentType>& parentHandle)
{
    DFL::Mdib::MdibChangeSet changes;
    changes.addOneToInsert(DFL::Mdib::EntityFactory::create(metricHandle, descBuilder, parentHandle));
    ASSERT_MDIB_WRITE_SUCCESS(mdib.writeDescription(changes));
}

template<class EntityType>
void checkUpdateError(DFL::Mdib::LocalMdibAccess& mdib,
                      const DFL::Mdib::BasicHandle<EntityType>& metricHandle,
                      const typename EntityType::DescriptorBuilderType& descBuilder,
                      const char* errorMessage)
{
    auto metricEntity = mdib.latestMdib()->entity(metricHandle);
    ASSERT_TRUE(metricEntity);

    DFL::Mdib::MdibChangeSet changes;
    changes.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(metricEntity), descBuilder));
    auto result = mdib.writeDescription(changes);

    using namespace testing;
    ASSERT_THAT(result.status(), Eq(DFL::Mdib::WriteStatus::CheckPluginError)) << "Failed for EntityType= " << typeid(EntityType).name();
    EXPECT_THAT(result.error().value(), AllOf(HasSubstr(metricHandle.string()), HasSubstr(errorMessage)));
}

template<class EntityType>
void updateSuccessfully(DFL::Mdib::LocalMdibAccess& mdib,
                        const DFL::Mdib::BasicHandle<EntityType>& metricHandle,
                        const typename EntityType::DescriptorBuilderType& descBuilder)
{
    auto metricEntity = mdib.latestMdib()->entity(metricHandle);
    ASSERT_TRUE(metricEntity);

    DFL::Mdib::MdibChangeSet changes;
    changes.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(metricEntity), descBuilder));
    ASSERT_MDIB_WRITE_SUCCESS(mdib.writeDescription(changes));
}

template<class EntityType>
typename EntityType::DescriptorBuilderType makeDescriptorBuilder(typename std::enable_if<!std::is_same<EntityType, DFL::Mdib::EnumStringMetric>::value>::type* = nullptr)
{
    typename EntityType::DescriptorBuilderType builder;
    return builder;
}

template<class EntityType>
typename EntityType::DescriptorBuilderType makeDescriptorBuilder(typename std::enable_if<std::is_same<EntityType, DFL::Mdib::EnumStringMetric>::value>::type* = nullptr)
{
    typename EntityType::DescriptorBuilderType builder;
    builder.allowedValues(DFL::Mdib::AllowedEnumValues{DFL::Locale::Utf8("abc")});
    return builder;
}

template<class EntityType>
void testContinuousMetricMustHaveDeterminationPeriod()
{
    const auto metricHandle = DFL::Mdib::BasicHandle<EntityType>{"entityUnderTest"};
    const auto parentHandle = DFL::Mdib::Test::BaseTree::Channel;

    auto mdib = createMdib();
    auto desc = makeDescriptorBuilder<EntityType>();
    desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("1234"));

    desc.metricAvailability(DFL::Mdib::MetricAvailability::Continuous);
    checkInsertError(*mdib, metricHandle, desc, parentHandle, "DeterminationPeriod is required");

    desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Milliseconds{300}});
    insertSuccessfully(*mdib, metricHandle, desc, parentHandle);

    desc.determinationPeriod(boost::none);
    checkUpdateError(*mdib, metricHandle, desc, "DeterminationPeriod is required");
}

template<class EntityType>
void testLifeTimePeriodRequiredForMetrics(DFL::Mdib::MetricCategory category, DFL::Mdib::MetricAvailability availability, CheckerRequired required)
{
    const auto metricHandle = DFL::Mdib::BasicHandle<EntityType>{"entityUnderTest"};
    const auto parentHandle = DFL::Mdib::Test::BaseTree::Channel;

    auto mdib = createMdib();
    auto desc = makeDescriptorBuilder<EntityType>();
    desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("1234"));

    desc.metricCategory(category);
    desc.metricAvailability(availability);
    if (availability == DFL::Mdib::MetricAvailability::Continuous)
    {
        desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Seconds{1}});
    }

    (required == CheckerRequired::True) ? checkInsertError(*mdib, metricHandle, desc, parentHandle, "LifeTimePeriod is required")
                                        : insertSuccessfully(*mdib, metricHandle, desc, parentHandle);

    desc.lifeTimePeriod(DFL::Mdib::Duration{DFL::Chrono::Minutes{60}});
    (required == CheckerRequired::True) ? insertSuccessfully(*mdib, metricHandle, desc, parentHandle)
                                        : updateSuccessfully(*mdib, metricHandle, desc);

    desc.lifeTimePeriod(boost::none);
    (required == CheckerRequired::True) ? checkUpdateError(*mdib, metricHandle, desc, "LifeTimePeriod is required")
                                        : updateSuccessfully(*mdib, metricHandle, desc);
}

template <class EntityType>
DFL::NotNull<DFL::Mdib::SharedPtr<EntityType>> entityForValueTest(DFL::Mdib::LocalMdibAccess& mdib,
                                                                  DFL::Mdib::MetricAvailability availability,
                                                                  DFL::Mdib::MetricCategory category)
{
    const auto metricHandle = DFL::Mdib::BasicHandle<EntityType>{"entityUnderTest"};
    const auto parentHandle = DFL::Mdib::Test::BaseTree::Channel;

    auto desc = makeDescriptorBuilder<EntityType>();
    desc.type(DFL::Mdib::CodedValueFactory::create11073cfCode("1234"));
    desc.metricCategory(category);
    desc.metricAvailability(availability);

    if (availability == DFL::Mdib::MetricAvailability::Continuous)
    {
        desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Seconds{1}});
    }

    if (category == DFL::Mdib::MetricCategory::Measurement
        || category == DFL::Mdib::MetricCategory::Calculation)
    {
        desc.lifeTimePeriod(DFL::Mdib::Duration{DFL::Chrono::Hours{24}});
    }

    insertSuccessfully(mdib, metricHandle, desc, parentHandle);

    if (const auto newEntity = mdib.latestMdib()->entity(metricHandle))
    {
        return DFL::asNotNull(newEntity);
    }
    throw std::runtime_error("addEntityUnderTest failed");
}

DFL::Mdib::NumericMetricValueBuilder makeValueBuilder(const boost::optional<DFL::Mdib::NumericMetricValue>&,
                                                      boost::optional<DFL::Mdib::Decimal>&& value);

DFL::Mdib::StringMetricValueBuilder makeValueBuilder(const boost::optional<DFL::Mdib::StringMetricValue>&,
                                                     boost::optional<DFL::Locale::Utf8>&& value);

DFL::Mdib::SampleArrayValueBuilder makeValueBuilder(const boost::optional<DFL::Mdib::SampleArrayValue>&,
                                                    DFL::Mdib::Samples&& samples);

DFL::Mdib::SampleArrayValueBuilder makeValueBuilder(const boost::optional<DFL::Mdib::SampleArrayValue>&,
                                                    boost::none_t);

template<class EntityType>
DFL::Mdib::WriteResult updateState(DFL::Mdib::LocalMdibAccess& mdib,
                                   const DFL::NotNull<DFL::Mdib::SharedPtr<EntityType>>& entityUnderTest,
                                   const typename EntityType::StateBuilderType& stateBuilder)
{
    DFL::Mdib::MdibChangeSet changes;
    changes.addOneToUpdate(DFL::Mdib::EntityFactory::create(entityUnderTest, stateBuilder));
    return mdib.writeMetricStates(changes);
}

DFL::Mdib::WriteResult updateState(DFL::Mdib::LocalMdibAccess& mdib,
                                   const DFL::NotNull<DFL::Mdib::RealTimeSampleArrayMetricSharedPtr>& rtsaUnderTest,
                                   const DFL::Mdib::RealTimeSampleArrayMetricStateBuilder& stateBuilder);

enum class TestType
{
    Ok,
    Fail
};

template <class EntityType>
void testOngoingMetricMustHaveStartTime(boost::optional<DFL::Mdib::Timestamp> startTime,
                                        TestType testType)
{
    auto mdib = createMdib();
    auto entityUnderTest = entityForValueTest<EntityType>(*mdib,
                                                          DFL::Mdib::MetricAvailability::Intermittent,
                                                          DFL::Mdib::MetricCategory::Measurement);

    // Using empty value (note: SampleArray is adapted by makeValueBuilder to handle boost::none)
    auto valueBuilder = makeValueBuilder(entityUnderTest->state()->metricValue(), boost::none);
    valueBuilder.metricQuality(DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::MeasurementOngoing));
    valueBuilder.startTime(startTime);

    auto stateBuilder = DFL::Mdib::getBuilder(entityUnderTest->state());
    stateBuilder.metricValue(valueBuilder.build());

    auto result = updateState(*mdib, entityUnderTest, stateBuilder);

    using namespace testing;
    if (testType == TestType::Fail)
    {
        ASSERT_THAT(result.status(), Eq(DFL::Mdib::WriteStatus::CheckPluginError)) << "Failed for EntityType= " << typeid(EntityType).name();
        EXPECT_THAT(result.error().value(), AllOf(HasSubstr(entityUnderTest->handle().string()),
                                                  HasSubstr("if MetricQuality/@Validity=MeasurementOngoing, then StartTime is required")));
    }
    else
    {
        EXPECT_THAT(result.status(), Eq(DFL::Mdib::WriteStatus::Success)) << "Failed for EntityType= " << typeid(EntityType).name();
    }
}

template <class EntityType>
void testContinuesMetricValidity(MeasurementValidity validity,
                                 TestType testType)
{
    auto mdib = createMdib();
    auto entityUnderTest = entityForValueTest<EntityType>(
        *mdib,
        DFL::Mdib::MetricAvailability::Continuous,
        DFL::Mdib::MetricCategory::Measurement);

    // Using empty value (note: SampleArray is adapted by makeValueBuilder to handle boost::none)
    auto valueBuilder = makeValueBuilder(entityUnderTest->state()->metricValue(), boost::none);
    valueBuilder.metricQuality(DFL::Mdib::MetricQuality(validity));

    auto stateBuilder = DFL::Mdib::getBuilder(entityUnderTest->state());
    stateBuilder.metricValue(valueBuilder.build());

    auto result = updateState(*mdib, entityUnderTest, stateBuilder);

    using namespace testing;
    if (testType == TestType::Fail)
    {
        ASSERT_THAT(result.status(), Eq(DFL::Mdib::WriteStatus::CheckPluginError)) << "Failed for EntityType= " << typeid(EntityType).name();
        EXPECT_THAT(result.error().value(), AllOf(HasSubstr(entityUnderTest->handle().string()),
                                                  HasSubstr("if @MetricAvailability=Continuous, then the metric's @Validity != MeasurementOngoing")));
    }
    else
    {
        EXPECT_THAT(result.status(), Eq(DFL::Mdib::WriteStatus::Success)) << "Failed for EntityType= " << typeid(EntityType).name();
    }
}

}
