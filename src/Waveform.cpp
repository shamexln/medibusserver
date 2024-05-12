#include <Waveform.h>

#include <S31/Log/Public/Logger.h>

#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/Model/Component/Channel.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/Model/Metric/SampleArrayValue.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Thread/Public/Thread.h>

#include <iomanip>
#include <iostream>
#define _USE_MATH_DEFINES  // for M_PI
#include <math.h>

using namespace S31::Samples;

S31_LOGGER("TestDevice");

const auto HandleWaveform = "sample_waveform";

namespace
{
constexpr int samplesPerSecond{100};

std::vector<double> generateSineWaveValues()
{
    const int    seconds{1};
    const int    numSamples = samplesPerSecond * seconds;
    const double frequency  = 1;

    std::vector<double> sineWaveValues(numSamples);

    // Compute sine wave values
    for (int i = 0; i < numSamples; ++i)
    {
        double time       = i / static_cast<double>(samplesPerSecond);
        sineWaveValues[i] = sin(2.0 * M_PI * frequency * time);
    }

    // generate normalized (1, -1) values
    double maxAbsValue = 0.0;
    for (int i = 0; i < numSamples; ++i)
    {
        double absValue = std::abs(sineWaveValues[i]);
        if (absValue > maxAbsValue)
        {
            maxAbsValue = absValue;
        }
    }
    if (maxAbsValue > 0.0)
    {
        for (int i = 0; i < numSamples; ++i)
        {
            sineWaveValues[i] /= maxAbsValue;
        }
    }
    return sineWaveValues;
}
}  // namespace


Waveform::Waveform(DFL::NotNull<DFL::Mdib::LocalMdibAccessSharedPtr>& localMdibAccess)
    : ContinuousBase(localMdibAccess)
    , m_samples{generateSineWaveValues()}
{
}

void Waveform::initMdib(
        DFL::Mdib::MdibChangeSet& changeSet,
        DFL::NotNull<std::shared_ptr<DFL::Mdib::Vmd>>     /*vmd*/, 
        DFL::NotNull<std::shared_ptr<DFL::Mdib::Channel>> channel) const
{
    auto type = DFL::Mdib::CodedValueFactory::create11073cfCode("121212");
    DFL::Mdib::RealTimeSampleArrayMetricDescriptorBuilder desc;
    {
        desc.type(type);
        desc.unit(DFL::Mdib::Unit::CENTI_M);
        desc.samplePeriod(DFL::Chrono::Milliseconds(4));
        desc.metricCategory(DFL::Mdib::MetricCategory::Unspecified);
        desc.metricAvailability(DFL::Mdib::MetricAvailability::Continuous);
        desc.determinationPeriod(DFL::Mdib::Duration{DFL::Chrono::Milliseconds{100}});
    }

    auto rtsa2 = DFL::Mdib::EntityFactory::create(
            DFL::Mdib::RealTimeSampleArrayMetricHandle("sample_waveform"), desc, channel->handle());
    changeSet.addOneToInsert(rtsa2);
}

void Waveform::start()
{
    const auto sample_waveform = DFL::Mdib::RealTimeSampleArrayMetricHandle("sample_waveform");

    DFL::Mdib::MdibChangeSet changes;
    const auto               mdib   = m_localMdibAccess->latestMdib();
    const auto               entity = mdib->entity(sample_waveform);
    if (!entity)
    {
        throw std::runtime_error("sample_waveform not found");
    }
    auto descr = DFL::Mdib::getBuilder(entity->descriptor());
    descr.technicalRanges(DFL::Mdib::Ranges{DFL::Mdib::Range(DFL::Mdib::Decimal(-1), DFL::Mdib::Decimal(1))});
    descr.samplePeriod(DFL::Mdib::Duration(DFL::Chrono::Microseconds(1000000 / samplesPerSecond)));

    changes.addOneToUpdate(DFL::Mdib::EntityFactory::create(DFL::asNotNull(entity), descr));
    THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeDescription(changes));

    ContinuousBase::start();
}


void Waveform::metricUpdateThread()
{
    int interval = 1000;  // Loop interval in milliseconds.

    while (m_running)
    {
        auto currentMillis = DFL::Chrono::duration_cast<DFL::Chrono::Milliseconds>(
                                     DFL::Chrono::SystemClock::now().time_since_epoch())
                                     .count();
        auto previousTick = currentMillis - (currentMillis % interval);
       // auto nextTick = currentMillis + interval;
        auto nextTick = previousTick + interval;

        auto determinationTime = DFL::Chrono::SystemClock::now();
      // writeWaveformSample(HandleWaveform, determinationTime);

        std::stringstream msg;
        msg << "\r\n\nWaveform: "
            << "set " << HandleWaveform << " from '" << m_samples[1] << " " << m_samples[2] << "' to '"
            << m_samples[98] << " " << m_samples[99] << "'\x1b[A\x1b[A\r";
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

void Waveform::writeWaveformSample(const std::string& handle, DFL::Chrono::SystemClock::TimePoint determinationTime)
{
    auto entity = m_localMdibAccess->latestMdib()->entity(DFL::Mdib::RealTimeSampleArrayMetricHandle(handle));

    if (entity)
    {
        DFL::Mdib::Samples samples;
        samples.reserve(m_samples.size());
        for (const auto& s : m_samples)
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

        DFL::Mdib::MdibChangeSet changes;
        auto                     builder = getBuilder(entity->state());
        builder.metricValue(sav);
        changes.addOneToUpdate(DFL::Mdib::EntityFactory::create(*entity, builder));
        THROW_ON_MDIB_WRITE_FAILED(m_localMdibAccess->writeSampleArrayMetricStates(changes));
    }
}
