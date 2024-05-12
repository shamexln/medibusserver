#pragma once

#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationResult.h>
#include <Framework/Mdib/Public/Model/LocalizedTexts.h>

#include <boost/optional/optional.hpp>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Provides information regarding necessary or performed calibration steps including potential calibration results like accuracy.
 * @ingroup Mdib
 */
class CalibrationDocumentation
{
    public:
        /**
         * @brief Empty documentation.
         */
        CalibrationDocumentation() = default;

        /**
         * @brief Constructor.
         */
        CalibrationDocumentation(const LocalizedTexts& localizedTexts,
                CalibrationResults calibrationResults);

        /**
          * @brief Human readable documentation of a %CalibrationDocumentation entry.
          */
        const LocalizedTexts& localizedTexts() const;

        /**
          * @brief Result of calibration.
          */
        const CalibrationResults& calibrationResults() const;

    private:
        LocalizedTexts m_localizedTexts;
        CalibrationResults m_calibrationResults;
};

/**
 * @brief Sequence of \ref CalibrationDocumentation.
 * @ingroup Mdib
 */
using CalibrationDocumentations = std::vector<CalibrationDocumentation>;

inline CalibrationDocumentation::CalibrationDocumentation(const LocalizedTexts& localizedTexts, // NOLINT(modernize-pass-by-value)
                                                          CalibrationResults calibrationResults):
        m_localizedTexts(localizedTexts),
        m_calibrationResults(std::move(calibrationResults))
{
}

inline const LocalizedTexts& CalibrationDocumentation::localizedTexts() const
{
    return m_localizedTexts;
}

inline const CalibrationResults& CalibrationDocumentation::calibrationResults() const
{
    return m_calibrationResults;
}

bool operator==(const CalibrationDocumentation &lhs, const CalibrationDocumentation &rhs);
bool operator!=(const CalibrationDocumentation &lhs, const CalibrationDocumentation &rhs);

/// Comparator for CalibrationDocumentation
/// @ingroup Mdib
inline bool operator==(const CalibrationDocumentation &lhs, const CalibrationDocumentation &rhs)
{
    if (&lhs == &rhs)
    {
        return true;
    }
    return lhs.localizedTexts() == rhs.localizedTexts() &&
            lhs.calibrationResults() == rhs.calibrationResults();
}

/// Comparator for CalibrationDocumentation
/// @ingroup Mdib
inline bool operator!=(const CalibrationDocumentation &lhs, const CalibrationDocumentation &rhs)
{
    return !(lhs == rhs);
}


} /* namespace Mdib */
} /* namespace DFL */
