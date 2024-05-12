#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Encoding types used in HTTP Content-Encoding header
 * @ingroup S31SdcCommon
 */
enum class EncodingType
{
        None,
        gzip
};

DFL_ENUM_CLASS_STREAM_OPERATOR(EncodingType, (None)(gzip))

}
