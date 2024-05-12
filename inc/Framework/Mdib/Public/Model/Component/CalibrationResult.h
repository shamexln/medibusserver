#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/CodedValue.h>
#include <Framework/Mdib/Public/Model/Measurement.h>

#include <boost/optional/optional.hpp>

#include <vector>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Result of a calibration event.
 * @ingroup Mdib
 */
class CalibrationResult
{
    public:
        /**
         * @brief Constructor.
         */
        CalibrationResult(const CodedValue& code, const Measurement& value);

        /**
         * @brief Code that semantically describes the calibration result.
         */
        const CodedValue& code() const;

        /**
         * @brief Measurement that represents the value related to that specific calibration result.
         */
        const Measurement& value() const;

    private:
        CodedValue m_code;
        Measurement m_value;
};

/**
 * @brief Sequence of \ref CalibrationResult.
 * @ingroup Mdib
 */
using CalibrationResults = std::vector<CalibrationResult>;

inline CalibrationResult::CalibrationResult(const CodedValue& code, // NOLINT(modernize-pass-by-value)
                                            const Measurement& value) : // NOLINT(modernize-pass-by-value)
        m_code(code),
        m_value(value)
{
}

inline const CodedValue& CalibrationResult::code() const
{
    return m_code;
}

inline const Measurement& CalibrationResult::value() const
{
    return m_value;
}

bool operator==(const CalibrationResult &lhs, const CalibrationResult &rhs);
bool operator!=(const CalibrationResult &lhs, const CalibrationResult &rhs);

/// Comparator for CalibrationResult
/// @ingroup Mdib
inline bool operator==(const CalibrationResult &lhs, const CalibrationResult &rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.code() == rhs.code() &&
            lhs.value() == rhs.value();
}

/// Comparator for CalibrationResult
/// @ingroup Mdib
inline bool operator!=(const CalibrationResult &lhs, const CalibrationResult &rhs)
{
    return !(lhs == rhs);
}


} /* namespace Mdib */
} /* namespace DFL */
