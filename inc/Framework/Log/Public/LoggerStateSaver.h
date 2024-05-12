#pragma once

#include <Framework/Log/Public/Logger.h>

#include <Framework/Utils/Public/StateSaver.h>

namespace DFL
{
namespace Log
{
/**
 * @brief
 * Saves state of given Logger when constructed and restores this state when
 * destructed.
 *
 * @snippet Log/Test/UnitTest/TestLoggerStateSaver.cpp SaveRestore
 *
 * @ingroup Log
 */
using LoggerStateSaver = StateSaver<Logger>;
}
}
