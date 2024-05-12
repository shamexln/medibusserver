#pragma once

#include <Framework/Format/Public/StdContainerIo.h>
#include <Framework/Utils/Public/EnumClass.h>

#include <set>

namespace S31::Sdc
{

/**
 * @brief   Subscription types for MDIB updates
 * @ingroup S31SdcClient
 */
enum class MdibSubscriptionType
{
    /// Entity descriptor update service type
    DescriptionEventService,
    /// Entity State update service type including metric, component, alert and operational states
    StateEventService,
    /// Context update service type
    ContextService,
    /// Waveform update service type
    WaveformService
};
DFL_ENUM_CLASS_STREAM_OPERATOR(MdibSubscriptionType, (DescriptionEventService)(StateEventService)(ContextService)(WaveformService))

/**
 * @brief Set of \ref MdibSubscriptionType "MdibSubscriptionTypes".
 * @ingroup S31SdcClient
 */
using MdibSubscriptionTypes = std::set<MdibSubscriptionType>;

}
