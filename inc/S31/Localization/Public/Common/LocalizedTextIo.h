#pragma once

#include <S31/Localization/Public/Common/S31LtsExImp.h>

#include <Framework/Format/Public/Stream.h>

#include <ostream>

namespace S31::Localization
{

class LocalizedText;

/**
 * @brief Generates a human readable representation.
 * @details Format is not specified. It is typically used for debug log messages.
 * @param out Sink for data
 * @param data Input data structure to convert to string
 * @return human readable representation of data.
 */
S31_LTS_EXPIMP DFL::Format::Stream& operator<<(DFL::Format::Stream& out, LocalizedText const& data);

/**
 * @brief Stream operator for \ref LocalizedText.
 * @param out Sink for data
 * @param data Data to stream
 * @return the referenced sink (first argument)
 */
S31_LTS_EXPIMP std::ostream& operator<<(std::ostream& out, LocalizedText const& data);

}
