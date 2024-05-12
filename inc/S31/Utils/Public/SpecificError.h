#pragma once

#include <S31/Utils/Public/AnySubclass.h>

#include <any>

namespace S31::Utils
{

/**
 * @brief Base Class for all specific Errors.
 * @ingroup S31SdcCommon
 */
struct SpecificError
{
};

using AnySubclassOfSpecificError = AnySubclass<SpecificError>;

} /* Namespace S31::Utils */