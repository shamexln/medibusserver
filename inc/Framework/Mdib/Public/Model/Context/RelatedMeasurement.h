#pragma once

#include <Framework/Mdib/Public/Model/Measurement.h>
#include <Framework/Mdib/Public/Model/ReferenceRange.h>
#include <Framework/Mdib/Public/Model/Metric/MeasurementValidity.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Related measurements for this clinical observation if applicable.
 * @ingroup Mdib
 */
class RelatedMeasurement
{
    public:
        /**
         * @brief Constructor.
         */
        RelatedMeasurement(boost::optional<MeasurementValidity> validity,
                           const Measurement& value,
                           const ReferenceRanges& referenceRange);

        /**
         * @brief Validity of the related measurement. See also \ref MeasurementValidity.
         * @return Validity
         */
        boost::optional<MeasurementValidity> validity() const;

        /**
         * @brief Value of related measurement
         * @return Value
         */
        const Measurement& value() const;

        /**
         * @brief Representation of the normal or abnormal reference range for the measurement.
         * @return Range value
         */
        const ReferenceRanges& referenceRange() const;

    private:
        boost::optional<MeasurementValidity> m_validity;
        Measurement m_value;
        ReferenceRanges m_referenceRange;
};

inline RelatedMeasurement::RelatedMeasurement(boost::optional<MeasurementValidity> validity,
                                              const Measurement& value,
                                              const ReferenceRanges& referenceRange) :
        m_validity(validity),
        m_value(value),
        m_referenceRange(referenceRange)
{
}

inline boost::optional<MeasurementValidity> RelatedMeasurement::validity() const
{
    return m_validity;
}

inline const Measurement& RelatedMeasurement::value() const
{
    return m_value;
}

inline const ReferenceRanges& RelatedMeasurement::referenceRange() const
{
    return m_referenceRange;
}

} /* namespace Mdib */
} /* namespace DFL */
