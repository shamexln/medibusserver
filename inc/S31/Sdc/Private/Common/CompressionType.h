#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc::Impl
{

/**
 * @brief Compression to use on the wire
 * @ingroup S31SdcCommon
 */
enum class CompressionType
{
    None,
    gzip
};

DFL_ENUM_CLASS_STREAM_OPERATOR(CompressionType, (None)(gzip))

}
