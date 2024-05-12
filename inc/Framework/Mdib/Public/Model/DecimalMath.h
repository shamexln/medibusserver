#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Decimal.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief Math function for \ref Decimal.
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP DecimalMath
{
    public:
        /**
         * @brief Normalizes value and exponent.
         *
         * Trailing zeros of the value are removed by incrementing the exponent.
         * E.g.,
         * - 34.30 will be converted to 34.3
         * - Decimal(3430, -2) -> Decimal(343, -1)
         * - Decimal(100, 0) -> Decimal(1, 2)
         *
         * @param number numeric value to normalize
         * @return normalized value
         */
        static Decimal normalizeDecimal(const Decimal& number) noexcept;

        /**
         * @brief Count the length of digits.
         *
         * It will count trailing zeros, since it does not count the significant figures only.
         * Examples:
         * - 23 results in 2
         * - 230 results in 3
         * - -40 results in 2
         *
         * @param number numeric value to count digits.
         * @return length
         */
        static unsigned int numberOfDigits(int number);
};

} /* namespace Mdib */
} /* namespace DFL */
