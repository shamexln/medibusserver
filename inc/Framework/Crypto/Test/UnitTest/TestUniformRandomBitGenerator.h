#pragma once

#include <cmath>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <utility>

namespace DFLTest
{
namespace Crypto
{
namespace UnitTest
{
template <class UniformRandomBitGenerator>
inline bool testMin()
{
    using Type = typename UniformRandomBitGenerator::result_type;
    return (UniformRandomBitGenerator::min)() ==
           (std::numeric_limits<Type>::min)();
}

template <class UniformRandomBitGenerator>
inline bool testMax()
{
    using Type = typename UniformRandomBitGenerator::result_type;
    return (UniformRandomBitGenerator::max)() ==
           (std::numeric_limits<Type>::max)();
}

// NIST Statistical Test Suite - Monobit Test
// https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf
// chapter 2.1: Frequency (Monobit) Test
template <class UniformRandomBitGenerator>
inline std::pair<int, int> testMonobit(int n,
                                       UniformRandomBitGenerator& urbg,
                                       int& sn)
{
    // NOLINTNEXTLINE(misc-const-correctness)
    std::uniform_int_distribution<int> dist{0, 1};

    // Sn = noOfOnes - noOfZeros
    int Sn = 0;
    for (int i{0}; i < n; ++i)
    {
        Sn += 2 * dist(urbg) - 1;
    }

    // Given: P-value >= 0.01
    // P-value = erfc(erfcParam)
    // erfcParam = (abs(Sn) / sqrt(n)) / sqrt(2)

    // erfcParam is determined iteratively with a calculator so that
    // erfc(erfcParam) >= 0.01
    const double erfcParam = 1.821386;

    const int maxAbsSn{
        static_cast<int>(std::floor(erfcParam * std::sqrt(2.0 * n)))};
    sn = Sn;
    const int absSn{std::abs(Sn)};
    return std::make_pair(maxAbsSn, absSn);
}

template <class UniformRandomBitGenerator>
inline bool testMonobit(std::string& message)
{
    // according to https://www.random.org/analysis/Analysis2005.pdf, chapter N:
    // random.org (which claims to offer _true_ random numbers) has only a
    // success rate of 98% with a input size of 100.
    const float minSuccessRatePercent{97.0f};
    const int inputSize{100};

    const int numberOfTests{1000};
    int numberOfSuccessfulTests{0};
    UniformRandomBitGenerator urbg;
    std::ostringstream str;

    for (int i{0}; i < numberOfTests; ++i)
    {
        int sn{};
        const auto& result = testMonobit(inputSize, urbg, sn);
        const int maxAbsSn{result.first};
        const int absSn{result.second};
        if (absSn <= maxAbsSn)
        {
            ++numberOfSuccessfulTests;
        }
        else
        {
            str << "Diff between number of 0s and 1s should be max. "
                << maxAbsSn << ", but was " << absSn << " with sn = " << sn
                << '\n';
        }
    }

    const float successRatePercent{100.0f *
                                   static_cast<float>(numberOfSuccessfulTests) /
                                   static_cast<float>(numberOfTests)};
    str << "Min. " << minSuccessRatePercent
        << "% of tests should pass, but was " << successRatePercent << "%";
    message = str.str();

    return successRatePercent >= minSuccessRatePercent;
}
}
}
}
