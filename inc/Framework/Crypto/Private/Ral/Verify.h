#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

#include <Framework/Encoding/Public/Bytes.h>

#include <boost/utility/string_view.hpp>

namespace DFL
{
namespace Crypto
{
namespace Impl
{
namespace Ral
{
using Signature = Encoding::Bytes;

DFL_CRYPTO_EXPIMP bool verify(boost::string_view ralStr);
}
}
}
}
