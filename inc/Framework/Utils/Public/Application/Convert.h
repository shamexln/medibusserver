#pragma once

#include <Framework/Utils/Private/ExpImp.h>
#include <string>

namespace DFL
{
namespace Application
{
class SoftwareVersionNumber;

namespace Convert
{
/**
 * @brief Convert given software version number to IN4206 compatible string.
 * @details Format is MAJOR.MINOR.PATCH
 *
 * @snippet Utils/Test/UnitTest/TestSoftwareVersionNumber.cpp toIn4206
 *
 * @ingroup Utils 
 */
DFL_UTILS_EXPIMP std::string toIn4206(const SoftwareVersionNumber& v);
}
}
}
