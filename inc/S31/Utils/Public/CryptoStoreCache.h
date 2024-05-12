#pragma once

#include <S31/Utils/Private/S31UtilsExImp.h>

#include <Framework/Crypto/Public/Table.h>
#include <Framework/Thread/Public/RecursiveMutex.h>

namespace S31::Utils
{
/**
 * @brief Read cache for DFL crypto store.
 * @details
 * The cache is designed to provide deterministic read access (to cached data).
 * Furthermore, the access to the crypto store is not fast enough to access it every time.
 * @ingroup S31Utils
 */
class S31_UTILS_EXPIMP CryptoStoreCache
{
public:
    static CryptoStoreCache& instance();

    /**
     * @brief Returns the cached crypto store table.
     * @return In case of an error, an empty table will be returned
     */
    DFL::Crypto::Table table() const;

    /**
     * @brief Queries the crypto store and updates the cache.
     * @details
     * Due to access to the underlying IO system the completion time for this operation is non-deterministic.
     * Call this function is a low prio thread to update the cache
     */
    void forceSynchronousUpdate() noexcept;

     /**
     * @brief Resets the store table.
     */
    void reset();

private:
    CryptoStoreCache();

    mutable DFL::Thread::RecursiveMutex m_mutex;
    DFL::Crypto::Table m_table;
};

}
