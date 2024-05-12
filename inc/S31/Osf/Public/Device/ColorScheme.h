#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Osf
{
/*!
 * \brief Color schemes that can be processed by S31.
 *
 * \ingroup S31OsfDevice
 */
enum class ColorScheme
{
    /// day mode color scheme
    Light,
    /// day mode dark color scheme
    Dark
};
DFL_ENUM_CLASS_STREAM_OPERATOR(ColorScheme, (Light)(Dark))

}
