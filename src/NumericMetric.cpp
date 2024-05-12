#include <NumericMetric.h>

#include <S31/Log/Public/Logger.h>
#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Model/Metric/NumericMetricValueBuilder.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>
#include <Framework/Thread/Public/Thread.h>

#include <iomanip>
#include <iostream>

using namespace S31::Samples;

S31_LOGGER("TestDevice");

const auto HandleNumericMetric = "SampleNumericHandle";

void NumericMetric::initMdib(
        DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> /*vmd*/, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel) const
{
    DFL::Mdib::NumericMetricDescriptorBuilder desc;
    {
        desc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(HandleNumericMetric));
        desc.metricCategory(DFL::Mdib::MetricCategory::Measurement);
        desc.unit(DFL::Mdib::Unit::MILLI_VOLT);
        desc.technicalRanges(DFL::Mdib::Ranges{ DFL::Mdib::Range(DFL::Mdib::Decimal(1), DFL::Mdib::Decimal(100)) });
        desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Seconds{1}});
        desc.lifeTimePeriod(DFL::Mdib::Duration{DFL::Chrono::Hours{24}});
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
            DFL::Mdib::NumericMetricHandle(HandleNumericMetric), desc, state, channel->handle());

    changeSet.addOneToInsert(numeric);
    
}

void NumericMetric::metricUpdateThread()
{
    int interval = 500;  // Loop interval in milliseconds.
    int value    = 0;

    while (m_running)
    {
        auto currentMillis = DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(
                                     DFL::Chrono::SystemClock::now().time_since_epoch())
                                     .count();
        auto previousTick = currentMillis - (currentMillis % interval);
        auto nextTick     = previousTick + interval;

        value = (value + 1) % 100;
        //writeMetricValue(HandleNumericMetric, value);

        std::stringstream msg;
        msg << "\rNumericMetric: "
                  << "set " << HandleNumericMetric << " to " << std::setw(2) << value << "\r";
        std::cout << msg.str();

        auto waitTime = DFL::Chrono::Milliseconds(DFL::Chrono::Milliseconds(
                nextTick
                - DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(
                          DFL::Chrono::SystemClock::now().time_since_epoch())
                          .count()));
        if (waitTime > DFL::Chrono::Milliseconds(0))
        {
            DFL::Thread::ThisThread::sleepFor(waitTime);
        }
    }
}

void NumericMetric::writeMetricValue(const std::string& handle, int value)
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

        DFL::Mdib::MdibChangeSet changeSet;
        changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(numericMetric), state));

        THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeMetricStates(changeSet));
    }
}
