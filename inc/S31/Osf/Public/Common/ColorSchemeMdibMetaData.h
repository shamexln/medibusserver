#pragma once

#include <S31/S31CoreExImp.h>

#include <Framework/Mdib/Public/Model/CodedValue.h>

namespace S31::Osf::ColorSchemeMdibMetaData
{
/*!
 *
 * @return CodedValue that represents the color scheme set operation.
 */
DFL::Mdib::CodedValue S31_CORE_EXPIMP operationTypeColorScheme();

/*!
 *
 * @return CodedValue that represents the color scheme operation target.
 */
DFL::Mdib::CodedValue S31_CORE_EXPIMP operationTargetTypeColorScheme();
}
