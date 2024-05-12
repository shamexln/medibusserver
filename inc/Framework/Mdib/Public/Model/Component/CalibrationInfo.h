#pragma once

#include <boost/optional/optional.hpp>
#include <utility>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationDocumentation.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationState.h>
#include <Framework/Mdib/Public/Model/Component/CalibrationType.h>
#include <Framework/Mdib/Public/Model/Timestamp.h>
#include <Framework/Mdib/Private/HasExtensions.h>
#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Provides information in terms of component calibration.
 * @details By default it only maintains a calibration flag.
 * @ingroup Mdib
 */
class CalibrationInfo: public Impl::HasExtensions
{
    public:
        /**
         * @brief Defaults to \ref CalibrationType::Unspecified "unspecified calibration type".
         */
        CalibrationInfo() = default;

        /**
         * @brief Constructor.
         */
        CalibrationInfo(const boost::optional<CalibrationState>& componentCalibrationState,
                        CalibrationType type,
                        boost::optional<Timestamp> time,
                        CalibrationDocumentations calibrationDocumentation,
                        ExtensionTypes extensions = ExtensionTypes{ });

        /**
          * @brief The calibration state that is maintained by calibration information.
          */
        const boost::optional<CalibrationState>& componentCalibrationState() const;

        /**
          * @brief Type of the calibration.
          */
        CalibrationType type() const;

        /**
          * @brief Time of calibration.
          */
        const boost::optional<Timestamp>& time() const;

        /**
          * @brief Provides information about the last calibration that was performed.
          */
        const CalibrationDocumentations& calibrationDocumentation() const;

    private:
        boost::optional<CalibrationState> m_componentCalibrationState{};
        CalibrationType m_type{CalibrationType::Unspecified};
        boost::optional<Timestamp> m_time{};
        CalibrationDocumentations m_calibrationDocumentation{};
};

inline CalibrationInfo::CalibrationInfo(const boost::optional<CalibrationState>& componentCalibrationState,
                                        CalibrationType type,
                                        boost::optional<Timestamp> time,
                                        CalibrationDocumentations calibrationDocumentation,
                                        ExtensionTypes extensions):
        Impl::HasExtensions(std::move(extensions)),
        m_componentCalibrationState(componentCalibrationState),
        m_type(type),
        m_time(std::move(time)),
        m_calibrationDocumentation(std::move(calibrationDocumentation))
{
}

inline const boost::optional<CalibrationState>& CalibrationInfo::componentCalibrationState() const
{
    return m_componentCalibrationState;
}

inline CalibrationType CalibrationInfo::type() const
{
    return m_type;
}

inline const boost::optional<Timestamp>& CalibrationInfo::time() const
{
    return m_time;
}

inline const CalibrationDocumentations& CalibrationInfo::calibrationDocumentation() const
{
    return m_calibrationDocumentation;
}

/// Comparator for CalibrationInfo
/// @ingroup Mdib
DFL_MDIB_EXPIMP bool operator==(const CalibrationInfo& lhs, const CalibrationInfo& rhs);

/// Comparator for CalibrationInfo
/// @ingroup Mdib
DFL_MDIB_EXPIMP bool operator!=(const CalibrationInfo& lhs, const CalibrationInfo& rhs);

} /* namespace Mdib */
} /* namespace DFL */
