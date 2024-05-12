#pragma once

#include <Framework/Chrono/Private/ExpImp.h>

namespace DFL {
namespace Chrono {

/**
 * @brief Environment for the chrono library is configured here.
 * @ingroup Chrono
 */
class DFL_CHRONO_EXPIMP Environment
{
public:
    /**
     * @brief Initializes the @ref DFL::Chrono::Registry.
     *
     * @note This method shall be called prior to any usage of the chrono library.
     */
    static void init();

    /**
     * @brief Shuts the @ref DFL::Chrono::Registry down.
     */
    static void shutdown();
};

}
}
