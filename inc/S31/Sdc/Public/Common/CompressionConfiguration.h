#pragma once

#include <Framework/Utils/Public/EnumClass.h>

namespace S31::Sdc
{

/**
 * @brief Compression to use on the wire
 * @ingroup S31SdcCommon
 */
enum class CompressionConfiguration
{
    NoCompression,
    Compression
};
DFL_ENUM_CLASS_STREAM_OPERATOR(CompressionConfiguration, (NoCompression)(Compression))
}
