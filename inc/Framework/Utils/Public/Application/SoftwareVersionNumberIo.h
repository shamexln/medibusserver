#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <iosfwd>

namespace DFL
{
namespace Application
{
class SoftwareVersionNumber;
/**
 * @brief Creates readable form of given software version number.
 *
 * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp streaming
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP std::ostream& operator<<(std::ostream& str, const SoftwareVersionNumber& v);
}
}

namespace DFL
{
namespace Format
{
class Stream;
/**
 * @brief Creates readable form of given software version number.
 *
 * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp streaming
 *
 * @ingroup Utils
 */
DFL_UTILS_EXPIMP Stream& operator<<(Stream& str, const Application::SoftwareVersionNumber& v);
}
}
