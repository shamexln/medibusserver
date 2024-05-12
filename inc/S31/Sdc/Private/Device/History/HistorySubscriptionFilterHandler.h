#pragma once

#include <S31/History/Public/Query.h>

#include <optional>
#include <string_view>

namespace S31::Sdc::Impl
{

/**
 * @brief Parses a history subscription filter from gSOAP.
 * @details Get the  history query if there is one.
 * @ingroup S31SdcDevice
 */
std::optional<History::Query> parseHistoryQuery(std::string_view filter);

}  // namespace S31::Sdc::Impl
