#pragma once

#include <S31/Error/Public/EventCode.h>

namespace S31::Error
{
/**
 * @brief Listener interface for event code state changes.
 *
 * @ingroup S31ErrorGroup
 */
class EventCodeObserver
{
public:
    virtual ~EventCodeObserver() noexcept = default;
    ///
    /// \brief Notification callback. An event was added.
    /// \param id Id of the event.
    ///
    virtual void eventAdded(EventCode id) = 0;
    ///
    /// \brief Notification callback. An event was removed/resolved.
    /// \param id Id of the event.
    ///
    virtual void eventRemoved(EventCode id) = 0;
};

}
