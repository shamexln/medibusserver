#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string>
#include <string_view>

namespace S31::Sdc::Impl
{

namespace Tags
{
struct SubscriptionErrorCodeTag{};
struct SubscriptionFilterDialectTag;
struct SubscriptionFilterContentTag;
}  // namespace Tags

/**
 * @brief Error code for failed filter processing.
 * @details
 * For codes defined in WS-Eventing
 * @ingroup S31SdcDevice
 */
using SubscriptionErrorCode = DFL::StrongTypedef<std::string, Tags::SubscriptionErrorCodeTag, DFL::Skill::Streamable>;

/**
 * @brief View type for a WS-Eventing subscription filter dialect.
 * @ingroup S31SdcDevice
 */
using SubscriptionFilterDialect =
        DFL::StrongTypedef<std::string_view, Tags::SubscriptionFilterDialectTag, DFL::Skill::Streamable>;
/**
 * @brief View type for a WS-Eventing subscription filter content.
 * @details Typically text or XML snippet. XML schema data type ist xsd:any.
 * @ingroup S31SdcDevice
 */
using SubscriptionFilterContent =
        DFL::StrongTypedef<std::string_view, Tags::SubscriptionFilterContentTag, DFL::Skill::Streamable>;

}
