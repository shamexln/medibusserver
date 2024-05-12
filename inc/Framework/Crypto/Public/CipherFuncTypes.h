#pragma once

#include <Framework/Crypto/Private/ExpImp.h>
#include <Framework/Crypto/Public/Buffer.h>

namespace DFL
{
namespace Crypto
{
/**
 * @brief Type of hook for encryption.
 *
 * @ingroup Crypto
 */
using EncryptFunc = Buffer (*)(const Buffer&);
/**
 * @brief Type of hook for decryption.
 *
 * @ingroup Crypto
 */
using DecryptFunc = Buffer (*)(const Buffer&);
}
}
