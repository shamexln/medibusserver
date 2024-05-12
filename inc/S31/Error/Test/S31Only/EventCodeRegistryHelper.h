#pragma once

#include <S31/Error/S31Only/EventCodeRegistry.h>

namespace S31::Error::Test
{

/**
 * @brief Function to clear all active remos codes in global singleton.
 * @ingroup S31ErrorGroup
 */
static void clearAllActiveRemosCodes()
{
    const auto& errors = EventCodeRegistry::instance()->getActiveEvents();
    for (const auto& error : errors)
    {
        EventCodeRegistry::instance()->removeEvent(error);
    }
}

}
