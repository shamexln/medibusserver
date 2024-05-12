#pragma once

#include <Framework/Mdib/Private/ExpImp.h>
#include <Framework/Mdib/Public/Model/Decimal.h>
#include <Framework/Mdib/Public/Model/Decimals.h>

#include <boost/optional.hpp>

#include <string>

namespace DFL
{
namespace Mdib
{
namespace Convert
{

/**
 * @brief Converts \ref Decimal to std::string in canonical form of XML Schema decimal data type.
 * @details The string format is specified in
 * <a href="https://www.w3.org/TR/xmlschema-2/#decimal-canonical-representation">XML Schema Part&nbsp;2:
 * Datatypes Second Edition</a> section 3.2.3.2.
 * @note To avoid too long string representations special treatment for small and large exponents is implemented.
 * Decimals with an exponent > 80 will result in a runtime exception, while numeric values with an exponent < -80 will be 0.0.
 * @throw runtime exception for \ref Decimal instances with an exponent > 80.
 * @param decimal numeric value to convert from
 * @return numeric value in XML schema canonical form
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP std::string toXmlCanonicalString(Decimal const& decimal);

/**
 * @brief Converts \ref Decimal to std::string in canonical form of XML Schema decimal data type.
 * @details The string format is specified in
 * <a href="https://www.w3.org/TR/xmlschema-2/#decimal-canonical-representation">XML Schema Part&nbsp;2:
 * Datatypes Second Edition</a> section 3.2.3.2.
 * @note To avoid too long string representations special treatment for small and large exponents is implemented.
 * Decimals with an exponent > 80 will result in <tt>boost::none</tt>, while numeric values with an exponent < -80 will be 0.0.
 * @param decimal numeric value to convert from
 * @return numeric value in XML schema canonical form or <tt>boost::none</tt> for to long string representations.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<std::string> toOptionalXmlCanonicalString(Decimal const& decimal);

/**
 * @brief Converts a \ref Decimal to double.
 *
 * @param decimal input value
 * @return numeric value as double
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP double toDouble(Decimal const& decimal);

/**
 * @brief Parse numeric string value into \ref Decimal.
 * @throw Parsing errors and overflows result in a runtime exception.
 * For an exception free version use \ref toOptionalDecimal().
 *
 * @param decimalString
 * @return parsed numeric value
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Decimal toDecimal(const std::string& decimalString);

/**
 * @brief Parse numeric string value into \ref Decimal.
 * @throw Parsing errors and overflows result in a runtime exception.
 * For an exception free version use \ref toOptionalDecimal().
 *
 * @param decimalString The value as a string, nullptr is allowed but results in an convert error
 * @return parsed numeric value
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Decimal toDecimal(const char* decimalString);

/**
 * @brief Create \ref Decimal from double value.
 * @throw Converting errors (not a number, overflows, ...) result in a runtime exception.
 * For an exception free version use \ref toOptionalDecimal().
 *
 * @param value numeric value
 * @return newly created decimal
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Decimal toDecimal(double value);

/**
 * @brief Create \ref Decimal from float value.
 * @throw Converting errors (not a number, overflows, ...) result in a runtime exception.
 * For an exception free version use \ref toOptionalDecimal().
 *
 * @param value numeric value
 * @return newly created decimal
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Decimal toDecimal(float value);

/**
 * @brief Create \ref Decimal from double value.
 * @details Converting errors (not a number, overflows, ...) result in <tt>boost::none</tt>.
 *
 * @param value numeric value
 * @return newly created decimal or <tt>boost::none</tt> in case of converting problems.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<Decimal> toOptionalDecimal(double value);

/**
 * @brief Create \ref Decimal from float value.
 * @details Converting errors (not a number, overflows, ...) result in <tt>boost::none</tt>.
 *
 * @param value numeric value
 * @return newly created decimal or <tt>boost::none</tt> in case of converting problems.
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<Decimal> toOptionalDecimal(float value);

/**
 * @brief Parse numeric string value into \ref Decimal.
 *
 * In case of parsing errors <tt>boost::none</tt> will be returned.
 *
 * @param decimalString
 * @return parsed numeric value (or <tt>boost::none</tt>)
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<Decimal> toOptionalDecimal(const std::string& decimalString);

/**
 * @brief Parse numeric string value into \ref Decimal.
 *
 * In case of parsing errors <tt>boost::none</tt> will be returned.
 *
 * @param decimalString The value as a string, nullptr is allowed
 * @return parsed numeric value (or <tt>boost::none</tt>)
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<Decimal> toOptionalDecimal(const char* decimalString);

/**
 * @brief Parse numeric string value into \ref Decimal up to next whitespace.
 *
 * In case of parsing errors <tt>boost::none</tt> will be returned.
 *
 * @param decimalString The value as a string, nullptr is allowed
 * @return parsed numeric value (or <tt>boost::none</tt>)
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP boost::optional<Decimal> toOptionalDecimalUpToWhitespace(const char* decimalString);

/**
 * @brief Parse numeric string values into \ref Decimals.
 * @details Valid input strings are <tt>"2.3 -34.567"</tt> or <tt>" \t-34.5  \n 23.5  "</tt>.
 *
 * @throw Converting errors (not a number, overflows, ...) result in a runtime exception.
 *
 * @param decimalString Leading and trailing whitespaces are allowed as well as multiple whitespaces between decimals.
 * @return Sequence of Decimal
 *
 * @ingroup Mdib
 */
DFL_MDIB_EXPIMP Decimals toDecimals(const char* decimalString);

} /* namespace Convert */
} /* namespace Mdib */
} /* namespace DFL */
