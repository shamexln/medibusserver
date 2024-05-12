#pragma once

#include <S31/Sdc/Private/Common/Http/HttpResult.h>

#include <functional>

namespace S31::Sdc::Impl
{
/**
 * @brief Callback function to receive an @ref HttpResult.
 * @ingroup S31SdcCommon
 */
using HttpResultCallback = std::function<void(const HttpResult&)>;

}  // namespace S31::Sdc::Impl
