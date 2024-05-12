#pragma once

#include <S31/Sdc/Public/Client/ConnectionPriorityGroup.h>
#include <S31/S31CoreExImp.h>

#include <Framework/Chrono/Public/Duration.h>

namespace S31::Sdc::Impl
{

/**
 * @brief The maximum duration of a connection delay.
 * @ingroup S31SdcClient
 */
const DFL::Chrono::Seconds ConnectionDelayMaxDuration{2};

/**
 * @brief Provide the minimum delay of a @ref S31::Sdc::ConnectionPriorityGroup "priority group"
 * @ingroup S31SdcClient
 */
S31_CORE_EXPIMP DFL::Chrono::Seconds minimumConnectionDelay(ConnectionPriorityGroup groupId);

/**
 * @brief   Generate a delay time within the duration defined for
 * a @ref S31::Sdc::ConnectionPriorityGroup "priority group"
 * @details The delay time Td is a random number that has the following
 * properties: prio_group_id*5[s]<Td<(prio_group_id*5[s])+15 [s].
 * @ingroup S31SdcClient
 */
S31_CORE_EXPIMP DFL::Chrono::Milliseconds generateConnectionDelayTime(ConnectionPriorityGroup groupId);

}
