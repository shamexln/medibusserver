#pragma once

#include <Framework/Log/Private/ExpImp.h>
#include <Framework/Log/Public/ContainerLogger.h>

#include <iosfwd>

namespace DFL
{
namespace Log
{
/**
 * @brief Streams logged messages object to ostream.
 * @param out Stream to put log messages in.
 * @param logger Messages to be put into stream
 * @return The given stream object.
 * @ingroup Log
 */
DFL_LOG_EXPIMP std::ostream& operator<<(std::ostream& out,
                                        const ContainerLogger& logger);
}
}
