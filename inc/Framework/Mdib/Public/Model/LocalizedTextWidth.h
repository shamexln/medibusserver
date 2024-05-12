#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace DFL
{
namespace Mdib
{

/**
 * @brief   LocalizedTextWidth to represent TextWidth enumeration
 * @details Text width as defined in pm:LocalizedTextWidth
 *
 * @ingroup Mdib
 */
enum class LocalizedTextWidth
{
        /// A line has 4 or less fullwidth characters
        ExtraSmall,
        /// A line has 8 or less fullwidth characters.
        Small,
        /// A line has 12 or less fullwidth characters.
        Medium,
        /// A line has 16 or less fullwidth characters.
        Large,
        /// A line has 20 or less fullwidth characters.
        ExtraLarge,
        /// A line has 21 or more fullwidth characters.
        ExtraExtraLarge
};
DFL_ENUM_CLASS_STREAM_OPERATOR(LocalizedTextWidth, (ExtraSmall)(Small)(Medium)(Large)(ExtraLarge)(ExtraExtraLarge))


} /* namespace Mdib */
} /* namespace DFL */
DFL_ENUM_CLASS_SERIALIZATION(DFL::Mdib::LocalizedTextWidth, ((ExtraSmall,0))((Small,1))((Medium,2))((Large,3))((ExtraLarge,4))((ExtraExtraLarge,5)))
