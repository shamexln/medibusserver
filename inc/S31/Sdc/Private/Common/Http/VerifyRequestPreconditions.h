#pragma once

#include <S31/Sdc/Private/Common/Http/HttpSessionContext.h>
#include <S31/Utils/Public/Errors.h>

#include <functional>
#include <optional>

namespace S31::Sdc::Impl
{
/**
 * @brief Callback function to provide per-request checks of the session context.
 * @ingroup S31SdcCommon
 */
using VerifyRequestPreconditions = std::function<std::optional<Utils::Error>(const HttpSessionContext&)>;

}  // namespace S31::Sdc::Impl
