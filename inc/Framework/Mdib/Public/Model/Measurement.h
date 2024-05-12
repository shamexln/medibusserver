#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Private/CompilerGenerated.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Unit.h>
#include <Framework/Mdib/Private/HasExtensions.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Describes a measurement for stateful object attributes that do not have a reference to a descriptor object.
 * @details Example: weight of a patient.
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Measurement: public Impl::HasExtensions
{
    public:
        /**
         * @brief Constructor.
         */
        Measurement(Decimal value,
                    const Unit& unit,
                    ExtensionTypes extensions = ExtensionTypes{ });

        /**
         * @brief The measurement's value.
         */
        const Decimal& value() const;

        /**
         * @brief The measurement's unit.
         */
        const Unit& unit() const;

        friend bool operator==(const Measurement& lhs, const Measurement& rhs) noexcept;

    private:
        Decimal m_value;
        Unit m_unit;
};

/**
 * @brief Equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case all members equals.
 */
inline bool operator==(const Measurement& lhs, const Measurement& rhs) noexcept
{
    return lhs.m_value == rhs.m_value
           && lhs.m_unit == rhs.m_unit &&
           lhs.extensions() == rhs.extensions();
}

/**
 * @brief Not equal operator compares all members (including descriptive texts).
 * @param lhs Instance to compare with
 * @param rhs Instance to compare with
 * @return \c true in case at least one member does not equal.
 */
inline bool operator!=(const Measurement& lhs, const Measurement& rhs) noexcept
{
    return !(lhs == rhs);
}

} /* namespace Mdib */
} /* namespace DFL */
