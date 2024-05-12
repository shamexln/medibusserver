#pragma once

#include <Framework/Log/Private/BasicContainerLogger.h>
#include <Framework/Log/Public/Message.h>

#include <vector>

namespace DFL
{
namespace Log
{
/**
 * @brief Logs messages into a std::vector.
 *
 * Stored messages can be accessed via iterators.
 * @snippet Log/Test/UnitTest/TestContainerLogger.cpp Append
 *
 * @ingroup Log
 */
using ContainerLogger = Impl::BasicContainerLogger<std::vector<Message> >;
}
}
