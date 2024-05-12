#pragma once

#include <Framework/Mdib/Private/ExpImp.h>

namespace DFL
{
namespace Mdib
{
namespace Ext
{
/**
 * @brief Request suppression of any notification about ongoing external
 * control.
 *
 * @details
 * When an SDC Service Provider is being externally controlled, it may need to
 * inform the user or other SDC Participants that external control is ongoing.
 * This extension enables an SDC Service Consumer to request suppression of any
 * notification about ongoing external control. This can be meaningful, e.g., if
 * the controlling SDC Service Consumer is in immediate vicinity or actionable
 * vicinity to the controlled SDC Service Provider.
 *
 * Note 1: Externally controlling SDC Service Consumers may also decide to
 * supress showing remote control ongoing notifications.
 *
 * Note 2: The need for suppression of certain notifications depends upon the
 * proximity of an SDC Service Consumer to the externally controlled SDC Service
 * Provider.
 *
 * Note 3: Example: The Bridge is in the immediate vicinity of the patient
 * monitor it controls, and therefore remote control ongoing notifications can
 * be suppressed.
 *
 * @note An SDC Service Consumer shall set \@ext:MustUnderstand = "false"
 *
 * @ingroup Mdib
 */
class DFL_MDIB_EXPIMP SuppressExternalControlAlert
{
public:
    /**
     * @brief Specify whether external control alert shall be suppressed.
     */
    explicit SuppressExternalControlAlert(bool suppress);

    /**
     * @brief Indicates whether external control alert shall be suppressed.
     * @details
     * If \c true, the SDC Service Provider should not annunciate the external
     * control SCO operation call for which the SuppressExternalControlAlert is
     * specified. If \c false, no specific behavior is requested.
     */
    bool isSuppress() const noexcept;
private:
    bool m_suppress{false};
};

/**
 * @brief Checks for equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP
operator==(const SuppressExternalControlAlert& lhs,
           const SuppressExternalControlAlert& rhs) noexcept;

/**
 * @brief Checks for non-equality of both instances.
 * @ingroup Mdib
 */
bool DFL_MDIB_EXPIMP
operator!=(const SuppressExternalControlAlert& lhs,
           const SuppressExternalControlAlert& rhs) noexcept;
}
}
}
