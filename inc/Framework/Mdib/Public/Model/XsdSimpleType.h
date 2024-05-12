#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief XML Schema simple data type.
 * @details XML Schema Part 2 defines simple and complex data types.
 * The enumeration contains all simple data types like xsd:string, xsd:decimal, xsd:QName, ...
 * All 44 simple data types are listed in the standard
 * https://www.w3.org/TR/xmlschema-2/#built-in-datatypes
 * The original names are changed in that way, that they start with a capital letter.
 * This is also required to preserve keywords like \c int.
 *
 * @ingroup Mdib
 */
enum class XsdSimpleType
{
    String,
    Boolean,
    Decimal,
    Float,
    Double,
    Duration,
    DateTime,
    Time,
    Date,
    GYearMonth,
    GYear,
    GMonthDay,
    GDay,
    GMonth,
    HexBinary,
    Base64Binary,
    AnyURI,
    QName,
    NOTATION,
    NormalizedString,
    Token,
    Language,
    NMTOKEN,
    NMTOKENS,
    Name,
    NCName,
    ID,
    IDREF,
    IDREFS,
    ENTITY,
    ENTITIES,
    Integer,
    NonPositiveInteger,
    NegativeInteger,
    Long,
    Int,
    Short,
    Byte,
    NonNegativeInteger,
    UnsignedLong,
    UnsignedInt,
    UnsignedShort,
    UnsignedByte,
    PositiveInteger
};
DFL_ENUM_CLASS_STREAM_OPERATOR(XsdSimpleType, (String)(Boolean)(Decimal)(Float)(Double)(Duration)(DateTime)
    (Time)(Date)(GYearMonth)(GYear)(GMonthDay)(GDay)(GMonth)(HexBinary)(Base64Binary)(AnyURI)(QName)
    (NOTATION)(NormalizedString)(Token)(Language)(NMTOKEN)(NMTOKENS)(Name)(NCName)(ID)(IDREF)(IDREFS)
    (ENTITY)(ENTITIES)(Integer)(NonPositiveInteger)(NegativeInteger)(Long)(Int)(Short)(Byte)
    (NonNegativeInteger)(UnsignedLong)(UnsignedInt)(UnsignedShort)(UnsignedByte)(PositiveInteger))

}
}
