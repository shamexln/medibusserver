#pragma once

#include <S31/Osf/Public/Device/ColorScheme.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Utils/Public/Utf8.h>

/*!
 * \brief Functions to convert the ColorScheme to an allowed value string and vice versa.
 * \ingroup S31OsfDevice
 */
namespace S31::Osf::ColorSchemeConverter
{

/*!
 * Converts an arbitrary string to a S31::Osf::ColorScheme.
 *
 * @param colorScheme Identifier that holds a valid colorScheme value as string.
 *
 * @return Converted enumeration value. If conversion fails, a std::runtime_error is thrown
 */
S31::Osf::ColorScheme S31_CORE_EXPIMP toColorScheme(const DFL::Locale::Utf8& colorScheme);

/*!
 * Converts S31::Osf::ColorScheme to a string.
 *
 * @param colorScheme Color theme to convert.
 *
 * @return The Color theme string representation.
 */
DFL::Locale::Utf8 S31_CORE_EXPIMP toString(S31::Osf::ColorScheme colorScheme);

}
