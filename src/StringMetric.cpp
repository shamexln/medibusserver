#include <StringMetric.h>

#include <S31/Log/Public/Logger.h>
#include <Framework/Mdib/Public/Model/Metric/StringMetricValueBuilder.h>
#include <Framework/Mdib/Test/Public/TestFactory.h>
#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Thread/Public/Thread.h>

#include <iostream>
#include <iomanip>

using namespace S31::Samples;

S31_LOGGER("TestDevice");

const auto HandleStringMetric = DFL::Mdib::StringMetricHandle("string_metric_setting1");

void StringMetric::initMdib(DFL::Mdib::MdibChangeSet& changeSet, DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>> /*vmd*/, DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel) const
 {
    DFL::Mdib::StringMetricDescriptorBuilder desc;
    {
        desc.type(DFL::Mdib::Test::TestFactory::hashCodedValue(HandleStringMetric.string()));
        desc.metricCategory(DFL::Mdib::MetricCategory::Setting);
        desc.metricAvailability(DFL::Mdib::MetricAvailability::Intermittent);
        desc.unit(DFL::Mdib::Unit::DIMLESS);
    }

    DFL::Mdib::StringMetricStateBuilder state;
    state.activationState(DFL::Mdib::ComponentActivation::On);

    auto string = DFL::Mdib::EntityFactory::create(HandleStringMetric, desc, state, channel->handle());
    changeSet.addOneToInsert(string);
}

void StringMetric::metricUpdateThread()
{
    int interval = 1000; // Loop interval in milliseconds.
    int value = 0;

    while (m_running)
    {
        auto currentMillis = DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(DFL::Chrono::SystemClock::now().time_since_epoch()).count();
        auto previousTick = currentMillis - (currentMillis % interval);
        auto nextTick = previousTick + interval;

        std::stringstream metric;
        value = (value + 1) % 100;
        metric << "Value:" << value;

        writeMetricValue(HandleStringMetric, metric.str());

        std::stringstream msg;
        msg << "\r\nStringMetric: " << "set " << HandleStringMetric.string() << " to '" << std::setw(2) << metric.str() << "'\x1b[A";
        std::cout << msg.str();

        auto waitTime=DFL::Chrono::Milliseconds(DFL::Chrono::Milliseconds(nextTick - DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(DFL::Chrono::SystemClock::now().time_since_epoch()).count()));
        if (waitTime>DFL::Chrono::Milliseconds(0))
        {
            DFL::Thread::ThisThread::sleepFor(waitTime);
        }
    }
}

void StringMetric::writeMetricValue(const DFL::Mdib::StringMetricHandle& handle, const std::string& value)
{
    auto now = DFL::Chrono::SystemClock::now();
    auto stringMetric = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::StringMetricHandle(handle));
    if (stringMetric)
    {
        DFL::Mdib::StringMetricValueBuilder stringMetricValueBuilder;

        stringMetricValueBuilder.value(DFL::Locale::Utf8(value));
        stringMetricValueBuilder.metricQuality(DFL::Mdib::MetricQuality(DFL::Mdib::MeasurementValidity::Valid));
        stringMetricValueBuilder.determinationTime(now);
        stringMetricValueBuilder.startTime(now);
        stringMetricValueBuilder.stopTime(now + DFL::Mdib::Duration(DFL::Chrono::Milliseconds(1000)));

        DFL::Mdib::StringMetricStateBuilder builder(stringMetric->state());
        builder.activationState(DFL::Mdib::ComponentActivation::NotReady);
        builder.metricValue(stringMetricValueBuilder.build());

        DFL::Mdib::MdibChangeSet changeSet;
        changeSet.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(stringMetric), builder));
       
        THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeMetricStates(changeSet));
    }
}
