#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

namespace DFL
{
namespace Crypto
{
class Certificate;

namespace Impl
{
class DFL_CRYPTO_EXPIMP KnownRootCas
{
public:
    static const Certificate& deviceRootCa();
    static const Certificate& testRootCa();
    static const Certificate& stagingRootCa();
};
}
}
}
