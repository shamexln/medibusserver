#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Utils/Public/StrongTypedef.h>

#include <cstdint>
#include <optional>

namespace DFL::Mdib::Ext
{
namespace Impl
{
struct FractionalDigitsTag {};
}

/**
 * @brief Specifies the number of digits of the decimal to truncate after the decimal point
 * @ingroup Mdib
 */
using FractionalDigits = DFL::StrongTypedef<std::uint32_t, Impl::FractionalDigitsTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;

/**
 * @brief A decimal number that is truncated at a certain fractional digit
 * @details Truncation rules with FractionalDigits: 
 * - If the fractionalDigits value is absent, no truncation is performed
 * - If the fractionalDigits value is present, it specifies the number of digits to the right of the decimal point
 * - If the actual fractional digits of the decimal are less than the fractional digits to truncate, the rendered decimal is padded with 
 *   zeros to the right to meet the number of digits specified by fractionalDigits
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP DecimalWithFractionalDigits
{
public: 
    /**
     * @brief Constructor with decimal value and the optional number of digits to truncate to after the decimal point
     */
    DecimalWithFractionalDigits(Decimal decimal, std::optional<FractionalDigits> fractionalDigits);

    /**
     * @brief Decimal value number
     */
    Decimal decimal() const noexcept;
    
    /**
     * @brief The number of digits of the decimal to truncate after the decimal point
     */
    std::optional<FractionalDigits> fractionalDigits() const noexcept;

private:

    DFL::Mdib::Decimal m_decimal;
    std::optional<FractionalDigits> m_digits;
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator==(const DecimalWithFractionalDigits& lhs,
                                const DecimalWithFractionalDigits& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP operator!=(const DecimalWithFractionalDigits& lhs,
                                const DecimalWithFractionalDigits& rhs) noexcept;
}
