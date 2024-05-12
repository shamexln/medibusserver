#pragma once

#include <S31/Sdc/Test/Utils/TestClient.h>
#include <S31/Sdc/Test/Public/Common/TimeHelper.h>
#include <S31/Sdc/Test/Utils/Matcher.h>
#include <S31/Sdc/Test/Utils/MdibChangesTracking.h>
#include <S31/Sdc/Test/Utils/Modifier.h>
#include <S31/Sdc/Test/Utils/TestDevice.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace S31::Sdc::Test
{

inline DFL::Mdib::StringMetricValue modifyStringMetricValue(const boost::optional<DFL::Mdib::StringMetricValue>& in)
{
    auto nonOptionalIn = in.get_value_or(DFL::Mdib::StringMetricValue());
    auto value = nonOptionalIn.value().get_value_or(DFL::Locale::Utf8(""));
    value += DFL::Locale::Utf8("av1");
    return {DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::Valid),
            nonOptionalIn.annotations(),
            nonOptionalIn.startTime(),
            nonOptionalIn.stopTime(),
            S31::Sdc::Test::now(),
            value};
}

inline S31::Sdc::Test::Matcher modifyStringValueInFirstEnumStringMetric(DFL::Mdib::LocalMdibAccess& mdib)
{
    auto oldEntity = S31::Sdc::Test::firstEntity<DFL::Mdib::EnumStringMetric>(*mdib.latestMdib());
    DFL::Mdib::EnumStringMetricStateBuilder state(oldEntity->state());
    auto metricValue = modifyStringMetricValue(state.metricValue());
    state.metricValue(metricValue);
    DFL::Mdib::Test::MdibWriter::writeMetricState(mdib, oldEntity, state);

    std::function<bool(const DFL::Mdib::EnumStringMetric&)> entityMatcher =
            [=](const DFL::Mdib::EnumStringMetric& entity)
            { return entity.state()->metricValue() == metricValue; };

    return S31::Sdc::Test::Matcher::createModifiedEntityMatcher(oldEntity->handle(), entityMatcher);
}


inline S31::Sdc::Test::Matcher modifyTechnicalRangesInFirstNumericMetric(DFL::Mdib::LocalMdibAccess& mdib)
{
    auto oldEntity = S31::Sdc::Test::firstEntity<DFL::Mdib::NumericMetric>(*mdib.latestMdib());
    DFL::Mdib::NumericMetricDescriptorBuilder desc(oldEntity->descriptor());
    desc.technicalRanges(S31::Sdc::Test::modifyRanges(desc.technicalRanges()));
    DFL::Mdib::Test::MdibWriter::writeDescriptor(mdib, oldEntity, desc);

    std::function<bool(const DFL::Mdib::NumericMetric&)> entityMatcher =
            [=](const DFL::Mdib::NumericMetric& entity)
            { return entity.descriptor()->technicalRanges() == desc.technicalRanges(); };

    return S31::Sdc::Test::Matcher::createModifiedEntityMatcher(oldEntity->handle(), entityMatcher);
}

inline S31::Sdc::Test::Matcher modifyPhysiologicalRangesInFirstNumericMetric(DFL::Mdib::LocalMdibAccess& mdib)
{
    auto oldEntity = S31::Sdc::Test::firstEntity<DFL::Mdib::NumericMetric>(*mdib.latestMdib());
    DFL::Mdib::NumericMetricStateBuilder state(oldEntity->state());
    state.physiologicalRanges(S31::Sdc::Test::modifyRanges(state.physiologicalRanges()));
    DFL::Mdib::Test::MdibWriter::writeMetricState(mdib, oldEntity, state);

    std::function<bool(const DFL::Mdib::NumericMetric&)> entityMatcher =
            [=](const DFL::Mdib::NumericMetric& entity)
            { return entity.state()->physiologicalRanges() == state.physiologicalRanges(); };

    return S31::Sdc::Test::Matcher::createModifiedEntityMatcher(oldEntity->handle(), entityMatcher);
}

