#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>

namespace S31::Sdc::Impl
{

/**
 * @brief Container for a client-side local WS-Eventing subscription identifier.
 *
 * @details
 * The subscription identifier is used here on the client side to distinguish between the
 * different WS-Eventing subscriptions when delivering the event reports.
 *
 * In the WS-Eventing Subscribe SOAP message, it is embedded in the wse:NotifyTo element
 * (the subscription ID is appended to the content of the wsa:Address element). In the
 * reports it is part of the wsa:To SOAP header block.
 *
 * \ingroup S31SdcClientEventing
 */
using WSEventingClientSubscriptionId = DFL::StrongTypedef<std::string, struct WSEventingClientSubscriptionIdTag, DFL::Skill::TotallyOrdered, DFL::Skill::Streamable>;


}
