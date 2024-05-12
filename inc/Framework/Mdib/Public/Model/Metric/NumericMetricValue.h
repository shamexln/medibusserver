#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricValue.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Numeric value of a \ref NumericMetricState.
 * @ingroup Mdib
 */
class NumericMetricValue: public AbstractMetricValue
{
    public:
        /**
         * @brief Defaults to an invalid metric without a value.
         */
        NumericMetricValue() = default;

        /**
         * @brief Constructor.
         */
        NumericMetricValue(const MetricQuality& metricQuality,
                           const Annotations& annotations,
                           const boost::optional<Timestamp>& startTime,
                           const boost::optional<Timestamp>& stopTime,
                           const boost::optional<Timestamp>& determinationTime,
                           boost::optional<Decimal> value,
                           ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The value of a numeric metric.
         * @return Value or \c boost::none if undefined.
         */
        boost::optional<Decimal> value() const;

    private:
        boost::optional<Decimal> m_value;
};

/**
 * @brief Equal compare of \ref NumericMetricValue.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are equal.
 */
DFL_MDIB_EXPIMP bool operator==(const NumericMetricValue& lhs, const NumericMetricValue& rhs);

/**
 * @brief Not equal compare of \ref NumericMetricValue.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are not equal.
 */
DFL_MDIB_EXPIMP bool operator!=(const NumericMetricValue& lhs, const NumericMetricValue& rhs);

inline NumericMetricValue::NumericMetricValue(const MetricQuality& metricQuality,
                                              const Annotations& annotations,
                                              const boost::optional<Timestamp>& startTime,
                                              const boost::optional<Timestamp>& stopTime,
                                              const boost::optional<Timestamp>& determinationTime,
                                              boost::optional<Decimal> value,
                                              ExtensionTypes extensions) :
        AbstractMetricValue(metricQuality, annotations, startTime, stopTime, determinationTime, std::move(extensions)),
        m_value(std::move(value))
{
}

inline boost::optional<Decimal> NumericMetricValue::value() const
{
    return m_value;
}

} /* namespace Mdib */
} /* namespace DFL */
