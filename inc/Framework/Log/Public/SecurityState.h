#pragma once

namespace DFL
{
namespace Log
{
/**
 * @brief Indicates the security state of a ::DFL::Log::Message
 *
 * @ingroup Log
 */
enum class SecurityState
{
    /// Message is not security related
    None,
    /// Message originated from a security event
    Event,
    /// Message originated from a security event which needs SNMP trap handling
    Trap
};

}
}