inline S31::Sdc::Test::Matcher modifyDeterminationPeriodsInFirstNumericMetric(DFL::Mdib::LocalMdibAccess& mdib)
{
    auto oldEntity = S31::Sdc::Test::firstEntity<DFL::Mdib::NumericMetric>(*mdib.latestMdib());
    DFL::Mdib::NumericMetricDescriptorBuilder desc(oldEntity->descriptor());
    desc.determinationPeriod(S31::Sdc::Test::modifyDuration(desc.determinationPeriod()));
    DFL::Mdib::NumericMetricStateBuilder state(oldEntity->state());
    state.activeDeterminationPeriod(S31::Sdc::Test::modifyDuration(state.activeDeterminationPeriod()));
    DFL::Mdib::Test::MdibWriter::writeDescriptor(mdib, oldEntity, desc, state);

    std::function<bool(const DFL::Mdib::NumericMetric&)> entityMatcher =
            [=](const DFL::Mdib::NumericMetric& entity)
            { return (entity.descriptor()->determinationPeriod() == desc.determinationPeriod())
                && (entity.state()->activeDeterminationPeriod() == state.activeDeterminationPeriod()); };

    return S31::Sdc::Test::Matcher::createModifiedEntityMatcher(oldEntity->handle(), entityMatcher);
}

inline S31::Sdc::Test::Matcher modifyTypeTranslationsInFirstNumericMetric(DFL::Mdib::LocalMdibAccess& mdib)
{
    auto oldEntity = S31::Sdc::Test::firstEntity<DFL::Mdib::NumericMetric>(*mdib.latestMdib());
    DFL::Mdib::NumericMetricDescriptorBuilder desc(oldEntity->descriptor());
    desc.type(S31::Sdc::Test::modifyTranslation(desc.type()));
    DFL::Mdib::Test::MdibWriter::writeDescriptor(mdib, oldEntity, desc);

    std::function<bool(const DFL::Mdib::NumericMetric&)> entityMatcher =
            [=](const DFL::Mdib::NumericMetric& entity)
            { return entity.descriptor()->type() == desc.type(); };

    return S31::Sdc::Test::Matcher::createModifiedEntityMatcher(oldEntity->handle(), entityMatcher);
}

inline S31::Sdc::Test::Matcher modifyActivationInFirstNumericMetric(DFL::Mdib::LocalMdibAccess& mdib)
{
    auto oldEntity = S31::Sdc::Test::firstEntity<DFL::Mdib::NumericMetric>(*mdib.latestMdib());
    DFL::Mdib::NumericMetricStateBuilder state(oldEntity->state());
    state.activationState(S31::Sdc::Test::modifyComponentActivation(state.activationState()));
    DFL::Mdib::Test::MdibWriter::writeMetricState(mdib, oldEntity, state);

    std::function<bool(const DFL::Mdib::NumericMetric&)> entityMatcher =
            [=](const DFL::Mdib::NumericMetric& entity)
            { return entity.state()->activationState() == state.activationState(); };

    return S31::Sdc::Test::Matcher::createModifiedEntityMatcher(oldEntity->handle(), entityMatcher);
}

/**
 * @brief The given client connects to the given device and transmits data.
 * @details It's required that the device Mdib contains a numeric metric. So this ensures that client can connect to the device
 * and that the device can notify the client about Mdib changes.
 */
inline void shallConnectAndCommunicate(TestClient& client, TestDevice& device)
{
    ASSERT_TRUE(client.connect(std::chrono::seconds{10}, device.epr()))
            << "client failed to connect to device " << device.epr().address().str();
    auto changesObserver = client.createMdibChangesObserver(device.epr());
    auto matcher = modifyActivationInFirstNumericMetric(*device.localMdibAccess());
    EXPECT_TRUE(changesObserver->waitFor(std::chrono::seconds{10}, matcher.changesMatcher, DFL::Mdib::MdibChangeType::MetricStates));
}

#define SHALL_CONNECT_AND_COMMUNICATE(client, device)  do { SCOPED_TRACE(""); shallConnectAndCommunicate(client, device); } while(false)

}
