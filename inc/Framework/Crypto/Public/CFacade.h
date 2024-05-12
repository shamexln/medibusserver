#pragma once

#include <Framework/Config/Public/Config.h>
#if defined(DFL_CONFIG_OS_WIN32)

#include <Framework/Crypto/Private/ExpImp.h>

#include <cstdint>

/**
 * @brief Searches for the given component and returns the respective
 * certificate chain if found
 *
 * @param cryptoStoreFolder Path to crypto store in filesystem
 * @param componentId Numeric ID of component
 * @param componentInstance Instance id of component
 * @param chainBuffer Buffer to receive chain
 * @param chainBufferLen Length of buffer in bytes
 *
 * @return
 * - 0 on success
 * - -1 if no entry in store or the store is not accessbile
 * - -2 if buffer is too short to hold chain
 * - -3 if chain in store is empty or not convertible to PEM
 *
 * In case of an error the given buffer is not altered.
 *
 * @ingroup Crypto
 */
extern "C" DFL_CRYPTO_EXPIMP int dflCryptoStoreChain(
    const char* cryptoStoreFolder,
    uint16_t componentId,
    uint16_t componentInstance,
    char* chainBuffer,
    size_t chainBufferLen);

/**
 * @brief Searches for given component and returns private key if found
 *
 * @param cryptoStoreFolder Path to crypto store in filesystem
 * @param componentId Numeric ID of component
 * @param componentInstance Instance id of component
 * @param keyBuffer Buffer to receive private key
 * @param keyBufferLen Length of buffer in bytes
 *
 * @return
 * - 0 on success
 * - -1 if no entry in store or the store is not accessbile
 * - -2 if buffer is too short to hold private key
 * - -3 if key is empty or not convertible to PEM
 *
 * In case of an error the given buffer is not altered.
 *
 * @ingroup Crypto
 */
extern "C" DFL_CRYPTO_EXPIMP int dflCryptoStorePrivateKey(
    const char* cryptoStoreFolder,
    uint16_t componentId,
    uint16_t componentInstance,
    char* keyBuffer,
    size_t keyBufferLen);

#endif
