#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Application
{
class Identifier;
/**
 * @brief Creates readable form of given application identifier.
 *
 * @snippet Utils/Test/UnitTest/TestIdentifier.cpp streaming
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& str, const Identifier& id);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given application identifier.
 *
 * @snippet Utils/Test/UnitTest/TestIdentifier.cpp streaming
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& str, const Application::Identifier& id);
}
}
