#pragma once

#include <Framework/Crypto/Private/ExpImp.h>

namespace DFL::Crypto
{
class Configuration;
/**
 * @brief Initializes/Shuts down this library.
 *
 * Every init call shall be paired with an according shutdown call.
 * Internally a counter is held which is incremented on a call to init
 * and decremented on a call to shutdown. Only the first init and the
 * last shutdown call execute code.
 * If the certificate store shall be used config has to be called between
 * init and shutdown.
 *
 * @note
 * These functions must be called during a single threaded phase!
 *
 * @ingroup Crypto
 */
class DFL_CRYPTO_EXPIMP Environment
{
public:
    /**
     * @brief Initializes this library.
     *
     * Any further calls just increment a call counter.
     *
     * @return
     * True if successful, otherwise false.
     * If false is returned the library is not usable.
     */
    static bool init();
    /**
     * @brief Configures the certificate store.
     *
     * @pre init has been called successfully.
     *
     * @return
     * True if successful, otherwise false.
     * If false is returned the certificate store is not usable.
     */
    static bool config(const Configuration& cfg);
    /**
     * @brief Shuts this library down.
     *
     * An internal counter is decremented and the actual shutdown
     * operation is only executed if this counter reaches 0.
     *
     * @pre init has been called successfully.
     *
     * @return
     * True if successful, otherwise false.
     */
    static bool shutdown();
};
}
