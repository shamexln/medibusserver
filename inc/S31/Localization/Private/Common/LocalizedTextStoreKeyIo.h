#pragma once

#include <S31/Localization/Private/Common/LocalizedTextStore.h>

#include <Framework/Format/Public/Stream.h>

#include <iosfwd>

namespace S31::Localization::Impl
{

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31LocalizationCommon
 */
std::ostream& operator<<(std::ostream& out, const LocalizedTextStoreKey& data);

/**
 * @brief stream data to given stream.
 * @param out sink stream
 * @param data data to stream
 * @return passed stream
 * @ingroup S31LocalizationCommon
 */
DFL::Format::Stream& operator<<(DFL::Format::Stream& out, const LocalizedTextStoreKey& data);

}
