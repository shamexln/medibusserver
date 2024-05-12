#pragma once

#include <boost/optional.hpp>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Private/Utils/SmartPtrTypes.h>
#include <Framework/Mdib/Public/Model/Component/AbstractDeviceComponentDescriptor.h>
#include <Framework/Mdib/Public/Model/Measurement.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief For battery-powered devices, static battery information can be contained in this object.
 * @ingroup Mdib
 */
class BatteryDescriptor: public AbstractDeviceComponentDescriptor
{
    DFL_MDIB_IMMUTABLE(BatteryDescriptor)

    public:
        /**
         * @brief Defaults to \ref SafetyClassification "safety classification" \ref SafetyClassification::Informational "informational"
         * without further information.
         */
        BatteryDescriptor() = default;

        /**
         * @brief Constructor.
         */
        template<class OptionalCodedValue_T, class OptionalMeasurement_T1, class OptionalMeasurement_T2, class OptionalMeasurement_T3>
        BatteryDescriptor(SafetyClassification safetyClassification,
                          OptionalCodedValue_T&& type,
                          ProductionSpecifications productionSpecifications,
                          OptionalMeasurement_T1&& capacityFullCharge,
                          OptionalMeasurement_T2&& capacitySpecified,
                          OptionalMeasurement_T3&& voltageSpecified,
                          ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief Current battery capacity after a full charge.
         * @return Full charge capacity number or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& capacityFullCharge() const;

        /**
         * @brief Rated capacity the manufacturer claims for the battery.
         * @return Rated capacity of battery or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& capacitySpecified() const;

        /**
         * @brief Specified battery voltage.
         * @return Specified battery voltage or \c boost::none if not specified.
         */
        const boost::optional<Measurement>& voltageSpecified() const;

    private:
        boost::optional<Measurement> m_capacityFullCharge;
        boost::optional<Measurement> m_capacitySpecified;
        boost::optional<Measurement> m_voltageSpecified;

};

template<class OptionalCodedValue_T, class OptionalMeasurement_T1, class OptionalMeasurement_T2, class OptionalMeasurement_T3>
inline BatteryDescriptor::BatteryDescriptor(SafetyClassification safetyClassification,
                                            OptionalCodedValue_T&& type,
                                            ProductionSpecifications productionSpecifications,
                                            OptionalMeasurement_T1&& capacityFullCharge,
                                            OptionalMeasurement_T2&& capacitySpecified,
                                            OptionalMeasurement_T3&& voltageSpecified,
                                            ExtensionTypes extensions):
        AbstractDeviceComponentDescriptor(safetyClassification,
                                          std::forward<OptionalCodedValue_T>(type),
                                          std::move(productionSpecifications), std::move(extensions)),
        m_capacityFullCharge(std::forward<OptionalMeasurement_T1>(capacityFullCharge)),
        m_capacitySpecified(std::forward<OptionalMeasurement_T2>(capacitySpecified)),
        m_voltageSpecified(std::forward<OptionalMeasurement_T3>(voltageSpecified))
{
}

inline const boost::optional<Measurement>& BatteryDescriptor::capacityFullCharge() const
{
    return m_capacityFullCharge;
}

inline const boost::optional<Measurement>& BatteryDescriptor::capacitySpecified() const
{
    return m_capacitySpecified;
}

inline const boost::optional<Measurement>& BatteryDescriptor::voltageSpecified() const
{
    return m_voltageSpecified;
}

/**
 * @brief Definition of shared pointer type \ref BatteryDescriptorSharedPtr for descriptor \ref BatteryDescriptor.
 * @ingroup Mdib
 */
using BatteryDescriptorSharedPtr = SharedPtr<BatteryDescriptor>;


} /* namespace Mdib */
} /* namespace DFL */
