#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/RandomDeviceResultType.h>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Type of hook for random source.
 *
 * @ingroup Crypto
 */
using RandSourceFunc = RandomDeviceResultType (*)();
}
}
