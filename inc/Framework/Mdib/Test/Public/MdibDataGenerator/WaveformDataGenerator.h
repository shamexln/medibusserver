#pragma once

#include <vector>
#include <boost/math/constants/constants.hpp>
#include <Framework/Chrono/Public/Duration.h>
#include <Framework/Chrono/Public/TimePoint.h>
#include <Framework/Chrono/Public/SystemClock.h>
#include <Framework/Mdib/Public/Model/Decimals.h>
#include <Framework/Mdib/Public/Model/DecimalConvert.h>
#include <Framework/Utils/Public/StrongTypedef.h>
#include <Framework/Mdib/Test/Public/MdibDataGenerator/CommonTypes.h>

namespace DFL
{
namespace Mdib
{
namespace Test
{

struct SamplesPerSecondTag;
using SamplesPerSecond = DFL::StrongTypedef<unsigned int, SamplesPerSecondTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Data source for waveforms/real time sample arrays.
 * @details Datapoints of a function.
 */
class Wave
{
    public:
        /// Constructor.
        explicit Wave(SamplesPerSecond samplesPerSecond):
            m_samplesPerSecond(samplesPerSecond)
        {}

        /// Destructor.
        virtual ~Wave() = default;

        /**
         * @brief Returns the samples from start to start + duration.
         */
        Decimals samples(MdibTimePoint start, Duration segment) const;

        /**
         * @brief Returns the duration between 2 sample points.
         */
        DFL::Chrono::Microseconds samplePeriod() const;

    protected:
        /**
         * @brief The value of the function for a given time point.
         */
        virtual Decimal value(MdibTimePoint t) const = 0;

        /**
         * @brief Get the samples per second.
         */
        SamplesPerSecond samplesPerSecond() const;

    private:
        SamplesPerSecond m_samplesPerSecond;
};

struct PeriodLengthTag;
using PeriodLength = DFL::StrongTypedef<Duration, PeriodLengthTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief Periodic function.
 */
class PeriodicWave: public Wave
{
    public:
        /// Constructor.
        PeriodicWave(SamplesPerSecond samplesPerSecond, PeriodLength period):
            Wave(samplesPerSecond),
            m_periodLength(period)
        {}

    protected:
        /**
         * @brief Get the period length.
         */
        PeriodLength periodLength() const;

    private:
        PeriodLength m_periodLength;
};

/**
 * @brief A sawtooth function.
 */
class SawtoothWave: public PeriodicWave
{
    public:
        /// Constructor.
        SawtoothWave(PeriodLength periodLength, SamplesPerSecond samplesPerSecond):
            PeriodicWave(samplesPerSecond, periodLength)
        {}

    protected:
        Decimal value(MdibTimePoint t) const override;

};

/**
 * @brief A sine function.
 */
class SinusWave: public PeriodicWave
{
    public:
        /// Constructor.
        SinusWave(PeriodLength periodLength, SamplesPerSecond samplesPerSecond):
            PeriodicWave(samplesPerSecond, periodLength)
        {}

    protected:
        Decimal value(MdibTimePoint t) const override;

};

inline Decimals Wave::samples(MdibTimePoint start, Duration segment) const
{
    Decimals result;
    const DFL::Chrono::Microseconds betweenSamples(1000000/samplesPerSecond().get());
    auto current = start;
    while (current < start + segment)
    {
        result.push_back(value(current));
        current += betweenSamples;
    }
    return result;
}

inline Chrono::Microseconds Wave::samplePeriod() const
{
    return DFL::Chrono::Microseconds{1000000 / m_samplesPerSecond.get()};
}

inline SamplesPerSecond Wave::samplesPerSecond() const
{
    return m_samplesPerSecond;
}

inline PeriodLength PeriodicWave::periodLength() const
{
    return m_periodLength;
}

inline Decimal SawtoothWave::value(MdibTimePoint t) const
{
    const auto tduration = t.time_since_epoch();
    const auto remainder = tduration % periodLength().get();
    return DFL::Mdib::Convert::toDecimal(
                static_cast<double>(remainder.count())
                /
                static_cast<double>(periodLength().get().count()));
}

inline Decimal SinusWave::value(MdibTimePoint t) const
{
    const auto tduration = t.time_since_epoch();
    const auto remainder = tduration % periodLength().get();
    return DFL::Mdib::Convert::toDecimal(
                sin(
                    (static_cast<double>(remainder.count()) * 2 * boost::math::constants::pi<double>())
                    /
                    static_cast<double>(periodLength().get().count())));
}

}
}
}
