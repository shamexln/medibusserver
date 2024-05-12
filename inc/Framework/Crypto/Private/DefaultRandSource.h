#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/RandSourceFuncType.h>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
DFL_CRYPTO_EXPIMP RandomDeviceResultType openSslRandomNumber();

namespace Default
{
DFL_CRYPTO_EXPIMP RandSourceFunc randSource();
}
}
}
}
