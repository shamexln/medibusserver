#pragma once

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string_view>

namespace S31::Sdc::Impl
{
/**
 * @brief Soap Action
 */
/// @{
struct SoapActionViewTag;
using SoapActionView =
        DFL::StrongTypedef<std::string_view, SoapActionViewTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;
/// @}

struct SoapMessageBodyViewTag;
/**
 * @brief Soap message body, to be encapsulated in a Soap envelope.
 */
using SoapMessageBodyView = DFL::
        StrongTypedef<std::string_view, SoapMessageBodyViewTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;
}
