#pragma once

#include <boost/optional/optional.hpp>
#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Metric/AbstractMetricValue.h>
#include <Framework/Utils/Public/Utf8.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Value of a \ref StringMetricState.
 * @ingroup Mdib
 */
class StringMetricValue : public AbstractMetricValue
{
    public:
        /**
         * @brief Default constructor.
         */
        StringMetricValue() = default;

        /**
         * @brief Constructor to populate all fields.
         */
        StringMetricValue(const MetricQuality& metricQuality,
                          const Annotations& annotations,
                          const boost::optional<Timestamp>& startTime,
                          const boost::optional<Timestamp>& stopTime,
                          const boost::optional<Timestamp>& determinationTime,
                          boost::optional<Locale::Utf8> value,
                          ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The string value.
         * @return Value or \c boost::none if undefined.
         */
        const boost::optional<Locale::Utf8>& value() const;

    private:
        boost::optional<Locale::Utf8> m_value;
};

/**
 * @brief Equal compare of \ref StringMetricValue.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are equal.
 */
DFL_MDIB_EXPIMP bool operator==(const StringMetricValue& lhs, const StringMetricValue& rhs);

/**
 * @brief Not equal compare of \ref StringMetricValue.
 * @param lhs left value for comparison.
 * @param rhs right value for comparison.
 * @return \c true in case all value are not equal.
 */
DFL_MDIB_EXPIMP bool operator!=(const StringMetricValue& lhs, const StringMetricValue& rhs);

inline StringMetricValue::StringMetricValue(const MetricQuality& metricQuality,
                                            const Annotations& annotations,
                                            const boost::optional<Timestamp>& startTime,
                                            const boost::optional<Timestamp>& stopTime,
                                            const boost::optional<Timestamp>& determinationTime,
                                            boost::optional<Locale::Utf8> value,
                                            ExtensionTypes extensions) :
        AbstractMetricValue(metricQuality, annotations, startTime, stopTime, determinationTime, std::move(extensions)),
        m_value(std::move(value))
{
}

inline const boost::optional<Locale::Utf8>& StringMetricValue::value() const
{
    return m_value;
}

} /* namespace Mdib */
} /* namespace DFL */
