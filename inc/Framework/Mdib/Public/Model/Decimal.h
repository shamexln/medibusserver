#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <boost/operators.hpp>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Represent a numeric value with fixed point.
 * @details The representation of this class uses an integer value with an additional exponent (base 10).
 * It is designed to preserve the precision from the <a href="https://www.w3.org/TR/xmlschema-2/#decimal">XML schema decimal datatype</a> and
 * also covers numeric metric values from the S14 platform without conversions.
 *
 * For conversion to/from double and std::string \ref Model/DecimalIo.h provides corresponding functions.
 *
 * The class is explicitly defined without
 * - not a number
 * - overflow
 * - underflow
 *
 * support. The reasons are
 * - XML Schema decimal requires to have a valid numeric value
 * - S14 also does not support invalid states of its equivalent data types.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP Decimal: public boost::less_than_comparable<Decimal>
{
    public:
        /**
         * @brief Default to the value 0.0.
         */
        Decimal() = default;

        /**
         * @brief Construct from integer value.
         * @param value integer value of numeric value
         */
        explicit Decimal(int value) noexcept;

        /**
         * @brief Not available. Use \ref Convert::toOptionalDecimal() instead.
         * @warning not available, use DecimalIo instead
         * @param value not available
         */
        explicit Decimal(float value);

        /**
         * @brief Not available. Use \ref Convert::toOptionalDecimal() instead.
         * @warning not available, use DecimalIo instead
         * @param value not available
         */
        explicit Decimal(double value);

        /**
         * @brief Constructor with scientific notation.
         *
         * An approximation for pi (3.14) has a value of 314 and an exponent of -2:
         * Decimal(314, -2) = 3.14
         *
         * @param value Integer value of the fixed point number (as if there were no point).
         * @param exponent Exponent with base 10.
         */
        Decimal(int value, int exponent) noexcept;

        /**
         * @brief Provides the value.
         * @details Can only be used in conjunction with exponent to interpret absolute value.
         * @return the value
         */
        int intValue() const;

        /**
         * @brief Provides the exponent of the decimal.
         * @return the exponent
         */
        int intExponent() const;

    private:
        int m_value{0};
        int m_exponent{0};

};

/**
 * @brief Compares two \ref Decimal instances.
 * @details For the comparison the decimal value is "normalized".
 * Decimal(30, 0) equals Decimal (3, 1), since both represent an integer value of 30.
 * @param lhs first value to compare with.
 * @param rhs second value to compare with.
 * @return \c true in case the instances represent the same numeric value.
 *
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const Decimal& lhs, const Decimal& rhs) noexcept;

/**
 * @brief Compares two \ref Decimal instances.
 * @param lhs first value to compare with.
 * @param rhs second value to compare with.
 * @return \c true in case the instances represent different numeric values.
 *
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const Decimal& lhs, const Decimal& rhs) noexcept;

/**
 * @brief Compares two \ref Decimal instances.
 * @param lhs first value to compare with.
 * @param rhs second value to compare with.
 * @return \c true in case the numerical value of \ref Decimal is lesser.
 *
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator<(const Decimal& lhs, const Decimal& rhs);

} /* namespace Mdib */
} /* namespace DFL */
