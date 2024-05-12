#pragma once

#include <S31/Base/S31Only/NtStringView.h>

#include <Framework/Utils/Public/StrongTypedef.h>

#include <string_view>

namespace S31::Sdc::Impl
{

struct SoapActionNtViewTag;
using SoapActionNtView =
        DFL::StrongTypedef<NtStringView, SoapActionNtViewTag, DFL::Skill::EqualityComparable, DFL::Skill::Streamable>;

}  // namespace S31::Sdc::Impl
