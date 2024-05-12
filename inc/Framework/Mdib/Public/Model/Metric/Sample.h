#pragma once

#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Decimals.h>
#include <Framework/Mdib/Public/Model/Metric/Annotation.h>
#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief A single sample of a \ref SampleArrayValue.
 * @ingroup Mdib
 */
class Sample
{
    public:
        /**
         * @brief Constructor that creates a sample without annotations.
         */
        explicit Sample(Decimal value);

        /**
         * @brief Constructor that creates a sample with annotations.
         */
        Sample(Decimal value, const Annotations& annotations);

        /**
         * @brief Constructor that creates a sample with annotations.
         */
        Sample(Decimal value, Annotations&& annotations);

        /**
         * @brief Returns the decimal number of the sample.
         */
        Decimal value() const;

        /**
         * @brief Returns the list of annotations that is attached to the sample.
         */
        const Annotations& annotations() const;

    private:
        Decimal m_value;
        Annotations m_annotations;
};

/**
 * @brief A sequence of \ref Sample objects.
 * @ingroup Mdib
 */
using Samples = std::vector<Sample>;


inline Sample::Sample(Decimal value) :
        m_value(value),
        m_annotations()
{
}

inline Sample::Sample(Decimal value,
                      const Annotations& annotations) : // NOLINT(modernize-pass-by-value)
        m_value(value),
        m_annotations(annotations)
{
}

inline Sample::Sample(Decimal value, Annotations&& annotations) :
        m_value(value),
        m_annotations(std::move(annotations))
{
}

inline Decimal Sample::value() const
{
    return m_value;
}

inline const Annotations& Sample::annotations() const
{
    return m_annotations;
}

/**
 * @brief operator == for @ref Sample
 * @details Note that order of annotations matters.
 * @ingroup Mdib
 */
inline bool operator==(const Sample& lhs, const Sample& rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.value() == rhs.value() && lhs.annotations() == rhs.annotations();
}

/**
 * @brief operator != for @ref Sample
 * @ingroup Mdib
 */
inline bool operator!=(const Sample& lhs, const Sample& rhs)
{
    return !(lhs == rhs);
}

/**
 * @brief Creates @ref DFL::Mdib::Samples "Samples" (containing no annotations)
 * from @ref DFL::Mdib::Decimals "Decimals".
 * @ingroup Mdib
 */
inline Samples makeSamples(const Decimals& source)
{
    Samples result;
    result.reserve(source.size());
    for (const auto& decimal : source)
    {
        result.push_back(Sample(decimal));
    }
    return result;
}

} /* namespace Mdib */
} /* namespace DFL */
