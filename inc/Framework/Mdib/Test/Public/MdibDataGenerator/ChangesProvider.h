#pragma once

#include <functional>
#include <map>
#include <boost/optional.hpp>
#include <Framework/Chrono/Public/SteadyClock.h>
#include <Framework/Mdib/Private/Log.h>
#include <Framework/Mdib/Public/LocalMdibAccess.h>
#include <Framework/Mdib/Public/LocalMdibAccessSmartPtrTypes.h>
#include <Framework/Mdib/Public/Mdib.h>
#include <Framework/Mdib/Public/MdibChangeSet.h>
#include <Framework/Mdib/Public/WriteResultIo.h>
#include <Framework/Mdib/Public/Model/EntityFactory.h>
#include <Framework/Mdib/Public/Model/HandleIo.h>
#include <Framework/Mdib/Public/Model/Metric/RealTimeSampleArrayMetric.h>
#include <Framework/Mdib/Public/WriteResult.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/Annotations.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/CommonTypes.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/RecurringTasks.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/WaveformDataGenerator.h>


namespace DFL
{
namespace Mdib
{
namespace Test
{

struct UpdatesPerSecondTag;
using UpdatesPerSecond = DFL::StrongTypedef<unsigned int, UpdatesPerSecondTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;
using RealTimeSampleArrayMetricStateCallback = std::function<void(const RealTimeSampleArrayMetricHandle&, RealTimeSampleArrayMetricStateBuilder&)>;

/**
 * @brief A recurring task that changes waves in the given Mdib.
 * @details
 * ### Clocks
 * The repeating notification is controlled by the SteadyClock while Mdib timepoints use the SystemClock.
 * SystemClock changes have no effect on notification interval.
 * The usage of both clocks is synchronized from time to time (see m_syncSystemAndSteadyClockCounter).
 */
class WaveformChanger: public RecurringTask
{
    public:
        /**
         * @brief Constructor.
         * @param mdibAccess Mdib access.
         * @param updatesPerSecond Updates of the Mdib per second e.g. if this is 10 and the waveform generates 50 samples per second
         *                         then there will be 10 updates for the waveform in the Mdib with 5 samples each (per second).
         * @param callback Callback to modify the new RealTimeSampleArrayMetricState (e.g. customize annotations,...).
         */
        WaveformChanger(LocalMdibAccessWeakPtr mdibAccess, UpdatesPerSecond updatesPerSecond, RealTimeSampleArrayMetricStateCallback callback):
            m_mdibAccess(std::move(mdibAccess)),
            m_durationBetweenUpdates(DFL::Chrono::Microseconds(1000000 / updatesPerSecond.get())),
            m_onBuildStateCallback(callback)
        {}

        /// Type alias.
        using WavePtr = DFL::NotNull<std::unique_ptr<Wave>>;

        /**
         * @brief Add a waveform given by a data source (wave) and a Mdib handle.
         */
        void add(WavePtr wave, RealTimeSampleArrayMetricHandle handle, AnnotationAdderPtr annotation = nullptr);

        ExecutionTimepoint execute() override;

    private:
        struct WaveContext
        {
            WavePtr wave;
            AnnotationAdderPtr annotationAdder;
        };

        LocalMdibAccessWeakPtr m_mdibAccess;
        DFL::Chrono::Microseconds m_durationBetweenUpdates;
        RealTimeSampleArrayMetricStateCallback m_onBuildStateCallback;
        std::map<RealTimeSampleArrayMetricHandle, WaveContext> m_waves;
        boost::optional<ExecutionTimepoint> m_lastExecution;
        boost::optional<MdibTimePoint> m_lastDeterminationTime;
        int m_syncSystemAndSteadyClockCounter{0};

        void execute(const RealTimeSampleArrayMetricHandle& handle,
                const WaveContext& waveContext,
                const Mdib& mdib,
                MdibChangeSet& changes);
};

inline void WaveformChanger::add(WavePtr wave, RealTimeSampleArrayMetricHandle handle, AnnotationAdderPtr annotation)
{
    WaveContext context{std::move(wave), std::move(annotation)};
    m_waves.insert(std::make_pair(handle, std::move(context)));
}

inline ExecutionTimepoint WaveformChanger::execute()
{
    if (!m_lastExecution)
    {
        m_lastExecution = DFL::Chrono::SteadyClock::now();
    }
    else
    {
        *m_lastExecution += m_durationBetweenUpdates;
    }

    if (!m_lastDeterminationTime || m_syncSystemAndSteadyClockCounter++ > 1000)
    {
        m_lastDeterminationTime = DFL::Chrono::SystemClock::now();
        m_syncSystemAndSteadyClockCounter = 0;
    }
    else
    {
        *m_lastDeterminationTime += m_durationBetweenUpdates;
    }

    const ExecutionTimepoint result = *m_lastExecution + m_durationBetweenUpdates;
    LocalMdibAccessSharedPtr mdibAccess = m_mdibAccess.lock();
    if (!mdibAccess)
    {
        DFL_MDIB_STREAM_ERROR("No MdibAccess.");
        return result;
    }

    const auto mdib = mdibAccess->latestMdib();
    MdibChangeSet changes;

    for (const auto& wave : m_waves)
    {
        execute(wave.first, wave.second, *mdib, changes);
    }

    auto writeResult = mdibAccess->writeSampleArrayMetricStates(changes);
    if (writeResult.status() != WriteStatus::Success)
    {
        DFL_MDIB_STREAM_ERROR("Writing into Mdib failed: ", writeResult);
    }

    return result;
}

inline void WaveformChanger::execute(const RealTimeSampleArrayMetricHandle& handle, const WaveContext& waveContext, const Mdib& mdib, MdibChangeSet& changes)
{
    const auto& entity = mdib.entity(handle);
    if (!entity)
    {

        DFL_MDIB_STREAM_ERROR(handle, " not found.");
        return;
    }

    const auto pureSamples = waveContext.wave->samples(*m_lastDeterminationTime - m_durationBetweenUpdates, m_durationBetweenUpdates);
    Samples samples;
    samples.reserve(pureSamples.size());
    for (const auto& s : pureSamples)
    {
        if (auto& a = waveContext.annotationAdder)
        {
            samples.push_back(a->add(Sample(s)));
        }
        else
        {
            samples.push_back(Sample(s));
        }
    }

    SampleArrayValue sav(
                MetricQuality(MeasurementValidity::Valid),
                Annotations(),
                boost::none,
                boost::none,
                *m_lastDeterminationTime - m_durationBetweenUpdates,
                std::move(samples));

    auto builder = getBuilder(entity->state());
    builder.metricValue(sav);
    m_onBuildStateCallback(handle, builder);
    changes.addOneToUpdate(EntityFactory::create(*entity, builder));
}

}
}
}
